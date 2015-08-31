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
    response.serviceName =  serviceName;
    response.regType = regtype;
    response.addString =  addString;
    response.moreString =  moreString;
    response.errorCode =  errorCode;
    response.replyDomain =  replyDomain;

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

    response.fullname=  fullname;
    response.hosttarget =  hosttarget;
    response.port =  port;

}

ZeroConfManager::ZeroConfManager(const char * service_type, Monitor* socket_monitor, ZeroConfListener* lstnr) : Thread ("ZeroConf Manager Thread") {
    
    this->listener = lstnr;
    monitor = socket_monitor;
    
    DNSServiceErrorType error;
    
    error = DNSServiceBrowse(&browseServiceRef,
                             0,                // no flags
                             0,                // all network interfaces
                             service_type,     // service type
                             "",               // default domains
                             zeroBrowseCallback,   // call back function
                             NULL);            // no context
    
    
    monitor->addFileDescriptorAndListener(this->getBrowseServiceFileDescriptor(), this);
}

ZeroConfManager::~ZeroConfManager()
{
    stopThread(20);
}

void ZeroConfManager::handleFileDescriptor(int fileDescriptor)
{
    Logger::writeToLog("ZeroConf Manager is handling it's file descriptor");
    DNSServiceErrorType err = kDNSServiceErr_NoError;
    DNSServiceErrorType error;
    
    if(fileDescriptor == DNSServiceRefSockFD(browseServiceRef))
    {
        err = DNSServiceProcessResult(this->browseServiceRef);
        if (response.addString.equalsIgnoreCase("ADD")) {
            
            Logger::writeToLog("DNSServiceBrowser Found A Match");
            error = DNSServiceResolve(&resolveServiceRef,
                                      0,
                                      0,
                                      response.serviceName.toRawUTF8(),
                                      response.regType.toRawUTF8(),
                                      response.replyDomain.toRawUTF8(),
                                      zeroResolveCallback,
                                      NULL);
            
            if (error == kDNSServiceErr_NoError) {
                Logger::writeToLog("Attempting to Resolve Service");
                monitor->addFileDescriptorAndListener(this->getResolveServiceFileDescriptor(), this);
                serviceList.add(new ZeroConfService(response));

            }
        }else if (response.addString.equalsIgnoreCase("REMOVE")){
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
        
    }else if (fileDescriptor == DNSServiceRefSockFD(resolveServiceRef))
    {
  
        err = DNSServiceProcessResult(this->resolveServiceRef);
        Logger::writeToLog("serviceName: " + response.serviceName);
        Logger::writeToLog("regType: " + response.regType);
        Logger::writeToLog("replyDomain: " + response.replyDomain);
        
        for (int i = 0; i < serviceList.size(); i++) {
            ZeroConfService *service = serviceList.getUnchecked(i);
            if (*service == response)
            {
                serviceList.removeObject(service);
                
                break;
            }
        }
        serviceList.add(new ZeroConfService(response));

        startThread();
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

void ZeroConfManager::run()
{
    notifyListener();
}

void ZeroConfManager::notifyListener()
{
    listener->handleZeroConfUpdate(&serviceList);
}
