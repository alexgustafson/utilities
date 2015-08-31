/*
  ==============================================================================

    ZeroConfManager.h
    Created: 27 Aug 2015 11:17:34am
    Author:  Alexander Gustafson

  ==============================================================================
*/

#ifndef ZEROCONFMANAGER_H_INCLUDED
#define ZEROCONFMANAGER_H_INCLUDED
#include "Monitor.h"
#include "JuceHeader.h"
#include <dns_sd.h>


class ZeroConfService {
public:
    uint32_t interfaceIndex;
    DNSServiceFlags flags;
    DNSServiceErrorType errorCode;
    
    String serviceName = "";
    String regType = "";
    String replyDomain = "";
    String fullname = "";
    String hosttarget = "";
    String addString = "";
    String moreString = "";
    uint16_t port = 0;
    
    bool operator==(const ZeroConfService& rhs) const {
        return
            serviceName == rhs.serviceName
        && regType == rhs.regType
        && replyDomain == rhs.replyDomain;

    }
    
    const char* key() {
        return String(serviceName + "." + regType + "." + replyDomain).toRawUTF8();
    }
    
    void clear() {
        interfaceIndex = 0;
        flags = 0;
        errorCode= 0;
        
        serviceName = "";
        regType = "";
        replyDomain = "";
        fullname = "";
        hosttarget = "";
        addString = "";
        moreString = "";
        port = 0;
        
    }
    
private:
};

class ZeroConfListener {
public:
    virtual ~ZeroConfListener() {};
    virtual void handleZeroConfUpdate(OwnedArray<ZeroConfService> *serviceList) = 0;
};


class ZeroConfManager : public FileDescriptorListener,
                        private Thread
{
public:
    ZeroConfManager(const char * service_type, Monitor* socketMonitor, ZeroConfListener* listener);
    ~ZeroConfManager();
    
    void handleFileDescriptor(int fileDescriptor);
    int getBrowseServiceFileDescriptor();
    int getResolveServiceFileDescriptor();
    
private:
    
    void run () override;
    void notifyListener();
    
    DNSServiceRef  browseServiceRef;
    DNSServiceRef  resolveServiceRef;
    
    NamedValueSet browseResponse;
    NamedValueSet resolveResponse;
    
    Monitor *monitor;
    
    ZeroConfListener* listener;
    OwnedArray<ZeroConfService> serviceList;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ZeroConfManager)
};

#endif  // ZEROCONFMANAGER_H_INCLUDED
