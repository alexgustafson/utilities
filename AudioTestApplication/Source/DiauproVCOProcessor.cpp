/*
  ==============================================================================

    DiauproVCOProcessor.cpp
    Created: 30 Sep 2015 3:15:24pm
    Author:  Alexander Gustafson

  ==============================================================================
*/

#include "DiauproVCOProcessor.h"

void DiauproVCOProcessor::localProcess(AudioSampleBuffer &buffer, MidiBuffer &midiMessages) {

    int sampleNr;
    int nextMidiEventCount = -1;
    MidiBuffer::Iterator midiEventIterator(midiMessages);
    MidiMessage nextMidiEvent;
    bool hasEvent;
    buffer.clear();

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
                voice_count++;
                frequency = MidiMessage::getMidiNoteInHertz(nextMidiEvent.getNoteNumber());
                double cyclesPerSample = frequency / getSampleRate();
                step = cyclesPerSample * 2.0 * double_Pi;

            } else{
                voice_count--;
            }
        }

        if(voice_count > 0)
        {
            const float currentSample = (float) (sin (phase) * level);
            phase += step;

            for(int i = 0; i < buffer.getNumChannels(); i++)
            {
                buffer.setSample(i, sampleNr, currentSample);
            }

        }
    }
}
