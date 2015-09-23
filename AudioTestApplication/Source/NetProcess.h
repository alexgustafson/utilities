/*
  ==============================================================================

    NetProcess.h
    Created: 18 Sep 2015 3:18:38pm
    Author:  Alexander Gustafson

  ==============================================================================
*/

#ifndef NETPROCESS_H_INCLUDED
#define NETPROCESS_H_INCLUDED
#include "JuceHeader.h"
#include "Monitor.h"

class NetProcess : public AudioProcessor, public FileDescriptorListener
{
public:
    
    NetProcess() : FileDescriptorListener("Net Process"),
                    circularBuffer(44100)
    {
        tempBuffer = new AudioSampleBuffer(2, 44100);
        socket = new DatagramSocket();
        socket->bindToPort(40240);
    };
    ~NetProcess() {};
    
    void setTarget(int port, String host);
    void setSocket(int sock);
    void removeSocket();
    
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;
    void processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages) override;
    void reset() override;
    
    const String getName() const override { return "Net Process"; };
    
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
    
    void handleFileDescriptor(int fileDescriptor) override;
    
private:
    int32 nodeID;
    ScopedPointer<DatagramSocket> socket;
    int targetPort;
    String targetHost;
    
    
    drow::FifoBuffer<float> circularBuffer;
    ScopedPointer<AudioSampleBuffer> tempBuffer;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NetProcess)
};



#endif  // NETPROCESS_H_INCLUDED
