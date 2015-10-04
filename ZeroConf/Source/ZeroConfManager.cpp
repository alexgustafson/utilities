/*
  ==============================================================================

    ZeroConfManager.cpp
    Created: 27 Aug 2015 11:17:34am
    Author:  Alexander Gustafson

  ==============================================================================
*/

#include "ZeroConfManager.h"
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>

#define NI_MAXHOST      1025
#define NI_MAXSERV      32


static void zeroBrowseCallback(DNSServiceRef sdRef,
                               DNSServiceFlags flags,
                               uint32_t interfaceIndex,
                               DNSServiceErrorType errorCode,
                               const char *serviceName,
                               const char *regtype,
                               const char *replyDomain,
                               void *context)
{
    if (errorCode != kDNSServiceErr_NoError)
    {
        Logger::writeToLog(String::formatted("zeroBrowseCallback returned %d\n", errorCode));
    }

    Logger::writeToLog("callback triggered : service found");

    ZeroConfManager* zManager = (ZeroConfManager*)context;

    String addString  = (flags & kDNSServiceFlagsAdd) ? "ADD" : "REMOVE";
    String moreString = (flags & kDNSServiceFlagsMoreComing) ? "MORE" : "";
    
    ZeroConfService *service = new ZeroConfService();
    
    service->setServiceName(serviceName);
    service->setRegType(regtype);
    service->setAddString(addString);
    service->setMoreString(moreString);
    service->setErrorCode(errorCode);
    service->setReplyDomain(replyDomain);
    service->status = ZeroConfService::ResultStatus::browseResult;

    Logger::writeToLog("addString"  + addString);
    Logger::writeToLog("moreString"  + moreString);

    Logger::writeToLog(String::formatted("Serivce Name: %s",  serviceName));
    Logger::writeToLog(String::formatted("RegType: %s",  regtype));
    Logger::writeToLog(String::formatted("Reply Domain: %s",  replyDomain));

    if(addString.equalsIgnoreCase("ADD")) Logger::writeToLog("Adding service");
    zManager->addService(service);

}

static void zeroResolveCallback(DNSServiceRef sdRef,
                                DNSServiceFlags flags,
                                uint32_t interfaceIndex,
                                DNSServiceErrorType errorCode,
                                const char *fullname,
                                const char *hosttarget,
                                uint16_t port,
                                uint16_t txtLen,
                                const unsigned char *txtRecord,
                                void *context)
{
    ZeroConfService *response = (ZeroConfService *)context;
    
    response->setFullname(fullname);
    response->setHosttarget(hosttarget);
    response->setPort(ntohs(port));
    response->setInterfaceIndex(interfaceIndex);
    response->status = ZeroConfService::ResultStatus::resolveResult;
    response->sdRef = &sdRef;
}

static void zeroRegisterCallback(DNSServiceRef sdRef,
                                DNSServiceFlags flags,
                                DNSServiceErrorType errorCode,
                                const char *serviceName,
                                const char *regtype,
                                const char *domain,
                                void *context)
{
    
    Logger::writeToLog(String::formatted("service %s %s registered", serviceName, regtype));
    
    ZeroConfService *service = new ZeroConfService();
    ZeroConfManager* zManager = (ZeroConfManager*)context;
    
    service->setServiceName(serviceName);
    service->setRegType(regtype);
    service->setErrorCode(errorCode);

    service->sdRef = &sdRef;
    service->status = ZeroConfService::ResultStatus::registerResult;
    
    zManager->addService(service);
}

static void zeroQueryRecordReply(DNSServiceRef       sdRef,
                                 DNSServiceFlags     flags,
                                 uint32_t            interfaceIndex,
                                 DNSServiceErrorType errorCode,
                                 const char*         fullname,
                                 uint16_t            rrtype,
                                 uint16_t            rrclass,
                                 uint16_t            rdlen,
                                 const void*         rdata,
                                 uint32_t            ttl,
                                 void*               context)
{
    ZeroConfService *response = (ZeroConfService *)context;
    response->setFullname(fullname);
    
    const unsigned char *rd  = (const unsigned char *)rdata;
    char rdb[1000] = "";
    
    snprintf(rdb, sizeof(rdb), "%d.%d.%d.%d", rd[0], rd[1], rd[2], rd[3]);
    
    Logger::writeToLog(String(rdb));
    response->setIP( String(rdb) );
    response->status = ZeroConfService::ResultStatus::queryResult;
}

