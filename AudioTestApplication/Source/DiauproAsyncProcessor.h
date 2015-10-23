/*
  ==============================================================================

    DiauproAsyncProcessor.h
    Created: 22 Oct 2015 4:54:02pm
    Author:  Alexander Gustafson

  ==============================================================================
*/

#ifndef DIAUPROASYNCPROCESSOR_H_INCLUDED
#define DIAUPROASYNCPROCESSOR_H_INCLUDED

#include "JuceHeader.h"
#include "ZeroConfManager.h"
#include "Monitor.h"
#include "DiauproMessage.h"

class DiauproAsyncProcessor : public Thread, ZeroConfListener, FileDescriptorListener
{
public:
    DiauproAsyncProcessor();
    
    ~DiauproAsyncProcessor();
    
    void initializeRingBuffers(int numChannels, int numSamples);
    void setMonitor(Monitor *monitor, bool asNode = false);

    void processBlock(AudioSampleBuffer &buffer, MidiBuffer &midiMessages);
    virtual void localProcess(AudioSampleBuffer &buffer, MidiBuffer &midiMessages, void *state);

    virtual String getServiceTag() {
        return "_diaproasync._udp";
    };
    
    virtual void *getState();
    
    virtual size_t getStateSize();
    
    virtual void setState(void* state);
    
    void run() override;
    
    //AudioProcessor Methods:
    
    virtual bool hasEditor() const;
    
    virtual void prepareToPlay(double sampleRate, int estimatedSamplesPerBlock);
    
    double getSampleRate() {
        return sampleRate;
    };
    
    virtual void getStateInformation(MemoryBlock &destData);
    
    virtual const String getInputChannelName(int channelIndex) const;
    
    virtual AudioProcessorEditor *createEditor();
    
    virtual bool isOutputChannelStereoPair(int index) const;
    
    virtual void setCurrentProgram(int index);
    
    virtual bool isInputChannelStereoPair(int index) const;
    
    virtual void changeProgramName(int index, const String &newName);
    
    virtual int getNumPrograms();
    
    virtual const String getProgramName(int index);
    
    virtual void releaseResources();
    
    virtual bool silenceInProducesSilenceOut() const;
    
    virtual int getCurrentProgram();
    
    virtual const String getName() const;
    
    virtual const String getOutputChannelName(int channelIndex) const;
    
    virtual void setStateInformation(const void *data, int sizeInBytes);
    
    virtual double getTailLengthSeconds() const;
    
    virtual bool producesMidi() const;
    
    virtual bool acceptsMidi() const;
    
    //ZeroConfListener Methods:
    
    virtual void handleZeroConfUpdate(OwnedArray<ZeroConfService, CriticalSection> *serviceList);
    
    //FileDescriptorListener Methods:
    
    void handleFileDescriptor(int fileDescriptor);
    
    bool hasActiveNetworkConnection();
    
    DiauproMessage *getCurrentMessage();
    
    double getProcessTime();
    
    double getRoundTripTime();
    
    void setAsyncMode(bool mode) {
        asyncMode = mode;
        if(asyncMode){
            startThread();
        }
    };
    
    void setTag(uint32 tag);
    uint32 getTag();

private:
    
    struct diauprostate {
        double totalProcessTime;
        double nodeProcessTime;
    };
    
    struct diauprostate *processState;
    
    ScopedPointer<DatagramSocket> socket;
    ScopedPointer<DiauproMessage> message;
    ZeroConfService *activeNode;
    ZeroConfService *service;
    ScopedPointer<ZeroConfManager> zManager;
    Monitor *monitor;
    int maxWaitTimeMs;
    int bytesRead;
    int targetPort;
    String targetHost;
    double sampleRate;
    double processTimeMs;
    double tripTimeMs;
    int timeoutCount;
    
    
    AudioSampleBuffer audioSampleBuffer;
    MidiBuffer midiBuffer;
    
    String listenerName = "Diaupro Processor";
    
    bool isNode;
    bool asyncMode;

    OwnedArray<drow::FifoBuffer<float>> ringBuffers;
    CriticalSection lock;
    uint32 tagNr;
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DiauproAsyncProcessor)
};


#endif  // DIAUPROASYNCPROCESSOR_H_INCLUDED
