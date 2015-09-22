/*
  ==============================================================================

    AudioProcessorNode.cpp
    Created: 17 Sep 2015 10:45:07am
    Author:  Alexander Gustafson

  ==============================================================================
*/

#include "AudioProcessorNode.h"



AudioProcessorNode::AudioProcessorNode()
{
    
    buffer = new AudioSampleBuffer(2, 1024);
    socket = new DatagramSocket(0);
    socket->bindToPort(0);
    
    fcntl(socket->getRawSocketHandle(), F_SETFL, O_NONBLOCK);

};

void AudioProcessorNode::handleFileDescriptor(int fileDescriptor)
{
    Logger::writeToLog("Data Recieved");
    int bufferSize =buffer->getNumChannels() * buffer->getNumSamples() + sizeof(float);
    bytesRead = socket->read(buffer->getWritePointer(0), bufferSize, false, senderHost, senderPort);
    
    socket->write(senderHost, senderPort, buffer->getReadPointer(0), bytesRead);
    Logger::writeToLog("Data Sent");
    
}

void AudioProcessorNode::handleZeroConfUpdate(OwnedArray<ZeroConfService> *serviceList)
{
    Logger::writeToLog("notified");
};

int AudioProcessorNode::getPort()
{
    return socket->getBoundPort();
}

int AudioProcessorNode::getSock()
{
    return socket->getRawSocketHandle();
}