ZeroConfManager::ZeroConfManager( Monitor* socket_monitor, ZeroConfListener* lstnr) : FileDescriptorListener("Zero Conf Manager"), Thread ("ZeroConf Manager Thread") {
    
    this->listener = lstnr;
    monitor = socket_monitor;
    
    this->registerServiceRef = NULL;
    this->browseServiceRef = NULL;
}

ZeroConfManager::~ZeroConfManager()
{
    stopThread(20);
}

void ZeroConfManager::run()
{
    notifyListener();
}

void ZeroConfManager::notifyListener()
{
    listener->handleZeroConfUpdate(&serviceList);
}

void ZeroConfManager::registerService(ZeroConfService *service)
{
    
    const ScopedLock myScopedLock (lock);

    DNSServiceErrorType error;
    
    error = DNSServiceRegister(&registerServiceRef,
                               0,
                               0,
                               service->getServiceName().toRawUTF8(),
                               service->getRegType().toRawUTF8(),
                               NULL,
                               NULL,
                               htons(service->getPort()),
                               0,
                               NULL,
                               zeroRegisterCallback,
                               (void*)this);
    if (error == kDNSServiceErr_NoError) {
        service->sdRef = &registerServiceRef;
        monitor->addFileDescriptorAndListener(this->getRegisterServiceFileDescriptor(), this, String::formatted("register service: %s",service->getServiceName().toRawUTF8()));
    }else {
        fprintf(stderr, "DNSServiceRegister returned %d\n", error);
    }
}

void ZeroConfManager::removeService(ZeroConfService *service)
{
    monitor->removeFileDescriptorAndListener(this->getRegisterServiceFileDescriptor());
}

void ZeroConfManager::browseService(const char * regType)
{
    const ScopedLock myScopedLock (lock);
    DNSServiceErrorType error;
    
    error = DNSServiceBrowse(&browseServiceRef,
            0,                      // no flags
            0,                      // all network interfaces
            regType,                // service type
            "",                     // default domains
            zeroBrowseCallback,     // call back function
            (void*)this);        // no context
    
    if (error == kDNSServiceErr_NoError) {
        Logger::writeToLog(String::formatted("Browsing for service: %s", regType));
        monitor->addFileDescriptorAndListener(this->getBrowseServiceFileDescriptor(), this, String::formatted("browse for service: %s",regType));
        
    }else {
        fprintf(stderr, "DNSServiceDiscovery returned %d\n", error);
    }
}


