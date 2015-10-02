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


AudioProcessorNode::AudioProcessorNode() : FileDescriptorListener("Audio Processor Node") {

    buffer = new AudioSampleBuffer(2, 1024);
    message = new DiauproMessage(65000, false);
    socket = new DatagramSocket(0);
    int result = socket->bindToPort(0);

    if (result < 0) {
        printf("bind() returned %d errno %d %s\n", result, errno, strerror(errno));
        return;
    }

    sock = socket->getRawSocketHandle();

    fcntl(sock, F_SETFL, O_NONBLOCK);
    int one = 1;
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one));

};

void AudioProcessorNode::handleFileDescriptor(int fileDescriptor) {
    Logger::writeToLog("packets received");

    bytesRead = message->readFromSocket(socket, senderHost, senderPort);

    socket->write(senderHost, senderPort, message->getData(), message->getSize());

}

void AudioProcessorNode::handleZeroConfUpdate(OwnedArray<ZeroConfService> *serviceList) {
    Logger::writeToLog("notified");
};

int AudioProcessorNode::getPort() {
    struct sockaddr_in sin_addr;
    socklen_t len = sizeof(sin_addr);
    getsockname(sock, (struct sockaddr *) &sin_addr, &len);

    return ntohs (sin_addr.sin_port);
}

int AudioProcessorNode::getSock() {
    return sock;
}

