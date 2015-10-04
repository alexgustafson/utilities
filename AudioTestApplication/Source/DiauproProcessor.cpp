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


DiauproProcessor::DiauproProcessor() : FileDescriptorListener("Audio Processor Node") {
    socket = new DatagramSocket(0);
    message = new DiauproMessage(65000, false);
    socket->bindToPort(0);
    activeNode = nullptr;
}

DiauproProcessor::~DiauproProcessor() {

}

void DiauproProcessor::setMonitor(Monitor *monitor, bool asNode) {

    this->monitor = monitor;
    this->zManager = new ZeroConfManager(monitor, this);

    if (asNode) {
        ZeroConfService *service = new ZeroConfService();

        service->setPort(socket->getBoundPort());
        service->setServiceName("Audio_Processor_Node");
        service->setRegType(getServiceTag());

        zManager->registerService(service);
        this->monitor->addFileDescriptorAndListener(socket->getRawSocketHandle(), this);

    } else {
        this->zManager->browseService(getServiceTag().toRawUTF8());
    }
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

    if (hasActiveNetworkConnection()) {
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
        message->clear();

        bytesRead = 0;
        if (socket->waitUntilReady(true, maxWaitTimeMs)) {

            bytesRead = message->readFromSocket(socket);
            message->getAudioData(&buffer);
            message->getMidiData(midiBuffer);

            MidiBuffer::Iterator iterator(midiBuffer);
            MidiMessage tempMessage;
            int sampleIndex;
            if (!midiBuffer.isEmpty()) {
                Logger::writeToLog("has midi returned");

                while (iterator.getNextEvent(tempMessage, sampleIndex)) {
                    Logger::writeToLog(String::formatted("midi note: %d", tempMessage.getNoteNumber()));
                }
            }
        }else {
            Logger::writeToLog("timedout");
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


void DiauproProcessor::handleZeroConfUpdate(OwnedArray<ZeroConfService, CriticalSection> *serviceList) {

    if (serviceList->size() > 0) {
        
        ZeroConfService* service;

        for (int i = 0; i < serviceList->size(); i++) {
            
            service =serviceList->getUnchecked(i);
            
            if (!service->isTaken && service->status == ZeroConfService::ResultStatus::queryResult)
            {
                serviceList->getUnchecked(i)->isTaken = true;
                service = serviceList->getUnchecked(i);
                
                activeNode = service;
                targetHost = activeNode->ip;
                targetPort = activeNode->getPort();
                
                Logger::writeToLog(String::formatted("%s Node Found on %s:%d interface %d", getServiceTag().toRawUTF8(), targetHost.toRawUTF8(), targetPort, activeNode->getInterfaceIndex()));
                return;
            }
        }
        this->activeNode = nullptr;
        Logger::writeToLog(String::formatted("%s Node Not Found", getServiceTag().toRawUTF8()));
        return;
        
    }
    this->activeNode = nullptr;
    Logger::writeToLog(String::formatted("%s Node Lost", getServiceTag().toRawUTF8()));

}


void DiauproProcessor::handleFileDescriptor(int fileDescriptor) {
    Logger::writeToLog("packets received");
    bytesRead = message->readFromSocket(socket, targetHost, targetPort);
    
    this->sampleRate = message->getSampleRate();
    
    audioSampleBuffer.setSize(message->getNumberChannels(), message->getNumberSamples(), true, false, true);
    
    message->getAudioData(&audioSampleBuffer);
    message->getMidiData(midiBuffer);
    localProcess(audioSampleBuffer, midiBuffer);
    
    message->setAudioData(&audioSampleBuffer);

    socket->write(targetHost, targetPort, message->getData(), message->getSize());
}

bool DiauproProcessor::hasActiveNetworkConnection() {
    if (activeNode != nullptr)
    {
        return true;
    }
    return false;
}

DiauproMessage *DiauproProcessor::getCurrentMessage() {
    return this->message;
}