void ZeroConfManager::handleFileDescriptor(int fileDescriptor)
{
    
    const ScopedLock myScopedLock (lock);
    
    DNSServiceErrorType err = kDNSServiceErr_NoError;
    DNSServiceErrorType error;
    
    ZeroConfService *service;

    
    if (this->registerServiceRef && fileDescriptor == DNSServiceRefSockFD(this->registerServiceRef)) {

        err = DNSServiceProcessResult(this->registerServiceRef);
        return;
    }
    
    if (this->browseServiceRef && fileDescriptor == DNSServiceRefSockFD(this->browseServiceRef)) {

        //Socket for browserServiceRef was triggered
        Logger::writeToLog("Browser service was triggered");

        err = DNSServiceProcessResult(this->browseServiceRef);
        if(err)
        {
            Logger::writeToLog("Could not process result");
            fprintf(stderr, "DNSServiceProcessResult returned %d\n", err);
            return;
        }


        for (int i = 0; i < serviceList.size(); i++) {
            service = serviceList.getUnchecked(i) ;
            if (service->getAddString().equalsIgnoreCase("ADD") && service->status == ZeroConfService::ResultStatus::browseResult) {
                
                if (service->status == ZeroConfService::ResultStatus::browseComplete) {
                    return;
                }
                
                DNSServiceRef *ref = (DNSServiceRef *)calloc (1, sizeof(DNSServiceRef));
                
                //Note: this function does not work with Avahi's compatibility layer
                error = DNSServiceResolve(ref,
                                          0,
                                          0,
                                          service->getServiceName().toRawUTF8(),
                                          service->getRegType().toRawUTF8(),
                                          service->getReplyDomain().toRawUTF8(),
                                          zeroResolveCallback,
                                          (void*)service);
                
                if (error == kDNSServiceErr_NoError) {
                    service->status = ZeroConfService::ResultStatus::browseComplete;
                    service->sdRef = ref;
                    monitor->addFileDescriptorAndListener(DNSServiceRefSockFD(*service->sdRef), this, String::formatted("adding service to resolve: %s",service->getServiceName().toRawUTF8()));
                    
                }else{
                    Logger::writeToLog("Could not set DNSServiceResolve()");
                    fprintf(stderr, "DNSServiceResolve returned %d\n", error);

                }
                
            }else if (service->getAddString().equalsIgnoreCase("REMOVE")){
                
                serviceList.removeObject(service);
                startThread();
            }
        }
        
        return;
    }
    
    for (int i = 0; i < serviceList.size(); i++) {
        if (fileDescriptor == DNSServiceRefSockFD(*serviceList.getUnchecked(i)->sdRef))
        {
            service = serviceList.getUnchecked(i);
            err = DNSServiceProcessResult(*service->sdRef);
            if(err)
            {
                Logger::writeToLog("Could not process result");
                fprintf(stderr, "DNSServiceProcessResult returned %d\n", err);
                return;
            }
            break;
        }
    }
    
    
    if (service->status == ZeroConfService::ResultStatus::resolveResult)
    {
        Logger::writeToLog("Resolving service details");
        DNSServiceRef *ref = (DNSServiceRef *)calloc (1, sizeof(DNSServiceRef));
        
        error =  DNSServiceQueryRecord(ref,
                                       0,
                                       0,
                                       service->getHosttarget().toRawUTF8(),
                                       1,
                                       kDNSServiceClass_IN,
                                       zeroQueryRecordReply,
                                       (void*)service);
        
        if (error == kDNSServiceErr_NoError) {

            monitor->removeFileDescriptorAndListener(fileDescriptor);
            DNSServiceRefDeallocate(*service->sdRef);
            service->sdRef = ref;
            
            monitor->addFileDescriptorAndListener(DNSServiceRefSockFD(*service->sdRef), this, String::formatted("adding record to query: %s",service->getServiceName().toRawUTF8()));
            
        }else{
            fprintf(stderr, "DNSServiceResolve returned %d\n", error);
        }

        return;
        
    }else if(service->status == ZeroConfService::ResultStatus::queryResult)
    {
        Logger::writeToLog("Resolving service ip");
        monitor->removeFileDescriptorAndListener(fileDescriptor);
        DNSServiceRefDeallocate(*service->sdRef);
        startThread();

        return;
        
    }else if(service->status == ZeroConfService::ResultStatus::registerResult)
    {
        return;
    }

    Logger::writeToLog("Should not arrive here");
    monitor->removeFileDescriptorAndListener(fileDescriptor);
    
}

int ZeroConfManager::getBrowseServiceFileDescriptor()
{
    return DNSServiceRefSockFD(browseServiceRef);
}

int ZeroConfManager::getRegisterServiceFileDescriptor()
{
    return DNSServiceRefSockFD(registerServiceRef);
}


OwnedArray<ZeroConfService, CriticalSection> *ZeroConfManager::getServiceList() {
    return &this->serviceList;
}

void ZeroConfManager::addService(ZeroConfService *service) {

    for (int i = 0; i < serviceList.size(); i++) {
        if (*service == *serviceList.getUnchecked(i) ) {
            serviceList.remove(i);
            Logger::writeToLog("Removed Service");
            break;
        }
    }
    serviceList.add(service);
    Logger::writeToLog("Added Service");
}
