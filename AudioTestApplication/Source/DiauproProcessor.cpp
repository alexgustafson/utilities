/*
  ==============================================================================

    DiauproProcessor.cpp
    Created: 22 Sep 2015 3:19:42pm
    Author:  Alexander Gustafson

  ==============================================================================
*/

#include "DiauproProcessor.h"

#include <netinet/in.h>
#include <arpa/inet.h>


DiauproProcessor::DiauproProcessor() :  circularBuffer(41000) {
    tempBuffer = new AudioSampleBuffer(2, 44100);
    socket = new DatagramSocket(0);
    socket->bindToPort(0);
    activeNode = nullptr;
}

DiauproProcessor::~DiauproProcessor() {

}

void DiauproProcessor::setMonitor(Monitor *monitor) {

    this->monitor = monitor;
    this->zManager = new ZeroConfManager(monitor, this);
    this->zManager->browseService("_diapro._udp");
}

bool DiauproProcessor::hasEditor() const {
    return false;
}

void DiauproProcessor::prepareToPlay(double sampleRate, int estimatedSamplesPerBlock) {

    maxWaitTimeMs = (estimatedSamplesPerBlock / sampleRate) * 1000;

}

void DiauproProcessor::getStateInformation(MemoryBlock &destData) {

}

const String DiauproProcessor::getInputChannelName(int channelIndex) const {
    return String();
}

AudioProcessorEditor *DiauproProcessor::createEditor() {
    return nullptr;
}

void DiauproProcessor::processBlock(AudioSampleBuffer &buffer, MidiBuffer &midiMessages) {

    if (activeNode != nullptr) {
        if (socket->waitUntilReady(false, maxWaitTimeMs)) {
            bytesRead = socket->write(targetHost, targetPort, buffer.getReadPointer(0), buffer.getNumChannels() * buffer.getNumSamples() * sizeof(float));
            Logger::writeToLog(String::formatted("Bytes Sent: %d", bytesRead));
            

            /*
            int result;
            
            struct sockaddr_in ip4addr;
            char s[INET6_ADDRSTRLEN];
            
            ip4addr.sin_family = AF_INET;
            ip4addr.sin_port = htons(targetPort);
            inet_pton(AF_INET, targetHost.toRawUTF8(), &ip4addr.sin_addr);
            
            //inet_ntop(AF_INET, &ip4addr.sin_addr, s, sizeof(s));
            
            //Logger::writeToLog(String::formatted("Attept seind to: %d %s", ntohs(ip4addr.sin_port), s ));
            
            result = sendto(socket->getRawSocketHandle(), buffer.getReadPointer(0), buffer.getNumChannels() * buffer.getNumSamples() * sizeof(float), 0, (struct sockaddr*)&ip4addr, sizeof(ip4addr));
             */
            

            if (bytesRead < 0) {
                printf("sendto() returned %d errno %d %s\n", bytesRead, errno, strerror(errno));
                return;
            }
        }

        buffer.clear();

        bytesRead = 0;
        if (socket->waitUntilReady(true, maxWaitTimeMs)) {
            bytesRead = socket->read(buffer.getWritePointer(0), buffer.getNumChannels() * buffer.getNumSamples() * sizeof(float), false);
        }

    } else {

        //do local processing

    }
}

bool DiauproProcessor::isOutputChannelStereoPair(int index) const {
    return false;
}

void DiauproProcessor::setCurrentProgram(int index) {

}

bool DiauproProcessor::isInputChannelStereoPair(int index) const {
    return false;
}

void DiauproProcessor::changeProgramName(int index, const String &newName) {

}

int DiauproProcessor::getNumPrograms() {
    return 0;
}

const String DiauproProcessor::getProgramName(int index) {
    return String();
}

void DiauproProcessor::releaseResources() {

}

bool DiauproProcessor::silenceInProducesSilenceOut() const {
    return false;
}

int DiauproProcessor::getCurrentProgram() {
    return 0;
}

const String DiauproProcessor::getName() const {
    return String();
}

const String DiauproProcessor::getOutputChannelName(int channelIndex) const {
    return String();
}

void DiauproProcessor::setStateInformation(const void *data, int sizeInBytes) {

}

double DiauproProcessor::getTailLengthSeconds() const {
    return 0;
}

bool DiauproProcessor::producesMidi() const {
    return false;
}

bool DiauproProcessor::acceptsMidi() const {
    return false;
}


void DiauproProcessor::handleZeroConfUpdate(OwnedArray<ZeroConfService> *serviceList) {

    if (serviceList->size() > 0) {
        
        activeNode = serviceList->getUnchecked(0);
        targetHost = activeNode->ip;
        targetPort = activeNode->getPort();

        Logger::writeToLog(String::formatted("Node Found on %s:%d interface %d", targetHost.toRawUTF8(), targetPort, activeNode->getInterfaceIndex()));
        return;
    }
    this->activeNode = nullptr;
    Logger::writeToLog("Node Lost");

}


