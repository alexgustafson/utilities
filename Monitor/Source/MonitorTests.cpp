/*
  ==============================================================================

    MonitorTests.cpp
    Created: 9 Aug 2015 1:32:09pm
    Author:  Alexander Gustafson

  ==============================================================================
*/

#include "MonitorTests.h"

void MonitorTests::firstTest()
{
    beginTest("Testing The Tester");
    expect(true);
    expectEquals(true, !false);
}

void MonitorTests::startUpAndShutDownTest()
{
    beginTest("Start Up and Shut Down Test");

    Monitor monitor;
    monitor.startMonitoring();
    
    Thread::sleep(200);
    
    monitor.stop();
    
    Thread::sleep(100); // wait for thread to stop
    
}

void MonitorTests::callBackTest()
{
    
    beginTest("CallBack Test");
    
    Monitor monitor;
    monitor.startMonitoring();
    
    ScopedPointer<SocketListener> listener = new SocketListener();
    listener->initializeSockets(40780, &monitor, "quark");
    
    pool->addJob(listener, false);
    
    while(pool->getNumJobs() > 0 )
    {
        Thread::sleep(5);
    }
    
    monitor.stop();
    expectEquals(true, listener->was_informed);

    
}

void MonitorTests::multiThreadedCallBackTest()
{
    beginTest("Concurrent CallBack Test");
    
    Monitor monitor;
    monitor.startMonitoring();
    
    
    OwnedArray<SocketListener> listeners;
    
    for (int i = 0; i < 50 ; i++) {
        SocketListener* listener = new SocketListener();
        listener->initializeSockets((40780 + (5*i)), &monitor, String("quassel") + String(i*20));
        listeners.add(listener);
    }
    
    for (int i = 0; i < 50 ; i++) {
        pool->addJob(listeners[i], false);
    }
    
    while(pool->getNumJobs() > 0 )
    {
        Thread::sleep(20);
    }
    
    monitor.stop();
    for (int i = 0; i < 50 ; i++) {
        
        expectEquals(listeners[i]->was_informed , true);
        
    }
    
}

void MonitorTests::runTest()
{
    firstTest();
    startUpAndShutDownTest();
    callBackTest();
    multiThreadedCallBackTest();
}
