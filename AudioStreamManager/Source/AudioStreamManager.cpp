/*
  ==============================================================================

    AudioStreamManager.cpp
    Created: 3 Sep 2015 4:36:43pm
    Author:  Alexander Gustafson

  ==============================================================================
*/

#include "AudioStreamManager.h"

AudioStreamManager::AudioStreamManager(Monitor *monitor)
        : circularBuffer(44100)
{
    this->setMonitor(monitor);
}

AudioStreamManager::~AudioStreamManager() {

}

void AudioStreamManager::handleFileDescriptor(int fileDescriptor) {



}
