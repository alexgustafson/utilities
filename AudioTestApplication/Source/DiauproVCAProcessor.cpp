/*
  ==============================================================================

    DiauproVCAProcessor.cpp
    Created: 30 Sep 2015 5:24:02pm
    Author:  Alexander Gustafson

  ==============================================================================
*/

#include "DiauproVCAProcessor.h"

void DiauproVCAProcessor::localProcess(AudioSampleBuffer &buffer, MidiBuffer &midiMessages) {
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
            phase = 0.0;
            if(nextMidiEvent.isNoteOn())
            {
                voice_count++;

            } else{
                voice_count--;
            }
        }

        if(voice_count > 0)
        {
            float currentSample;

            for(int i = 0; i < buffer.getNumChannels(); i++)
            {
                currentSample = buffer.getSample(i, sampleNr);

                //process current sample here
                if(phase < attackTimeInSamples)
                {
                    currentSample = currentSample * ((attackTimeInSamples  - (attackTimeInSamples - phase)) / attackTimeInSamples  );


                }else if(phase < attackTimeInSamples + decayTimeInSamples)
                {
                    double diff = 1.0 - (sustainLevel);
                    double fact = ( decayTimeInSamples - (decayTimeInSamples - (phase - attackTimeInSamples))) / decayTimeInSamples  ;
                    currentSample = currentSample * (1.0 - (diff * fact));
                }else {
                    currentSample = currentSample * sustainLevel;
                }


                buffer.setSample(i, sampleNr, currentSample);
                phase++;
            }

        }else {
            if(phase < attackTimeInSamples + decayTimeInSamples + releaseTimeInSamples)
            {
                //signal is in release state

                float currentSample;

                for(int i = 0; i < buffer.getNumChannels(); i++)
                {
                    currentSample = buffer.getSample(i, sampleNr);

                    //process current sample here



                    buffer.setSample(i, sampleNr, currentSample);
                    phase++;
                }
            }
        }
    }}
