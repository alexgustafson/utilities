/*
  ==============================================================================

    DiauproProcessor.cpp
    Created: 22 Sep 2015 3:19:42pm
    Author:  Alexander Gustafson

  ==============================================================================
*/

#include "DiauproProcessor.h"

DiauproProcessor::DiauproProcessor() : circularBuffer(41000) {
    tempBuffer = new AudioSampleBuffer(2, 44100);
    socket = new DatagramSocket();
    socket->bindToPort(0);
    activeNode = NULL;
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
        socket->write(targetHost, targetPort, buffer.getReadPointer(0), buffer.getNumChannels() * buffer.getNumSamples() * sizeof(float));
        buffer.clear();

        dataReturned.wait(maxWaitTimeMs);
        socket->read(buffer.getWritePointer(0), buffer.getNumChannels() * buffer.getNumSamples() * sizeof(float), false);  //deadlock here when node disconects

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


void DiauproProcessor::handleFileDescriptor(int fileDescriptor) {

    //int size = socket->read(tempBuffer->getWritePointer(0), tempBuffer->getNumChannels() * tempBuffer->getNumSamples() * sizeof(float), false);
    //int numSamples = size / (tempBuffer->getNumChannels() * sizeof(float));
    //circularBuffer.writeSamples(tempBuffer->getReadPointer(0), numSamples);
    dataReturned.signal();

}

void DiauproProcessor::handleZeroConfUpdate(OwnedArray<ZeroConfService> *serviceList) {

    if (serviceList->size() > 0) {
        activeNode = serviceList->getUnchecked(0);
        targetHost = activeNode->getHosttarget();
        targetPort = activeNode->getPort();
        this->monitor->addFileDescriptorAndListener(this->socket->getRawSocketHandle(), this);
        return;
    }
    serviceList = nullptr;

}


