/*
  ==============================================================================

    TestProcess.h
    Created: 9 Sep 2015 10:22:26pm
    Author:  Alexander Gustafson

  ==============================================================================
*/

#ifndef TESTPROCESS_H_INCLUDED
#define TESTPROCESS_H_INCLUDED
#include "JuceHeader.h"

class TestProcess : public AudioProcessor
{
public:

    TestProcess() {};
    ~TestProcess() {};

    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;
    void processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages) override;
    void reset() override;
    
    const String getName() const override { return "Empty Process"; };
    
    const String getInputChannelName (int channelIndex) const override;
    const String getOutputChannelName (int channelIndex) const override;
    bool isInputChannelStereoPair (int index) const override;
    bool isOutputChannelStereoPair (int index) const override;
    
    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool silenceInProducesSilenceOut() const override;
    double getTailLengthSeconds() const override;
    
    int getNumPrograms() override                                               { return 1; }
    int getCurrentProgram() override                                            { return 0; }
    void setCurrentProgram (int /*index*/) override                             {}
    const String getProgramName (int /*index*/) override                        { return "Default"; }
    void changeProgramName (int /*index*/, const String& /*newName*/) override  {}
    

    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    bool hasEditor() const override                  { return true; }
    AudioProcessorEditor* createEditor() override;
    
    void setNodeID (int32 newNodeID) { nodeID = newNodeID; }
    int32 getNodeID() { return nodeID; }
    
private:
    int32 nodeID;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TestProcess)
};

#endif  // TESTPROCESS_H_INCLUDED

