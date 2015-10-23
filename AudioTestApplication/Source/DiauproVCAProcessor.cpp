/*
  ==============================================================================

    DiauproVCAProcessor.cpp
    Created: 30 Sep 2015 5:24:02pm
    Author:  Alexander Gustafson

  ==============================================================================
*/

#include "DiauproVCAProcessor.h"

void DiauproVCAProcessor::localProcess(AudioSampleBuffer &buffer, MidiBuffer &midiMessages, void* state) {
    vca_state* s = (vca_state*)state;
    int sampleNr;
    int nextMidiEventCount = -1;
    MidiBuffer::Iterator midiEventIterator(midiMessages);
    MidiMessage nextMidiEvent;
    bool hasEvent;
    
    float currentSample;
    double vcoeff;

    for(sampleNr = 0; sampleNr < buffer.getNumSamples(); sampleNr++)
    {
        vcoeff = s->vfactor;
        
        if(nextMidiEventCount < sampleNr)
        {
            hasEvent = midiEventIterator.getNextEvent(nextMidiEvent,nextMidiEventCount );
        }

        if(hasEvent && nextMidiEventCount == sampleNr)
        {
            processNote(&nextMidiEvent);

            
            if (nextMidiEvent.isNoteOff() && hasNoteOn()) {
                
            }else{
                s->phase = 0.0;
                s->lastVelocity = nextMidiEvent.getFloatVelocity();
            }
        }

        if( hasNoteOn() )
        {
            
                if(s->phase < s->attack)
                {
                    vcoeff = ((s->attack  - (s->attack - s->phase)) / s->attack  );

                }else if(s->phase < s->attack + s->decay)
                {
                    double diff = 1.0 - (s->sustain);
                    double fact = ( s->decay - (s->decay - (s->phase - s->attack))) / s->decay  ;
                    vcoeff = (1.0 - (diff * fact)) ;
                    
                }else {
                    vcoeff = s->sustain;
                }


        }else {
            
            if(s->phase < s->release)
            {
                //signal is in release state

                if (s->release > 0.0) {
            
                    vcoeff = s->sustain * (s->release - s->phase) / s->release;
                }else {
                    vcoeff = 0.0;
                }

            }else
            {
                vcoeff = 0.0;
            }
            

            
        }
        s->vfactor += 0.01 * ((vcoeff* s->lastVelocity) - s->vfactor);
        for(int i = 0; i < buffer.getNumChannels(); i++)
        {
            currentSample = buffer.getSample(i, sampleNr) * s->vfactor;
            buffer.setSample(i, sampleNr, currentSample);
            
        }
        s->phase++;
    }
}

void *DiauproVCAProcessor::getState() {
    return this->processState;
}

size_t DiauproVCAProcessor::getStateSize() {
    return sizeof(vca_state) ;
}

void DiauproVCAProcessor::setState(void* state)
{
    memcpy(this->processState, (const void*)state, sizeof(vca_state));
}

void DiauproVCAProcessor::processNote(MidiMessage* message)
{
    if (this->processState->noteStates[message->getNoteNumber()] == (uint8)0) {
        this->processState->noteStates[message->getNoteNumber()] = message->getVelocity();
    }else{
        this->processState->noteStates[message->getNoteNumber()] = (uint8)0;
    }
}

uint8 DiauproVCAProcessor::getHighestNote()
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

bool DiauproVCAProcessor::hasNoteOn()
{
    int i = 127;
    while (i>=0 && this->processState->noteStates[i] == 0) {
        
        i--;
    }
    if (i > -1) {
        return true;
    }
    return false;
}