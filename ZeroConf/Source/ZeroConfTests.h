/*
  ==============================================================================

    ZeroConfTests.h
    Created: 27 Aug 2015 10:03:10am
    Author:  Alexander Gustafson

  ==============================================================================
*/

#ifndef ZEROCONFTESTS_H_INCLUDED
#define ZEROCONFTESTS_H_INCLUDED
#include "JuceHeader.h"
#include "ZeroConfManager.h"
#include "Monitor.h"
#include <inttypes.h>


class ZeroConfTests : public UnitTest
{
public:
    ZeroConfTests() : UnitTest("") {  }
    void firstTest();
    void browseTest();
    void registerTest();
    void runTest();
    
private:
    
class ZeroConfObserver : public ZeroConfListener
{
public:
        
        ZeroConfObserver() {};
        ~ZeroConfObserver() {};
        
        void handleZeroConfUpdate(OwnedArray<ZeroConfService, CriticalSection> *serviceList)
        {
            Logger::writeToLog("notified");
            for (int i = 0; i < serviceList->size(); i++) {
                
                ZeroConfService *service = serviceList->getUnchecked(i);
                String status = service->status == ZeroConfService::ResultStatus::queryResult ? "final" : "unfinished";
                Logger::writeToLog(String::formatted("Found service %s %s %s:%d %s",service->getRegType().toRawUTF8(), service->getServiceName().toRawUTF8(),service->ip.toRawUTF8(), service->getPort(), status.toRawUTF8() ));
            }
        };

private:
};
    

JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ZeroConfTests)
};
#endif  // ZEROCONFTESTS_H_INCLUDED
