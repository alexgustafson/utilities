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

class ZeroConfTests : public UnitTest
{
public:
    ZeroConfTests() : UnitTest("") { pool = new ThreadPool(); }
    void firstTest();
    void browseTest();
    void runTest();
    
private:
    
    class ZeroConfObserver : public ZeroConfListener
    {
    public:
        
        ZeroConfObserver() {};
        
        void handleZeroConfUpdate(OwnedArray<NamedValueSet> *serviceList)
        {
            Logger::writeToLog("notified");
            for (int i = 0; i < serviceList->size(); i++) {
                
                NamedValueSet *service = serviceList->getUnchecked(i);
                for (int j = 0; j < service->size(); j++) {
                    Logger::writeToLog(service->getValueAt(j).toString());
                }
                
                
            }
        };

    private:
    };
    
    ScopedPointer<ThreadPool> pool;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ZeroConfTests)
};
#endif  // ZEROCONFTESTS_H_INCLUDED
