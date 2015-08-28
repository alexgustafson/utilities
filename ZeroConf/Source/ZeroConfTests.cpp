/*
  ==============================================================================

    ZeroConfTests.cpp
    Created: 27 Aug 2015 10:03:10am
    Author:  Alexander Gustafson

  ==============================================================================
*/

#include "ZeroConfTests.h"


void ZeroConfTests::firstTest()
{
    beginTest("Testing The Tester");
    expect(true);
    expectEquals(true, !false);
}

void ZeroConfTests::browseTest()
{
    Monitor monitor;
    monitor.startMonitoring();
    
    ZeroConfObserver listener;
    
    ScopedPointer<ZeroConfManager> zeroConfManager = new ZeroConfManager("_diapro._udp", &monitor, &listener);

    
    Thread::sleep(2000);
    /*
     Start consolue command:
     dns-sd -R "Mu Shu" _diapro._udp local 9904
    */
    int i = 0;
    while (i < 100) {
        i++;
        Thread::sleep(300);
    }
    
    //Thread::sleep(18000);
    
    monitor.stop();
}

void ZeroConfTests::runTest()
{
    firstTest();
    browseTest();
}