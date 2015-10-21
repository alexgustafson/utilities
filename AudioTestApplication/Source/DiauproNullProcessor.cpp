/*
  ==============================================================================

    DiauproNullProcessor.cpp
    Created: 21 Oct 2015 1:41:40pm
    Author:  Alexander Gustafson

  ==============================================================================
*/

#include "DiauproNullProcessor.h"

void DiauproNullProcessor::localProcess(AudioSampleBuffer &buffer, MidiBuffer &midiMessages, void* state) {

    
}

void* DiauproNullProcessor::getState() {
    return this->processState;
}

size_t DiauproNullProcessor::getStateSize() {
    return sizeof(null_state) ;
}

void DiauproNullProcessor::setState(void* state)
{
    this->processState = (null_state*)state;
}