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

ZeroConfService response;

static void zeroBrowseCallback(DNSServiceRef sdRef,
                               DNSServiceFlags flags,
                               uint32_t interfaceIndex,
                               DNSServiceErrorType errorCode,
                               const char *serviceName,
                               const char *regtype,
                               const char *replyDomain,
                               void *context)
{
    String addString  = (flags & kDNSServiceFlagsAdd) ? "ADD" : "REMOVE";
    String moreString = (flags & kDNSServiceFlagsMoreComing) ? "MORE" : "";
    
    response.clear();
    response.setServiceName(serviceName);
    response.setRegType(regtype);
    response.setAddString(addString);
    response.setMoreString(moreString);
    response.setErrorCode(errorCode);
    response.setReplyDomain(replyDomain);
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
    response.setFullname(fullname);
    response.setHosttarget(hosttarget);
    response.setPort(ntohs(port));
    response.setInterfaceIndex(interfaceIndex);
}

static void zeroRegisterCallback(DNSServiceRef sdRef,
                                DNSServiceFlags flags,
                                DNSServiceErrorType errorCode,
                                const char *serviceName,
                                const char *regtype,
                                const char *domain,
                                void *context)
{
    response.clear();
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
    response.setFullname(fullname);
    
    const unsigned char *rd  = (const unsigned char *)rdata;
    const unsigned char *end = (const unsigned char *) rdata + rdlen;
    char rdb[1000] = "", *p = rdb;
    snprintf(rdb, sizeof(rdb), "%d.%d.%d.%d", rd[0], rd[1], rd[2], rd[3]);
    
    Logger::writeToLog(String(rdb));
    response.setIP( String(rdb) );
}

ZeroConfManager::ZeroConfManager( Monitor* socket_monitor, ZeroConfListener* lstnr) : FileDescriptorListener("Zero Conf Manager"), Thread ("ZeroConf Manager Thread") {
    
    this->listener = lstnr;
    monitor = socket_monitor;
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
    response.clear();
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
                               NULL);
    if (error == kDNSServiceErr_NoError) {
        monitor->addFileDescriptorAndListener(this->getRegisterServiceFileDescriptor(), this);
    }else {
        fprintf(stderr, "DNSServiceRegister returned %d\n", error);
    }
}
void ZeroConfManager::removeService(ZeroConfService *service)
{
    response.clear();
    monitor->removeFileDescriptorAndListener(this->getRegisterServiceFileDescriptor());
    
}

void ZeroConfManager::browseService(const char * service_type)
{
    response.clear();
    DNSServiceErrorType error;

    error = DNSServiceBrowse(&browseServiceRef,
            0,                // no flags
            0,                // all network interfaces
            service_type,     // service type
            "",               // default domains
            zeroBrowseCallback,   // call back function
            NULL);            // no context
    
    if (error == kDNSServiceErr_NoError) {
        monitor->addFileDescriptorAndListener(this->getBrowseServiceFileDescriptor(), this);
    }else {
        fprintf(stderr, "DNSServiceDiscovery returned %d\n", error);
    }
}


void ZeroConfManager::handleFileDescriptor(int fileDescriptor)
{
    DNSServiceErrorType err = kDNSServiceErr_NoError;
    DNSServiceErrorType error;
    
    if(fileDescriptor == DNSServiceRefSockFD(this->browseServiceRef))
    {
        err = DNSServiceProcessResult(this->browseServiceRef);
        if (response.getAddString().equalsIgnoreCase("ADD")) {
            
            
            error = DNSServiceResolve(&resolveServiceRef,
                                      0,
                                      0,
                                      response.getServiceName().toRawUTF8(),
                                      response.getRegType().toRawUTF8(),
                                      response.getReplyDomain().toRawUTF8(),
                                      zeroResolveCallback,
                                      NULL);
            
            if (error == kDNSServiceErr_NoError) {

                monitor->addFileDescriptorAndListener(this->getResolveServiceFileDescriptor(), this);
                ZeroConfService *s = new ZeroConfService(response);
                serviceList.add(s);
                
            }
        }else if (response.getAddString().equalsIgnoreCase("REMOVE")){
            for (int i = 0; i < serviceList.size(); i++) {
                ZeroConfService *service = serviceList.getUnchecked(i);
                if (*service == response)
                {
                    serviceList.removeObject(service);
                    break;
                }
            }
            startThread();
        }
        
    }else if (fileDescriptor == DNSServiceRefSockFD(this->resolveServiceRef))
    {
        
        err = DNSServiceProcessResult(this->resolveServiceRef);
        
        for (int i = 0; i < serviceList.size(); i++) {
            ZeroConfService *service = serviceList.getUnchecked(i);
            if (*service == response)
            {
                serviceList.removeObject(service);
                break;
            }
        }

        
        DNSServiceFlags flags;
        //flags = kDNSServiceFlagsShareConnection;
        
        error =  DNSServiceQueryRecord(&queryServiceRef,
                                       0,
                                       0,
                                       response.getHosttarget().toRawUTF8(),
                                       1,
                                       kDNSServiceClass_IN,
                                       zeroQueryRecordReply,
                                       NULL);
        
        if (error == kDNSServiceErr_NoError) {
            
            ZeroConfService *s = new ZeroConfService(response);
            serviceList.add(s);
            monitor->removeFileDescriptorAndListener(fileDescriptor);
            DNSServiceRefDeallocate(this->resolveServiceRef);
            monitor->addFileDescriptorAndListener(this->getQueryServiceFileDescriptor(), this);
            
        }

        
    }else if(fileDescriptor == DNSServiceRefSockFD(this->queryServiceRef))
    {
        err = DNSServiceProcessResult(this->queryServiceRef);
        
        for (int i = 0; i < serviceList.size(); i++) {
            ZeroConfService *service = serviceList.getUnchecked(i);
            if (*service == response)
            {
                serviceList.removeObject(service);
                break;
            }
        }
        
        monitor->removeFileDescriptorAndListener(fileDescriptor);
        DNSServiceRefDeallocate(this->queryServiceRef);
        ZeroConfService *s = new ZeroConfService(response);
        serviceList.add(s);
        
        startThread();
        
    }else if(fileDescriptor == DNSServiceRefSockFD(this->registerServiceRef))
    {
        err = DNSServiceProcessResult(this->registerServiceRef);
    }
}

int ZeroConfManager::getBrowseServiceFileDescriptor()
{
    return DNSServiceRefSockFD(browseServiceRef);
}

int ZeroConfManager::getResolveServiceFileDescriptor()
{
    return DNSServiceRefSockFD(resolveServiceRef);
}
int ZeroConfManager::getRegisterServiceFileDescriptor()
{
    return DNSServiceRefSockFD(registerServiceRef);
}

int ZeroConfManager::getQueryServiceFileDescriptor()
{
    return DNSServiceRefSockFD(queryServiceRef);

}



