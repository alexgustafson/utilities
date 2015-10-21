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
    Logger::writeToLog(String(s->toba));
    int sampleNr;
    int nextMidiEventCount = -1;
    MidiBuffer::Iterator midiEventIterator(midiMessages);
    MidiMessage nextMidiEvent;
    bool hasEvent;
    double currentSample;
    
    for(sampleNr = 0; sampleNr < buffer.getNumSamples(); sampleNr++)
    {
        if(nextMidiEventCount < sampleNr)
        {
            hasEvent = midiEventIterator.getNextEvent(nextMidiEvent,nextMidiEventCount );
        }

        if(hasEvent && nextMidiEventCount == sampleNr)
        {
            if(nextMidiEvent.isNoteOn())
            {
                s->phase = 0.0;
                s->voice_count++;
                s->frequency = MidiMessage::getMidiNoteInHertz(nextMidiEvent.getNoteNumber());
                double cyclesPerSample = s->frequency / getSampleRate();
                s->step = cyclesPerSample * 2.0 * double_Pi;

            } else{
                s->voice_count--;
                s->phase = 0.0;

            }
        }

        if(this->processState->voice_count > 0)
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
