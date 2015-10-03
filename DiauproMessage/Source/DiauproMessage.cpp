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
    setPointerToSampleData((float *) ((char *) this->data.getData() + sizeof(this->header)));
    setPointerToMidiData((uint8 *)((char *) this->data.getData() + getMidiDataOffset() ));
    setPointerToStateData((void *)((char *) this->data.getData() + getStateDataOffset() ));
    return bytesRead;
}

int DiauproMessage::readFromSocket(DatagramSocket *sock, String &targetHost, int &targetPort) {
    int bytesRead = sock->read(this->data.getData(), this->data.getSize(), false, targetHost, targetPort);
    this->data.copyTo(&this->header, 0, sizeof(struct diapro_header));
    setPointerToSampleData((float *) ((char *) this->data.getData() + sizeof(this->header)));
    setPointerToMidiData((uint8 *)((char *) this->data.getData() + getMidiDataOffset() ));
    setPointerToStateData((void *)((char *) this->data.getData() + getStateDataOffset() ));
    return bytesRead;
}


int DiauproMessage::getSequeceNumber() {
    return this->header.sequenceNumber;
}

int DiauproMessage::getNumberSamples() {
    return this->header.numSamples;
}

int DiauproMessage::getNumberChannels() {
    return this->header.numChannels;
}

void DiauproMessage::setNumberChannels(int numChannels) {
    this->header.numChannels = numChannels;
}

void DiauproMessage::setNumberSamples(int numSamples) {
    this->header.numSamples = numSamples;
}

void DiauproMessage::setSequenceNumber(int sequenceNumber) {
    this->header.sequenceNumber = sequenceNumber;
}

void DiauproMessage::setAudioData(AudioSampleBuffer *buffer) {
    setNumberChannels(buffer->getNumChannels());
    setNumberSamples(buffer->getNumSamples());
    setPointerToSampleData((float *) ((char *) this->data.getData() + sizeof(this->header)));
    for (int i = 0; i < buffer->getNumChannels(); i++) {
        this->data.copyFrom(buffer->getReadPointer(i), getAudioDataOffset() + (i * buffer->getNumSamples() * sizeof(float)), buffer->getNumSamples() * sizeof(float));
    }
    this->header.audioDataSize = buffer->getNumChannels() * buffer->getNumSamples() * sizeof(float);
}

void DiauproMessage::setMidiData(MidiBuffer *midiMessages) {
    this->data.copyFrom((void *) midiMessages->data.getRawDataPointer(), getMidiDataOffset(), midiMessages->data.size() * sizeof(uint8));
    setPointerToMidiData((uint8 *)((char *) this->data.getData() + getMidiDataOffset()));
    this->header.midiDataSize = midiMessages->data.size() * sizeof(uint8);
}

void DiauproMessage::setStateData(void *stateData, size_t stateSize) {
    this->data.copyFrom(stateData, getStateDataOffset(), stateSize);
    setPointerToStateData((void *)((char *) this->data.getData() + getStateDataOffset() ));
    this->header.stateDataSize = stateSize;
}

AudioSampleBuffer *DiauproMessage::getAudioData(AudioSampleBuffer *buffer) {

    for (int i = 0; i < getNumberChannels(); i++) {
        buffer->copyFrom(i, 0, this->header.sampleData + (i * getNumberSamples()), getNumberSamples());
        
    }
    return buffer;
}

float *DiauproMessage::getSampleData() {
    //return this->header.sampleData;
    return (float *) ((char *) this->data.getData() + sizeof(this->header));
}

int DiauproMessage::getSampleDataSize() {
    return getNumberSamples() * getNumberChannels() * sizeof(float);
}

void DiauproMessage::setPointerToSampleData(float *ptr) {
    this->header.sampleData = ptr;
}

void DiauproMessage::setPointerToMidiData(uint8 *ptr) {
    this->header.midiData = ptr;
}


void DiauproMessage::setPointerToStateData(void *ptr) {
    this->header.stateData = ptr;
}

void *DiauproMessage::getData() {
    this->data.copyFrom(&this->header, 0, sizeof(this->header));
    return this->data.getData();
}

size_t DiauproMessage::getSize() {
    return sizeof(diapro_header) + this->header.audioDataSize + this->header.midiDataSize;
}

size_t DiauproMessage::getAudioDataOffset() {
    return sizeof(this->header);
}

size_t DiauproMessage::getMidiDataOffset() {
    return sizeof(struct diapro_header) + (getNumberSamples() * getNumberChannels() * sizeof(float));
}

size_t DiauproMessage::getStateDataOffset() {
    return sizeof(struct diapro_header) + (getNumberSamples() * getNumberChannels() * sizeof(float) + this->header.midiDataSize);
}

void DiauproMessage::getMidiData(MidiBuffer &buffer) {

    buffer.data = Array<uint8>(this->header.midiData, this->header.midiDataSize);
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
    this->header.numChannels = 0;
    this->header.numSamples = 0;
    this->header.sequenceNumber = 0;
    this->header.sampleData = nullptr;
    this->header.midiData = nullptr;
    this->header.stateData = nullptr;
    this->header.sampleRate = 0;
}
