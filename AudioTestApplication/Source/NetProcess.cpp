/*
  ==============================================================================

    NetProcess.cpp
    Created: 18 Sep 2015 3:18:38pm
    Author:  Alexander Gustafson

  ==============================================================================
*/

#include "NetProcess.h"

void NetProcess::initializeSocket(int portNr)
{
    
}



void NetProcess::prepareToPlay(double sampleRate, int samplesPerBlock) {
    
}

void NetProcess::releaseResources() {
    
}

void NetProcess::processBlock(AudioSampleBuffer &buffer, MidiBuffer &midiMessages) {
    
    for (int channel = 0; channel < buffer.getNumChannels(); ++channel)
    {
        for (int sample = 0; sample < buffer.getNumSamples(); sample++) {
            
            
        }
    }
}

void NetProcess::reset() {
}

const String NetProcess::getInputChannelName(int channelIndex) const {
    return juce::String(channelIndex+1);
}

const String NetProcess::getOutputChannelName(int channelIndex) const {
    return juce::String(channelIndex+1);
}

bool NetProcess::isInputChannelStereoPair(int index) const {
    return false;
}

bool NetProcess::isOutputChannelStereoPair(int index) const {
    return false;
}

bool NetProcess::acceptsMidi() const {
    return true;
}

bool NetProcess::producesMidi() const {
    return false;
}

bool NetProcess::silenceInProducesSilenceOut() const {
    return false;
}

double NetProcess::getTailLengthSeconds() const {
    return 0;
}

void NetProcess::getStateInformation(MemoryBlock &destData) {
    
}

void NetProcess::setStateInformation(const void *data, int sizeInBytes) {
    
}

AudioProcessorEditor *NetProcess::createEditor() {
    return nullptr;
}
