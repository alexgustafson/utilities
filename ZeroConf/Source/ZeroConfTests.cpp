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
    
    service->setPort((uint16)(9905));
    service->setServiceName("Mu Shi");
    service->setRegType("_diapro._udp");
    
    ZeroConfObserver registrar2;
    ScopedPointer<ZeroConfManager> zeroConfManager3 = new ZeroConfManager(&monitor, &registrar2);
    ScopedPointer<ZeroConfService> service2 = new ZeroConfService();
    
    service2->setPort((uint16)(32320));
    service2->setServiceName("Mi Shu");
    service2->setRegType("_diapro._udp");
    
    zeroConfManager2->registerService(service);
    zeroConfManager3->registerService(service2);
    
    int i = 0;
    while (i < 150) {
        i++;
        Thread::sleep(50);
    }
    
    zeroConfManager2->removeService(service);
    zeroConfManager3->removeService(service2);
    Thread::sleep(1000);
    
    monitor.stop();
}

void ZeroConfTests::runTest()
{
    //firstTest();
    browseTest();
    registerTest();
}