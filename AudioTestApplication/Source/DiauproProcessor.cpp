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


DiauproProcessor::DiauproProcessor() {
    socket = new DatagramSocket(0);
    message = new DiauproMessage(65000, false);
    socket->bindToPort(0);
    activeNode = nullptr;
}

DiauproProcessor::~DiauproProcessor() {

}

void DiauproProcessor::setMonitor(Monitor *monitor) {

    this->monitor = monitor;
    this->zManager = new ZeroConfManager(monitor, this);
    this->zManager->browseService(service_tag.toRawUTF8());
}

bool DiauproProcessor::hasEditor() const {
    return false;
}

void DiauproProcessor::prepareToPlay(double sampleRate, int estimatedSamplesPerBlock) {

    this->sampleRate = sampleRate;
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

    if (!midiMessages.isEmpty()) {
        Logger::writeToLog("has midi sent");
    }

    if (activeNode != nullptr) {
        if (socket->waitUntilReady(false, maxWaitTimeMs)) {
            message->setAudioData(&buffer);
            message->setMidiData(&midiMessages);
            message->setSampleRate(sampleRate);
            bytesRead = socket->write(targetHost, targetPort, message->getData(), message->getSize());

            if (bytesRead < 0) {
                printf("sendto() returned %d errno %d %s\n", bytesRead, errno, strerror(errno));
                return;
            }
        }

        buffer.clear();

        bytesRead = 0;
        if (socket->waitUntilReady(true, maxWaitTimeMs)) {

            bytesRead = message->readFromSocket(socket);
            message->getAudioData(&buffer);

            MidiBuffer tempBuffer;
            message->getMidiData(tempBuffer);

            MidiBuffer::Iterator iterator(tempBuffer);
            MidiMessage tempMessage;
            int sampleIndex;
            if (!tempBuffer.isEmpty()) {
                Logger::writeToLog("has midi returned");

                while (iterator.getNextEvent(tempMessage, sampleIndex)) {
                    Logger::writeToLog(String::formatted("midi note: %d", tempMessage.getNoteNumber()));
                }
            }
        }

    } else {

        localProcess(buffer, midiMessages);

    }
}

void DiauproProcessor::localProcess(AudioSampleBuffer &buffer, MidiBuffer &midiMessages) {


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


