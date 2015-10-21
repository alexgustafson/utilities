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

    for(sampleNr = 0; sampleNr < buffer.getNumSamples(); sampleNr++)
    {
        if(nextMidiEventCount < sampleNr)
        {
            hasEvent = midiEventIterator.getNextEvent(nextMidiEvent,nextMidiEventCount );
        }

        if(hasEvent && nextMidiEventCount == sampleNr)
        {
            s->phase = 0.0;
            if(nextMidiEvent.isNoteOn())
            {
                s->voice_count++;

            } else{
                s->voice_count--;
            }
        }

        if(s->voice_count > 0)
        {
            float currentSample;

            for(int i = 0; i < buffer.getNumChannels(); i++)
            {
                currentSample = buffer.getSample(i, sampleNr);

                //process current sample here
                if(s->phase < s->attack)
                {
                    currentSample = currentSample * ((s->attack  - (s->attack - s->phase)) / s->attack  );


                }else if(s->phase < s->attack + s->decay)
                {
                    double diff = 1.0 - (s->sustain);
                    double fact = ( s->decay - (s->decay - (s->phase - s->attack))) / s->decay  ;
                    currentSample = currentSample * (1.0 - (diff * fact));
                }else {
                    currentSample = currentSample * s->sustain;
                }


                buffer.setSample(i, sampleNr, currentSample);
                s->phase++;
            }

        }else {
            if(s->phase < s->attack + s->decay + s->release)
            {
                //signal is in release state

                float currentSample;

                for(int i = 0; i < buffer.getNumChannels(); i++)
                {
                    currentSample = buffer.getSample(i, sampleNr);

                    //process current sample here

                    buffer.setSample(i, sampleNr, currentSample);
                    s->phase++;
                }
            }
        }
    }}

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