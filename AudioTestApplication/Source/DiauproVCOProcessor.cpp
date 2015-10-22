/*
  ==============================================================================

    DiauproVCOProcessor.cpp
    Created: 30 Sep 2015 3:15:24pm
    Author:  Alexander Gustafson

  ==============================================================================
*/

#include "DiauproVCOProcessor.h"

void DiauproVCOProcessor::localProcess(AudioSampleBuffer &buffer, MidiBuffer &midiMessages, void* state) {
    vco_state* s = (vco_state *)state;
    int sampleNr;
    int nextMidiEventCount = -1;
    MidiBuffer::Iterator midiEventIterator(midiMessages);
    MidiMessage nextMidiEvent;
    bool hasEvent;
    double currentSample;
    uint8 pitch;
    
    for(sampleNr = 0; sampleNr < buffer.getNumSamples(); sampleNr++)
    {
        if(nextMidiEventCount < sampleNr)
        {
            hasEvent = midiEventIterator.getNextEvent(nextMidiEvent,nextMidiEventCount );
        }

        if(hasEvent && nextMidiEventCount == sampleNr)
        {
            
            processNote(&nextMidiEvent);

            s->phase = 0.0;
            s->frequency = MidiMessage::getMidiNoteInHertz(getHighestNote());
            double cyclesPerSample = s->frequency / getSampleRate();
            s->step = cyclesPerSample * 2.0 * double_Pi;

        }

        if((pitch = getHighestNote()) < 128)
        {
            
            currentSample =  s->phase * s->level;
            currentSample = sin(currentSample);
            
            s->phase += s->step;
            for(int i = 0; i < buffer.getNumChannels(); i++)
            {
                float oldSample = buffer.getSample(i, sampleNr);
                buffer.setSample(i, sampleNr, (currentSample + oldSample)*0.5);
            }

        }
    }
}

void *DiauproVCOProcessor::getState() {
    return (void *)this->processState;
}

size_t DiauproVCOProcessor::getStateSize() {
    return sizeof(vco_state) ;
}

void DiauproVCOProcessor::setState(void* state)
{
    
    memcpy(this->processState, (const void*)state, sizeof(vco_state));
    
}

void DiauproVCOProcessor::processNote(MidiMessage* message)
{
    if (this->processState->noteStates[message->getNoteNumber()] == (uint8)0) {
        this->processState->noteStates[message->getNoteNumber()] = message->getVelocity();
    }else{
        this->processState->noteStates[message->getNoteNumber()] = (uint8)0;
    }
}

uint8 DiauproVCOProcessor::getHighestNote()
{
    int i = 127;
    while (i>=0 && this->processState->noteStates[i] == 0) {
        
        i--;
    }
    if (i > -1) {
        return i;
    }
    return (uint8)128;
}
