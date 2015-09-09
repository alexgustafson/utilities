/*
  ==============================================================================

    AudioStreamManager.h
    Created: 3 Sep 2015 4:36:43pm
    Author:  Alexander Gustafson

  ==============================================================================
*/

#ifndef AUDIOSTREAMMANAGER_H_INCLUDED
#define AUDIOSTREAMMANAGER_H_INCLUDED

#include "JuceHeader.h"
#include "Monitor.h"

struct rtAudioMessage {
    int64 sequenceNr;
    int numOfChannels;
    int payloadSize;
    int command;
    float samples[0];
    
    static rtAudioMessage* CreateNetAudioMessageFromAudioSampleBuffer(AudioSampleBuffer *buffer)
    {
        int payloadSize = buffer->getNumChannels() * buffer->getNumSamples() * sizeof(float);
        
        rtAudioMessage* m = (rtAudioMessage*)malloc(sizeof(rtAudioMessage)+ payloadSize);
        m->numOfChannels = buffer->getNumChannels();
        m->payloadSize = payloadSize;
        m->sequenceNr = 0;
        m->command = 0;
        
        memcpy(m->samples, buffer->getReadPointer(0), payloadSize);
        
        return m;
    }
    
    static rtAudioMessage* CreateNewMessage(int numChannels, int numSamples)
    {
        int payloadSize = numChannels * numSamples * sizeof(float);
        
        rtAudioMessage* m = (rtAudioMessage*)malloc(sizeof(rtAudioMessage)+ payloadSize);
        m->numOfChannels = numChannels;
        m->payloadSize = payloadSize;
        m->sequenceNr = 0;
        m->command = 0;
        
        return m;
    }
    
    void copyToAudioSampleBuffer(AudioSampleBuffer* destBuffer)
    {
        for(int i = 0; i < numOfChannels; i++)
        {
            destBuffer->copyFrom(i, 0, samples, getNumberOfSamples());
        }
    }
    
    int getNumberOfSamples()
    {
        return (int)payloadSize / (numOfChannels * sizeof(float));
    }
    
    int getSize()
    {
        return (sizeof(rtAudioMessage) - sizeof(float)) + payloadSize;
    }
    
    enum Command
    {
        ProcessAudio = 0,
        Quit = 100
    };
};


class AudioStreamManager : public FileDescriptorListener {
public:

    AudioStreamManager(Monitor *monitor);

    ~AudioStreamManager();

    void setMonitor(Monitor *monitor) {
        AudioStreamManager::monitor = monitor;
    }

    void handleFileDescriptor(int fileDescriptor);

private:
    Monitor *monitor;
    drow::FifoBuffer<float> circularBuffer;

};


#endif  // AUDIOSTREAMMANAGER_H_INCLUDED
