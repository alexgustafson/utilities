/*
  ==============================================================================

    ZeroConfManager.cpp
    Created: 27 Aug 2015 11:17:34am
    Author:  Alexander Gustafson

  ==============================================================================
*/

#include "ZeroConfManager.h"


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
    response.setInterfaceIndex(ntohl(interfaceIndex));
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
                serviceList.add(new ZeroConfService(response));
                
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
        monitor->removeFileDescriptorAndListener(fileDescriptor);
        DNSServiceRefDeallocate(this->resolveServiceRef);
        serviceList.add(new ZeroConfService(response));
        
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

