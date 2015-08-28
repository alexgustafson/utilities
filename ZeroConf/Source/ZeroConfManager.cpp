/*
  ==============================================================================

    ZeroConfManager.cpp
    Created: 27 Aug 2015 11:17:34am
    Author:  Alexander Gustafson

  ==============================================================================
*/

#include "ZeroConfManager.h"

NamedValueSet response;

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
    response.set("serviceName", serviceName);
    response.set("regtype", regtype);
    response.set("replyDomain", replyDomain);
    response.set("addString", addString);
    response.set("moreString", moreString);
    response.set("errorCode", errorCode);
    
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

    response.set("fullname", fullname);
    response.set("hosttarget", hosttarget);
    response.set("port", port);
    response.set("txtLen", txtLen);
    response.set("txtRecord", txtRecord);
    
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

}



void ZeroConfManager::handleFileDescriptor(int fileDescriptor)
{
    Logger::writeToLog("ZeroConf Manager is handling it's file descriptor");
    DNSServiceErrorType err = kDNSServiceErr_NoError;
    DNSServiceErrorType error;
    
    if(fileDescriptor == DNSServiceRefSockFD(browseServiceRef))
    {
        err = DNSServiceProcessResult(this->browseServiceRef);
        if (response.getVarPointer("addString")->toString().equalsIgnoreCase("ADD")) {
            
            Logger::writeToLog("DNSServiceBrowser Found A Match");
            error = DNSServiceResolve(&resolveServiceRef,
                                      0,
                                      0,
                                      response.getVarPointer("serviceName")->toString().toRawUTF8(),
                                      response.getVarPointer("regtype")->toString().toRawUTF8(),
                                      response.getVarPointer("replyDomain")->toString().toRawUTF8(),
                                      zeroResolveCallback,
                                      NULL);
            
            if (error == kDNSServiceErr_NoError) {
                Logger::writeToLog("Attempting to Resolve Service");
                monitor->addFileDescriptorAndListener(this->getResolveServiceFileDescriptor(), this);
            }
        }
        
    }else if (fileDescriptor == DNSServiceRefSockFD(resolveServiceRef))
    {
        err = DNSServiceProcessResult(this->resolveServiceRef);
        Logger::writeToLog(response.getVarPointer("fullname")->toString());
        Logger::writeToLog(response.getVarPointer("hosttarget")->toString());
        Logger::writeToLog(response.getVarPointer("port")->toString());
            
        serviceList.add(new NamedValueSet(response));
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
    listener->handleZeroConfUpdate(&serviceList);
}
