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

class ZeroConfListener {
public:
    //virtual ~ZeroConfListener();
    virtual void handleZeroConfUpdate(OwnedArray<NamedValueSet> *serviceList) = 0;
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
    
    void run () override;
    
private:
    DNSServiceRef  browseServiceRef;
    DNSServiceRef  resolveServiceRef;
    
    NamedValueSet browseResponse;
    NamedValueSet resolveResponse;
    
    Monitor *monitor;
    
    ZeroConfListener* listener;
    OwnedArray<NamedValueSet> serviceList;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ZeroConfManager)
};

#endif  // ZEROCONFMANAGER_H_INCLUDED
