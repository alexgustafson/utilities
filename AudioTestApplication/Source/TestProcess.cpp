/*
  ==============================================================================

    TestProcess.cpp
    Created: 9 Sep 2015 10:58:23pm
    Author:  Alexander Gustafson

  ==============================================================================
*/

#include "TestProcess.h"


void TestProcess::prepareToPlay(double sampleRate, int samplesPerBlock) {

}

void TestProcess::releaseResources() {

}

void TestProcess::processBlock(AudioSampleBuffer &buffer, MidiBuffer &midiMessages) {
    
    for (int channel = 0; channel < buffer.getNumChannels(); ++channel)
    {
        for (int sample = 0; sample < buffer.getNumSamples(); sample++) {


        }
    }
}

void TestProcess::reset() {
}

const String TestProcess::getInputChannelName(int channelIndex) const {
    return juce::String(channelIndex+1);
}

const String TestProcess::getOutputChannelName(int channelIndex) const {
    return juce::String(channelIndex+1);
}

bool TestProcess::isInputChannelStereoPair(int index) const {
    return false;
}

bool TestProcess::isOutputChannelStereoPair(int index) const {
    return false;
}

bool TestProcess::acceptsMidi() const {
    return true;
}

bool TestProcess::producesMidi() const {
    return false;
}

bool TestProcess::silenceInProducesSilenceOut() const {
    return false;
}

double TestProcess::getTailLengthSeconds() const {
    return 0;
}

void TestProcess::getStateInformation(MemoryBlock &destData) {

}

void TestProcess::setStateInformation(const void *data, int sizeInBytes) {

}

AudioProcessorEditor *TestProcess::createEditor() {
    return nullptr;
}
