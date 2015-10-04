/*
  ==============================================================================

    DiaproMessageTests.cpp
    Created: 26 Sep 2015 2:10:47pm
    Author:  Alexander Gustafson

  ==============================================================================
*/

#include "DiaproMessageTests.h"

void DiauproMessageTest::firstTest() {
    beginTest("Testing The Tester");
    expect(true);
    expectEquals(true, !false);
}

void DiauproMessageTest::secondTest() {
    beginTest("simple serialize test");

    DatagramSocket sendingSocket;
    DatagramSocket recievingSocket;

    sendingSocket.bindToPort(0);
    recievingSocket.bindToPort(0);


    AudioSampleBuffer sourceBuffer(2, 20);
    AudioSampleBuffer destinationBuffer(2, 20);
    destinationBuffer.clear();

    for(int i = 0; i < sourceBuffer.getNumChannels(); i++)
    {
        for(int j = 0; j < sourceBuffer.getNumSamples(); j++)
        {
            sourceBuffer.setSample(i, j, ((float)j)*0.2f );
        }
    }

    ScopedPointer<DiauproMessage> sourceMessage;
    sourceMessage = new DiauproMessage(65000);
    sourceMessage->setAudioData(&sourceBuffer);
    sourceMessage->setSequenceNumber(221);

    if(sendingSocket.waitUntilReady(false, 500))
    {
        sendingSocket.write("0.0.0.0", recievingSocket.getBoundPort(),sourceMessage->getData(), sourceMessage->getSize());
    }

    ScopedPointer<DiauproMessage> destinationMessage;
    destinationMessage = new DiauproMessage(65000);

    if(recievingSocket.waitUntilReady(true, 500))
    {
        destinationMessage->readFromSocket(&recievingSocket);
        destinationMessage->getAudioData(&destinationBuffer);
    }

    expectEquals(sourceMessage->getNumberChannels(), (uint16)2);
    expectEquals(destinationMessage->getNumberChannels(), (uint16)2);
    expectEquals(sourceMessage->getNumberSamples(), (uint16)20);
    expectEquals(destinationMessage->getNumberSamples(), (uint16)20);
    expectEquals(destinationMessage->getSequeceNumber(), (uint16)221);

    for(int i = 0; i < sourceBuffer.getNumChannels(); i++)
    {
        for(int j = 0; j < sourceBuffer.getNumSamples(); j++)
        {
            expectEquals(destinationBuffer.getSample(i,j), sourceBuffer.getSample(i, j));
        }
    }
}

void DiauproMessageTest::thirdTest()
{
    beginTest("simple serialize test with midi");

    DatagramSocket sendingSocket;
    DatagramSocket recievingSocket;

    sendingSocket.bindToPort(0);
    recievingSocket.bindToPort(0);

    int recievingPort = sendingSocket.getBoundPort();

    AudioSampleBuffer sourceBuffer(2, 20);
    AudioSampleBuffer destinationBuffer(2, 20);
    destinationBuffer.clear();

    for(int i = 0; i < sourceBuffer.getNumChannels(); i++)
    {
        for(int j = 0; j < sourceBuffer.getNumSamples(); j++)
        {
            sourceBuffer.setSample(i, j, (float)i+1 * j );
        }
    }

    MidiBuffer sourceMidiBuffer;
    MidiBuffer destinationMidiBuffer;

    for(int i = 0; i < 16; i++)
    {
        sourceMidiBuffer.addEvent(MidiMessage::noteOn(i+1, i,(float)i), i);
        Logger::writeToLog(String::formatted("midiBufferSize: %d",sourceMidiBuffer.data.size() * sizeof(uint8)));
    }

    ScopedPointer<DiauproMessage> sourceMessage;
    sourceMessage = new DiauproMessage(65000);
    sourceMessage->setAudioData(&sourceBuffer);
    sourceMessage->setMidiData(&sourceMidiBuffer);
    sourceMessage->setSequenceNumber(221);

    if(sendingSocket.waitUntilReady(false, 500))
    {
        sendingSocket.write("0.0.0.0", recievingSocket.getBoundPort(),sourceMessage->getData(), sourceMessage->getSize());
    }

    ScopedPointer<DiauproMessage> destinationMessage;
    destinationMessage = new DiauproMessage(65000);

    if(recievingSocket.waitUntilReady(true, 500))
    {
        destinationMessage->readFromSocket(&recievingSocket);
        destinationMessage->getAudioData(&destinationBuffer);
        destinationMessage->getMidiData(destinationMidiBuffer);
    }

    expectEquals(sourceMessage->getNumberChannels(), (uint16)2);
    expectEquals(destinationMessage->getNumberChannels(), (uint16)2);
    expectEquals(sourceMessage->getNumberSamples(), (uint16)20);
    expectEquals(destinationMessage->getNumberSamples(), (uint16)20);
    expectEquals(destinationMessage->getSequeceNumber(), (uint16)221);

    for(int i = 0; i < sourceBuffer.getNumChannels(); i++)
    {
        for(int j = 0; j < sourceBuffer.getNumSamples(); j++)
        {
            expectEquals(sourceBuffer.getSample(i, j), destinationBuffer.getSample(i,j));
        }
    }

    MidiMessage msg;
    int sampleIndex;
    MidiBuffer::Iterator iterator(destinationMidiBuffer);
    int i = 0;
    while(iterator.getNextEvent(msg, sampleIndex))
    {
        expectEquals(msg.getNoteNumber(), i);
        expectEquals(msg.getChannel(), i + 1);
        Logger::writeToLog(String::formatted("recieved note: %d on channel %d",msg.getNoteNumber(), msg.getChannel()));
        i++;
    }

}

void DiauproMessageTest::runTest() {
    firstTest();
    secondTest();
    thirdTest();
}
