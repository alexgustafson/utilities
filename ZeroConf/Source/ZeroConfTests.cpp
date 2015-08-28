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
    
    ScopedPointer<ZeroConfManager> zeroConfManager = new ZeroConfManager("_diapro._udp", &monitor);
    
    Thread::sleep(2000);
    /*
     Start consolue command:
     dns-sd -R "Mu Shu" _diapro._udp local 9904
    */
    
    Thread::sleep(18000);
    
    monitor.stop();
}

void ZeroConfTests::runTest()
{
    firstTest();
    browseTest();
}