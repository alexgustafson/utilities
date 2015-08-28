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


class ZeroConfManager : public FileDescriptorListener
{
public:
    ZeroConfManager(const char * service_type, Monitor* socketMonitor);
    ~ZeroConfManager();
    
    void handleFileDescriptor(int fileDescriptor);
    int getBrowseServiceFileDescriptor();
    int getResolveServiceFileDescriptor();
    
private:
    DNSServiceRef  browseServiceRef;
    DNSServiceRef  resolveServiceRef;
    int zeroconf_socket;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ZeroConfManager)
    NamedValueSet browserResponse;
    Monitor *monitor;
    Array<NamedValueSet> serviceBrowserResults;
    Array<NamedValueSet> serviceResolverResults;
};

#endif  // ZEROCONFMANAGER_H_INCLUDED
