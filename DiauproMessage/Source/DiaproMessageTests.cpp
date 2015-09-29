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

    ScopedPointer<DiauproMessage> sourceMessage;
    sourceMessage = new DiauproMessage(65000);
    sourceMessage->setAudioData(&sourceBuffer);

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

    expectEquals(sourceMessage->getNumberChannels(), 2);
    expectEquals(destinationMessage->getNumberChannels(), 2);
    expectEquals(sourceMessage->getNumberSamples(), 20);
    expectEquals(destinationMessage->getNumberSamples(), 20);

    for(int i = 0; i < sourceBuffer.getNumChannels(); i++)
    {
        for(int j = 0; j < sourceBuffer.getNumSamples(); j++)
        {
            expectEquals(sourceBuffer.getSample(i, j), destinationBuffer.getSample(i,j));
        }
    }
}

void DiauproMessageTest::runTest() {
    firstTest();
    secondTest();
}
