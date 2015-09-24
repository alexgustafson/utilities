/*
  ==============================================================================

    AudioProcessorNode.cpp
    Created: 17 Sep 2015 10:45:07am
    Author:  Alexander Gustafson

  ==============================================================================
*/

#include "AudioProcessorNode.h"
#include <netinet/in.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/select.h>


AudioProcessorNode::AudioProcessorNode() : FileDescriptorListener("Audio Processor Node")
{
    
    buffer = new AudioSampleBuffer(2, 1024);
    //socket = new DatagramSocket(0);
    //socket->bindToPort(0);
    
    //fcntl(socket->getRawSocketHandle(), F_SETFL, O_NONBLOCK);
    
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in sin;
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = 0;
    sin.sin_port = 0;
    
    int result;
    result = bind(sock, (struct sockaddr*)&sin, sizeof(sin));
    
    if (result < 0) {
        printf("bind() returned %d errno %d %s\n", result, errno, strerror(errno));
        return;
    }
    
    fcntl(sock, F_SETFL, O_NONBLOCK);
    int one = 1;
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one));

};

void AudioProcessorNode::handleFileDescriptor(int fileDescriptor)
{
    Logger::writeToLog("packets received");
    int bufferSize = buffer->getNumChannels() * buffer->getNumSamples() + sizeof(float);
    //bytesRead = socket->read(buffer->getWritePointer(0), bufferSize, false, senderHost, senderPort);
    struct sockaddr sender;
    socklen_t sendsize = sizeof(sender);
    bytesRead = recvfrom(sock, buffer->getWritePointer(0), bufferSize, 0, &sender, &sendsize);
    
    //socket->write(senderHost, senderPort, buffer->getReadPointer(0), bytesRead);
    sendto(sock, buffer->getReadPointer(0), bytesRead, 0, (struct sockaddr *)&sender, sendsize);
}

void AudioProcessorNode::handleZeroConfUpdate(OwnedArray<ZeroConfService> *serviceList)
{
    Logger::writeToLog("notified");
};

int AudioProcessorNode::getPort()
{
    //return socket->getBoundPort();
    struct sockaddr_in sin_addr;
    socklen_t len = sizeof (sin_addr);
    getsockname (sock, (struct sockaddr*) &sin_addr, &len);
    
    return ntohs (sin_addr.sin_port);
}

int AudioProcessorNode::getSock()
{
    //return socket->getRawSocketHandle();
    
    return sock;
}

