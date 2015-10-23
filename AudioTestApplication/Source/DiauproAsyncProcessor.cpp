/*
  ==============================================================================

    DiauproAsyncProcessor.cpp
    Created: 22 Oct 2015 4:54:02pm
    Author:  Alexander Gustafson

  ==============================================================================
*/

#include "DiauproAsyncProcessor.h"

DiauproAsyncProcessor::DiauproAsyncProcessor() : Thread("Diaupro Async Processor"), FileDescriptorListener("Audio Processor Node"),
processTimeMs(0.0), tripTimeMs(0.0), asyncMode(false), tagNr((uint32) 0) {
    
    this->processState = (diauprostate*)malloc(sizeof(diauprostate));
    processState->nodeProcessTime = 0.0;
    processState->totalProcessTime = 0.0;
    
    socket = new DatagramSocket(0);
    message = new DiauproMessage(65000, false);
    socket->bindToPort(0);
    activeNode = nullptr;
    timeoutCount = 0;
}

DiauproAsyncProcessor::~DiauproAsyncProcessor() {
    
    if(this->isNode)
    {
        this->zManager->removeService(service);
    }

    stopThread(300);
}

void DiauproAsyncProcessor::setMonitor(Monitor *monitor, bool asNode) {
    this->isNode = asNode;
    this->monitor = monitor;
    this->zManager = new ZeroConfManager(monitor, this);
    
    if (asNode) {
        service = new ZeroConfService();
        
        service->setPort(socket->getBoundPort());
        service->setServiceName("Audio_Processor_Node");
        service->setRegType(getServiceTag());
        
        zManager->registerService(service);
        this->monitor->addFileDescriptorAndListener(socket->getRawSocketHandle(), this);
        
    } else {
        
        this->zManager->browseService(getServiceTag().toRawUTF8());
    }
}

bool DiauproAsyncProcessor::hasEditor() const {
    return false;
}

void DiauproAsyncProcessor::prepareToPlay(double sampleRate, int estimatedSamplesPerBlock) {
    
    this->sampleRate = sampleRate;
    maxWaitTimeMs = (estimatedSamplesPerBlock / sampleRate) * 1000;
    
}

void DiauproAsyncProcessor::getStateInformation(MemoryBlock &destData) {
    
}

const String DiauproAsyncProcessor::getInputChannelName(int channelIndex) const {
    return String();
}

AudioProcessorEditor *DiauproAsyncProcessor::createEditor() {
    return nullptr;
}


void DiauproAsyncProcessor::processBlock(AudioSampleBuffer &buffer, MidiBuffer &midiMessages) {
    
    const double callbackStartTime = Time::getMillisecondCounterHiRes();
    const double startTime = Time::getMillisecondCounterHiRes();
    
    double returnTime;
    
    if (hasActiveNetworkConnection()) {
        if (socket->waitUntilReady(false, maxWaitTimeMs)) {
            const ScopedLock sl (lock);
            message->setSampleRate(sampleRate);
            message->setAudioData(&buffer);
            message->setMidiData(&midiMessages);
            message->setStateData(getState(), getStateSize());
            
            bytesRead = socket->write(targetHost, targetPort, message->getData(), message->getSize());
            
            if (bytesRead < 0) {
                printf("sendto() returned %d errno %d %s\n", bytesRead, errno, strerror(errno));
                return;
            }
        }
        
        buffer.clear();
        message->clear();
        
        if (asyncMode) {
            
        
        if (ringBuffers[0]->getNumAvailable() > buffer.getNumSamples()) {
            for(int i = 0; i < buffer.getNumChannels(); i++)
            {
                ringBuffers[i]->readSamples(buffer.getWritePointer(i), buffer.getNumSamples());
            }
        }else{
            Logger::writeToLog("no data returned");
            timeoutCount++;
            tripTimeMs = -1.0;
            return;
        }
        }else {
            bytesRead = 0;
            if (socket->waitUntilReady(true, maxWaitTimeMs)) {
                
                bytesRead = message->readFromSocket(socket);
                
                returnTime = Time::getMillisecondCounterHiRes();
                message->setTotalTime(startTime - returnTime);
                message->setTag(tagNr);
                message->getAudioData(&buffer);
                message->getMidiData(midiBuffer);
                setState(message->getState());
                this->processTimeMs  = message->getProcessTime();
                
            } else {
                Logger::writeToLog("timedout");
                timeoutCount++;
                tripTimeMs = -1.0;
                tagNr = (uint32)0;
                localProcess(buffer, midiMessages, getState());
            }
        }
        
    } else {
        
        localProcess(buffer, midiMessages, getState());
        
    }
    
    tripTimeMs  = Time::getMillisecondCounterHiRes() - callbackStartTime;
}

