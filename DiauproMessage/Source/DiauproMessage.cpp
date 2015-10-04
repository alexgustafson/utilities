/*
  ==============================================================================

    DiauproMessage.cpp
    Created: 26 Sep 2015 2:09:13pm
    Author:  Alexander Gustafson

  ==============================================================================
*/

#include "DiauproMessage.h"


DiauproMessage::DiauproMessage(int initialSize, bool initializeToZero) : data(initialSize, initializeToZero) {

    this->clear();
}

int DiauproMessage::readFromSocket(DatagramSocket *sock) {
    int bytesRead = sock->read(this->data.getData(), this->data.getSize(), false);
    this->data.copyTo(&this->header, 0, sizeof(struct diapro_header));
    return bytesRead;
}

int DiauproMessage::readFromSocket(DatagramSocket *sock, String &targetHost, int &targetPort) {
    int bytesRead = sock->read(this->data.getData(), this->data.getSize(), false, targetHost, targetPort);
    this->data.copyTo(&this->header, 0, sizeof(struct diapro_header));
    return bytesRead;
}


uint16 DiauproMessage::getSequeceNumber() {
    return this->header.sequenceNumber;
}

uint16 DiauproMessage::getNumberSamples() {
    return this->header.numSamples;
}

uint16 DiauproMessage::getNumberChannels() {
    return this->header.numChannels;
}

void DiauproMessage::setNumberChannels(uint16 numChannels) {
    this->header.numChannels = numChannels;
}

void DiauproMessage::setNumberSamples(uint16 numSamples) {
    this->header.numSamples = numSamples;
}

void DiauproMessage::setSequenceNumber(uint16 sequenceNumber) {
    this->header.sequenceNumber = sequenceNumber;
}

void DiauproMessage::setAudioData(AudioSampleBuffer *buffer) {
    setNumberChannels(buffer->getNumChannels());
    setNumberSamples(buffer->getNumSamples());
    //setPointerToSampleData((float *) ((char *) this->data.getData() + sizeof(this->header)));
    for (int i = 0; i < buffer->getNumChannels(); i++) {
        int channelOffset = i * buffer->getNumSamples() * sizeof(float);
        this->data.copyFrom(buffer->getReadPointer(i), getAudioDataOffset() + channelOffset, buffer->getNumSamples() * sizeof(float));
    }
    this->header.audioDataSize = buffer->getNumChannels() * buffer->getNumSamples() * sizeof(float);
}

void DiauproMessage::setMidiData(MidiBuffer *midiMessages) {
    this->data.copyFrom((void *) midiMessages->data.getRawDataPointer(), getMidiDataOffset(), midiMessages->data.size() * sizeof(uint8));
    //setPointerToMidiData((uint8 *)((char *) this->data.getData() + getMidiDataOffset()));
    this->header.midiDataSize = midiMessages->data.size() * sizeof(uint8);
}

void DiauproMessage::setStateData(void *stateData, size_t stateSize) {
    this->data.copyFrom(stateData, getStateDataOffset(), stateSize);
    //setPointerToStateData((void *)((char *) this->data.getData() + getStateDataOffset() ));
    this->header.stateDataSize = stateSize;
}

AudioSampleBuffer *DiauproMessage::getAudioData(AudioSampleBuffer *buffer) {

    for (int i = 0; i < getNumberChannels(); i++) {
        buffer->copyFrom(i, 0, (float*)((char*)this->data.getData() + getAudioDataOffset()+ (i * getNumberSamples() * sizeof(float) )), getNumberSamples());
    }
    return buffer;
}

float *DiauproMessage::getSampleData() {
    return (float *) ((char *) this->data.getData() + getAudioDataOffset() );
}

int DiauproMessage::getSampleDataSize() {
    return getNumberSamples() * getNumberChannels() * sizeof(float);
}

void DiauproMessage::setPointerToSampleData(float *ptr) {
    //this->header.sampleData = ptr;
}

void DiauproMessage::setPointerToMidiData(uint8 *ptr) {
    //this->header.midiData = ptr;
}

void DiauproMessage::setPointerToStateData(void *ptr) {
    //this->header.stateData = ptr;
}

void *DiauproMessage::getData() {
    this->data.copyFrom(&this->header, 0, sizeof(struct diapro_header));
    return this->data.getData();
}

size_t DiauproMessage::getSize() {
    return sizeof(diapro_header) + this->header.audioDataSize + this->header.midiDataSize + this->header.stateDataSize;
}

size_t DiauproMessage::getAudioDataOffset() {
    return sizeof(struct diapro_header);
}

size_t DiauproMessage::getMidiDataOffset() {
    return getAudioDataOffset() + (getNumberSamples() * getNumberChannels() * sizeof(float)) ;
}

size_t DiauproMessage::getStateDataOffset() {
    return getAudioDataOffset() + (getNumberSamples() * getNumberChannels() * sizeof(float)) + this->header.midiDataSize;
}

void DiauproMessage::getMidiData(MidiBuffer &buffer) {

    buffer.data = Array<uint8>((uint8*)((char*)this->getData() + getMidiDataOffset()) , this->header.midiDataSize);
}

double DiauproMessage::getSampleRate() {
    return this->header.sampleRate;
}

void DiauproMessage::setSampleRate(double rate) {
    this->header.sampleRate = rate;
}

void DiauproMessage::clear() {
    this->header.audioDataSize = 0;
    this->header.midiDataSize = 0;
    this->header.stateDataSize = 0;
    this->header.numChannels = 0;
    this->header.numSamples = 0;
    this->header.sequenceNumber = 0;
    //this->header.sampleData = nullptr;
    //this->header.midiData = nullptr;
    //this->header.stateData = nullptr;
    this->header.sampleRate = 0;
    this->data.fillWith((uint8) 0);
}

String DiauproMessage::headerToString() {
    return String::formatted("Header:\n sequenceNumber: %d\n numChannels: %d\n numSamples: %d\n audioDataSize: %d\n midiDataSize: %d\n stateDataSize: %d\nEnd Header",this->header.sequenceNumber, this->header.numChannels, this->header.numSamples, this->header.audioDataSize, this->header.midiDataSize, this->header.stateDataSize);
}
