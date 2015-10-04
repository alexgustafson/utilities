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
    enum ResultStatus
    {
        initResult,
        browseResult,
        browseComplete,
        resolveResult,
        queryResult,
        registerResult
    };

    int getInterfaceIndex() const {
        return interfaceIndex;
    }

    void setInterfaceIndex(int interfaceIndex) {
        ZeroConfService::interfaceIndex = interfaceIndex;
    }

    DNSServiceFlags getFlags() const {
        return flags;
    }

    void setFlags(DNSServiceFlags flags) {
        ZeroConfService::flags = flags;
    }

    DNSServiceErrorType getErrorCode() const {
        return errorCode;
    }

    void setErrorCode(DNSServiceErrorType errorCode) {
        ZeroConfService::errorCode = errorCode;
    }

    const String &getServiceName() const {
        return serviceName;
    }

    void setServiceName(const String &serviceName) {
        ZeroConfService::serviceName = serviceName;
    }

    const String &getRegType() const {
        return regType;
    }

    void setRegType(const String &regType) {
        ZeroConfService::regType = regType;
    }

    const String &getReplyDomain() const {
        return replyDomain;
    }

    void setReplyDomain(const String &replyDomain) {
        ZeroConfService::replyDomain = replyDomain;
    }

    const String &getFullname() const {
        return fullname;
    }

    void setFullname(const String &fullname) {
        ZeroConfService::fullname = fullname;
    }

    const String &getHosttarget() const {
        return hosttarget;
    }

    void setHosttarget(const String &hosttarget) {
        ZeroConfService::hosttarget = hosttarget;
    }

    const String &getAddString() const {
        return addString;
    }

    void setAddString(const String &addString) {
        ZeroConfService::addString = addString;
    }

    const String &getMoreString() const {
        return moreString;
    }

    void setMoreString(const String &moreString) {
        ZeroConfService::moreString = moreString;
    }

    uint16 getPort() const {
        return port;
    }

    void setPort(uint16 port) {
        ZeroConfService::port = port;
    }
    
    String getIP() const {
        return ip;
    }
    
    void setIP(String _ip) {
        ZeroConfService::ip = _ip;
    }

    bool operator==(const ZeroConfService &rhs) const {
        return
                 serviceName.equalsIgnoreCase(rhs.serviceName)
                        && regType.equalsIgnoreCase(rhs.regType)
                        && replyDomain.equalsIgnoreCase(rhs.replyDomain);
    }

    const char *key() {
        return String(serviceName + "." + regType + "." + replyDomain).toRawUTF8();
    }

    void clear() {
        interfaceIndex = 0;
        flags = 0;
        errorCode = 0;
        serviceName = "";
        regType = "";
        replyDomain = "";
        fullname = "";
        hosttarget = "";
        addString = "";
        moreString = "";
        port = 0;
        ip = "";
        isTaken = false;
        status = ResultStatus::initResult;
    }
    
    DNSServiceRef *sdRef;

    int interfaceIndex;
    DNSServiceFlags flags;
    DNSServiceErrorType errorCode;

    String serviceName = "";
    String regType = "";
    String replyDomain = "";
    String fullname = "";
    String hosttarget = "";
    String addString = "";
    String moreString = "";
    uint16 port = 0;
    String ip = "";
    bool isTaken = false;
    ResultStatus  status;

private:

};

class ZeroConfListener {
public:
    virtual ~ZeroConfListener() {
    };

    virtual void handleZeroConfUpdate(OwnedArray<ZeroConfService, CriticalSection> *serviceList) = 0;
};


class ZeroConfManager : public FileDescriptorListener,
                        private Thread {
public:
    ZeroConfManager(Monitor *socketMonitor, ZeroConfListener *listener);

    ~ZeroConfManager();

    void browseService(const char *regType);

    void registerService(ZeroConfService *service);

    void removeService(ZeroConfService *service);

    void handleFileDescriptor(int fileDescriptor) override;

    int getBrowseServiceFileDescriptor();

    int getRegisterServiceFileDescriptor();

    OwnedArray<ZeroConfService, CriticalSection>* getServiceList();

    void addService(ZeroConfService *service);

private:

    void run() override;

    void notifyListener();

    DNSServiceRef browseServiceRef;
    DNSServiceRef registerServiceRef;

    Monitor *monitor;
                            
    ZeroConfListener *listener;
    OwnedArray<ZeroConfService, CriticalSection> serviceList;
                            
    CriticalSection lock;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ZeroConfManager)
};

#endif  // ZEROCONFMANAGER_H_INCLUDED
