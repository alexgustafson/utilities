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



class AudioStreamManager : public FileDescriptorListener {
public:

    AudioStreamManager(Monitor *monitor);

    ~AudioStreamManager();

    void setMonitor(Monitor *monitor) {
        AudioStreamManager::monitor = monitor;
    }

    void

    void handleFileDescriptor(int fileDescriptor) override;

private:
    Monitor *monitor;
    drow::FifoBuffer<float> circularBuffer;
    int

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AudioStreamManager);
};


#endif  // AUDIOSTREAMMANAGER_H_INCLUDED
