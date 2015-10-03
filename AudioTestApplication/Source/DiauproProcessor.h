/*
  ==============================================================================

    DiauproProcessor.h
    Created: 22 Sep 2015 3:19:42pm
    Author:  Alexander Gustafson

  ==============================================================================
*/

#ifndef DIAUPROPROCESSOR_H_INCLUDED
#define DIAUPROPROCESSOR_H_INCLUDED

#include "JuceHeader.h"
#include "ZeroConfManager.h"
#include "Monitor.h"
#include "DiauproMessage.h"

class DiauproProcessor : public AudioProcessor,
                         public ZeroConfListener,
                         public FileDescriptorListener{
public:
    DiauproProcessor();

    ~DiauproProcessor();

    void setMonitor(Monitor *monitor, bool asNode = false);
    virtual String getServiceTag() { return "_diapro._udp"; };


    //AudioProcessor Methods:

    virtual bool hasEditor() const;

    virtual void prepareToPlay(double sampleRate, int estimatedSamplesPerBlock);
    double getSampleRate() {return sampleRate;};

    virtual void getStateInformation(MemoryBlock &destData);

    virtual const String getInputChannelName(int channelIndex) const;

    virtual AudioProcessorEditor *createEditor();

    virtual void processBlock(AudioSampleBuffer &buffer, MidiBuffer &midiMessages);

    virtual void localProcess(AudioSampleBuffer &buffer, MidiBuffer &midiMessages);

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

    DiauproMessage* getCurrentMessage();

private:

    ScopedPointer<DatagramSocket> socket;
    ScopedPointer<DiauproMessage> message;
    ZeroConfService *activeNode;
    ScopedPointer<ZeroConfManager> zManager;
    Monitor *monitor;
    int maxWaitTimeMs;
    int bytesRead;
    int targetPort;
    String targetHost;
    double sampleRate;
                             
    AudioSampleBuffer audioSampleBuffer;
    MidiBuffer midiBuffer;

    String listenerName = "Diaupro Processor";

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DiauproProcessor)
};


#endif  // DIAUPROPROCESSOR_H_INCLUDED
