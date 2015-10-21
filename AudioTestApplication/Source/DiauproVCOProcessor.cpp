/*
  ==============================================================================

    DiauproVCOProcessor.cpp
    Created: 30 Sep 2015 3:15:24pm
    Author:  Alexander Gustafson

  ==============================================================================
*/

#include "DiauproVCOProcessor.h"

void DiauproVCOProcessor::localProcess(AudioSampleBuffer &buffer, MidiBuffer &midiMessages, void* state) {
    this->processState = (vco_state *)state;
    int sampleNr;
    int nextMidiEventCount = -1;
    MidiBuffer::Iterator midiEventIterator(midiMessages);
    MidiMessage nextMidiEvent;
    bool hasEvent;
    float currentSample;
    
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
                processState->phase = 0.0;
                processState->voice_count++;
                processState->frequency = MidiMessage::getMidiNoteInHertz(nextMidiEvent.getNoteNumber());
                double cyclesPerSample = processState->frequency / getSampleRate();
                processState->step = cyclesPerSample * 2.0 * double_Pi;

            } else{
                processState->voice_count--;
                processState->phase = 0.0;

            }
        }

        if(this->processState->voice_count > 0)
        {
            
            currentSample = (float) ( processState->phase * processState->level);
            currentSample = sind(currentSample);
            
            processState->phase += processState->step;
            for(int i = 0; i < buffer.getNumChannels(); i++)
            {
                float oldSample = buffer.getSample(i, sampleNr);
                buffer.setSample(i, sampleNr, (currentSample + oldSample)*0.5);
            }

        }
    }
}

void *DiauproVCOProcessor::getState() {
    return this->processState;
}

size_t DiauproVCOProcessor::getStateSize() {
    return sizeof(vco_state) ;
}

void DiauproVCOProcessor::setState(void* state)
{
    this->processState = (vco_state*)state;
}
