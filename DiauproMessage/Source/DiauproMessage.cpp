/*
  ==============================================================================

    DiauproMessage.cpp
    Created: 26 Sep 2015 2:09:13pm
    Author:  Alexander Gustafson

  ==============================================================================
*/

#include "DiauproMessage.h"


DiauproMessage::DiauproMessage(int initialSize, bool initializeToZero) : data(initialSize, initializeToZero) {


}

int DiauproMessage::readFromSocket(DatagramSocket *sock) {
    int bytesRead = sock->read(this->data.getData(), this->data.getSize(), false);
    this->data.copyTo(&this->header, 0, sizeof(struct diapro_header));
    setPointerToSampleData((float *) ((char*)this->data.getData() + sizeof(this->header)));
    return bytesRead;
}

int DiauproMessage::readFromSocket(DatagramSocket *sock, String &targetHost, int &targetPort) {
    int bytesRead = sock->read(this->data.getData(), this->data.getSize(), false, targetHost, targetPort);
    this->data.copyTo(&this->header, 0, sizeof(struct diapro_header));
    setPointerToSampleData((float *) ((char*)this->data.getData() + sizeof(this->header)));
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

void DiauproMessage::setAudioData(AudioSampleBuffer *buffer) {
    setNumberChannels(buffer->getNumChannels());
    setNumberSamples(buffer->getNumSamples());
    setPointerToSampleData((float *) ((char*)this->data.getData() + sizeof(this->header)));
    for (int i = 0; i < buffer->getNumChannels(); i++) {
        this->data.copyFrom(buffer->getReadPointer(i), getAudioDataOffset() + (i * buffer->getNumSamples() * sizeof(float)), buffer->getNumSamples() * sizeof(float));
    }
}

void DiauproMessage::setMidiData(MidiBuffer &midiMessages)
{
    this->data.copyFrom((void *)midiMessages.data[0], getMidiDataOffset(), sizeof(midiMessages));
    setPointerToSampleData((MidiBuffer:: *) ((char*)this->data.getData() + getMidiDataOffset()));
    this->header.midiDataSize = sizeof(midiMessages);
}

AudioSampleBuffer *DiauproMessage::getAudioData(AudioSampleBuffer *buffer) {

    for(int i = 0; i < getNumberChannels(); i++)
    {
        buffer->copyFrom(i, 0, this->header.sampleData + (i * getNumberSamples()), getNumberSamples());
    }

    return buffer;
}

float *DiauproMessage::getSampleData() {
    //return this->header.sampleData;
    return (float *) ((char*)this->data.getData() + sizeof(this->header));
}

int DiauproMessage::getSampleDataSize() {
    return getNumberSamples() * getNumberChannels() * sizeof(float);
}

void DiauproMessage::setPointerToSampleData(float *ptr) {
    this->header.sampleData = ptr;
}
void DiauproMessage::setPointerToMidiData(MidiBuffer *ptr) {
    this->header.midiData = ptr;
}

void *DiauproMessage::getData() {
    this->data.copyFrom(&this->header, 0, sizeof(this->header));
    return this->data.getData();
}

size_t DiauproMessage::getSize() {
    return this->data.getSize();
}

size_t DiauproMessage::getAudioDataOffset() {
    return sizeof(this->header);
}

size_t DiauproMessage::getMidiDataOffset() {
    return sizeof(struct diapro_header) + (getNumberSamples() * getNumberChannels() * sizeof(float));
}

MidiBuffer *DiauproMessage::getMidiData() {
    return (MidiBuffer:: *) ((char*)this->data.getData() + getMidiDataOffset());
}
