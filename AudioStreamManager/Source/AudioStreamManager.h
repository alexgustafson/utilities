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

//==============================================================================
/**
    An abstract class
*/
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
