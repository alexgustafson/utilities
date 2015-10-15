/*
  ==============================================================================

    DiauproVCAProcessor.cpp
    Created: 30 Sep 2015 5:24:02pm
    Author:  Alexander Gustafson

  ==============================================================================
*/

#include "DiauproVCAProcessor.h"

void DiauproVCAProcessor::localProcess(AudioSampleBuffer &buffer, MidiBuffer &midiMessages, void* state) {
    this->processState = (vca_state*)state;
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
            processState->phase = 0.0;
            if(nextMidiEvent.isNoteOn())
            {
                processState->voice_count++;

            } else{
                processState->voice_count--;
            }
        }

        if(processState->voice_count > 0)
        {
            float currentSample;

            for(int i = 0; i < buffer.getNumChannels(); i++)
            {
                currentSample = buffer.getSample(i, sampleNr);

                //process current sample here
                if(processState->phase < processState->attack)
                {
                    currentSample = currentSample * ((processState->attack  - (processState->attack - processState->phase)) / processState->attack  );


                }else if(processState->phase < processState->attack + processState->decay)
                {
                    double diff = 1.0 - (processState->sustain);
                    double fact = ( processState->decay - (processState->decay - (processState->phase - processState->attack))) / processState->decay  ;
                    currentSample = currentSample * (1.0 - (diff * fact));
                }else {
                    currentSample = currentSample * processState->sustain;
                }


                buffer.setSample(i, sampleNr, currentSample);
                processState->phase++;
            }

        }else {
            if(processState->phase < processState->attack + processState->decay + processState->release)
            {
                //signal is in release state

                float currentSample;

                for(int i = 0; i < buffer.getNumChannels(); i++)
                {
                    currentSample = buffer.getSample(i, sampleNr);

                    //process current sample here

                    buffer.setSample(i, sampleNr, currentSample);
                    processState->phase++;
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
    this->processState = (vca_state*)state;
}