void DiauproAsyncProcessor::run()
{
    while (!threadShouldExit() && asyncMode) {
        if (socket->waitUntilReady(true, -1)) {
            const ScopedLock sl (lock);
            bytesRead = message->readFromSocket(socket);
            message->getAudioData(&ringBuffers);
            message->getMidiData(midiBuffer);
            tagNr = message->getTag();

            setState(message->getState());
            this->processTimeMs  = message->getProcessTime();
        }
    }
}

void DiauproAsyncProcessor::initializeRingBuffers(int numChannels, int numSamples)
{
    for(int i = 0; i < numChannels; i++)
    {
        ringBuffers.add(new drow::FifoBuffer<float>(numSamples));
    }
}


void DiauproAsyncProcessor::localProcess(AudioSampleBuffer &buffer, MidiBuffer &midiMessages, void *state) {
    

}

bool DiauproAsyncProcessor::isOutputChannelStereoPair(int index) const {
    return false;
}

void DiauproAsyncProcessor::setCurrentProgram(int index) {
    
}

bool DiauproAsyncProcessor::isInputChannelStereoPair(int index) const {
    return false;
}

void DiauproAsyncProcessor::changeProgramName(int index, const String &newName) {
    
}

int DiauproAsyncProcessor::getNumPrograms() {
    return 0;
}

const String DiauproAsyncProcessor::getProgramName(int index) {
    return String();
}

void DiauproAsyncProcessor::releaseResources() {
    
}

bool DiauproAsyncProcessor::silenceInProducesSilenceOut() const {
    return false;
}

int DiauproAsyncProcessor::getCurrentProgram() {
    return 0;
}

const String DiauproAsyncProcessor::getName() const {
    return String();
}

const String DiauproAsyncProcessor::getOutputChannelName(int channelIndex) const {
    return String();
}

void DiauproAsyncProcessor::setStateInformation(const void *data, int sizeInBytes) {
    
}

double DiauproAsyncProcessor::getTailLengthSeconds() const {
    return 0;
}

bool DiauproAsyncProcessor::producesMidi() const {
    return false;
}

bool DiauproAsyncProcessor::acceptsMidi() const {
    return false;
}

void DiauproAsyncProcessor::handleZeroConfUpdate(OwnedArray<ZeroConfService, CriticalSection> *serviceList) {
    
    if (serviceList->size() > 0) {
        
        ZeroConfService *service;
        
        for (int i = 0; i < serviceList->size(); i++) {
            
            service = serviceList->getUnchecked(i);
            
            if (!service->isTaken && service->status == ZeroConfService::ResultStatus::queryResult) {
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


void DiauproAsyncProcessor::handleFileDescriptor(int fileDescriptor) {
    
    const double startTime = Time::getMillisecondCounterHiRes();
    
    bytesRead = message->readFromSocket(socket, targetHost, targetPort);
    setState(message->getState());
    
    sampleRate = message->getSampleRate();
    
    audioSampleBuffer.setSize(message->getNumberChannels(), message->getNumberSamples(), true, false, true);
    
    message->getAudioData(&audioSampleBuffer);
    message->getMidiData(midiBuffer);
    if(message->getTag() == (uint32)555)
    {
        Logger::writeToLog("Got tag");
    }
    
    localProcess(audioSampleBuffer, midiBuffer, getState());
    
    message->setAudioData(&audioSampleBuffer);
    
    message->setStateData(getState(), getStateSize());
    message->setProcessTime( Time::getMillisecondCounterHiRes() - startTime );
    socket->write(targetHost, targetPort, message->getData(), message->getSize());
}

bool DiauproAsyncProcessor::hasActiveNetworkConnection() {
    if (activeNode != nullptr) {
        return true;
    }
    return false;
}

DiauproMessage *DiauproAsyncProcessor::getCurrentMessage() {
    return this->message;
}

void DiauproAsyncProcessor::setState(void* state)
{
    memcpy(this->processState, (const void*)state, sizeof(diauprostate));
}

void* DiauproAsyncProcessor::getState() {
    return this->processState;
}

size_t DiauproAsyncProcessor::getStateSize() {
    return sizeof(diauprostate);
}

double DiauproAsyncProcessor::getProcessTime()
{
    return processTimeMs;
}
double DiauproAsyncProcessor::getRoundTripTime()
{
    return tripTimeMs;
}
void DiauproAsyncProcessor::setTag(uint32 tag)
{
    tagNr = tag;
}
uint32 DiauproAsyncProcessor::getTag()
{
    return tagNr;
}

