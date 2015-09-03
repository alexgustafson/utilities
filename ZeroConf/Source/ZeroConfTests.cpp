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
    beginTest("Browse Test");
    Monitor monitor;
    monitor.startMonitoring();
    
    ZeroConfObserver listener;
    
    ScopedPointer<ZeroConfManager> zeroConfManager = new ZeroConfManager(&monitor, &listener);
    zeroConfManager->browseService("_diapro._udp");
    
    Thread::sleep(2000);
    /*
     Start consolue command:
     dns-sd -R "Mu Shu" _diapro._udp local 9904
    */
    int i = 0;
    while (i < 50) {
        i++;
        Thread::sleep(50);
    }
    
    monitor.stop();
}

void ZeroConfTests::registerTest()
{
    
    beginTest("Register Test");
    Monitor monitor;
    monitor.startMonitoring();
    
    ZeroConfObserver listener;
    
    ScopedPointer<ZeroConfManager> zeroConfManager = new ZeroConfManager(&monitor, &listener);
    zeroConfManager->browseService("_diapro._udp");
    
    Thread::sleep(100);
    ZeroConfObserver registrar;
    ScopedPointer<ZeroConfManager> zeroConfManager2 = new ZeroConfManager(&monitor, &registrar);
    ScopedPointer<ZeroConfService> service = new ZeroConfService();
    
    service->setPort(9905);
    service->setServiceName("Mu Shi");
    service->setRegType("_diapro._udp");
    
    zeroConfManager2->registerService(service);
    
    Thread::sleep(2000);

    int i = 0;
    while (i < 50) {
        i++;
        Thread::sleep(50);
    }
    
    zeroConfManager2->removeService(service);
    Thread::sleep(1000);
    
    monitor.stop();
}

void ZeroConfTests::runTest()
{
    firstTest();
    browseTest();
    registerTest();
}