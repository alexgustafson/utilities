/*
  ==============================================================================

    ConsolidatedTests.cpp
    Created: 3 Oct 2015 12:49:15pm
    Author:  Alexander Gustafson

  ==============================================================================
*/

#include "ConsolidatedTests.h"

void ConsolidatedTests::firstTest()
{
    beginTest("Testing The Tester");
    expect(true);
    expectEquals(true, !false);

    Monitor monitor;
    monitor.startMonitoring();

    ScopedPointer<DiauproTestProcessor> diauproTestProcessor;
    diauproTestProcessor = new DiauproTestProcessor();
    diauproTestProcessor->setMonitor(&monitor);

    diauproTestProcessor->prepareToPlay(22050, 512);

    MidiBuffer midiBuffer;
    midiBuffer.addEvent(MidiMessage::noteOn(1,1,0.7f), 12);
    midiBuffer.addEvent(MidiMessage::noteOn(7,7,0.1f), 12);


    ScopedPointer<AudioSampleBuffer> buffer;
    buffer = new AudioSampleBuffer(1,22);
    
    for (int i = 0; i < buffer->getNumSamples(); i++) {
        buffer->setSample(0, i, ((float)i) * 0.1f);
    }
    

    while (!diauproTestProcessor->hasActiveNetworkConnection())
    {
        Thread::sleep(20);
    }

    diauproTestProcessor->processAudioWrapper(*buffer, midiBuffer);


    while(diauproTestProcessor->data_returned == 0 )
    {
        Thread::sleep(20);
    }

    DiauproMessage* message = diauproTestProcessor->getCurrentMessage();
    MidiBuffer mBuffer;
    message->getMidiData(mBuffer);
    
    Logger::writeToLog("Midi Dump:");
    for(int i = 0; i < midiBuffer.data.size(); i++)
    {
        Logger::writeToLog(String::formatted("  %d", midiBuffer.data[i]));
    }
    Logger::writeToLog("End Midi Dump:");
    
    Logger::writeToLog(message->headerToString());
    
    monitor.stop();
    int i = 10;
    while(i-- > 0 )
    {
        Thread::sleep(20);
    }

}

void ConsolidatedTests::runTest()
{
    firstTest();

}
