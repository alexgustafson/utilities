/*
  ==============================================================================

    DiauproVCOProcessor.cpp
    Created: 30 Sep 2015 3:15:24pm
    Author:  Alexander Gustafson

  ==============================================================================
*/

#include "DiauproVCOProcessor.h"

void DiauproVCOProcessor::localProcess(AudioSampleBuffer &buffer, MidiBuffer &midiMessages, void* state) {

    this->processState = *(vco_state*)state;
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
            if(nextMidiEvent.isNoteOn())
            {
                this->processState.voice_count++;
                this->processState.frequency = MidiMessage::getMidiNoteInHertz(nextMidiEvent.getNoteNumber());
                double cyclesPerSample = this->processState.frequency / getSampleRate();
                this->processState.step = cyclesPerSample * 2.0 * double_Pi;

            } else{
                this->processState.voice_count--;
            }
        }

        if(this->processState.voice_count > 0)
        {
            const float currentSample = (float) (sin (this->processState.phase) * this->processState.level);
            this->processState.phase += this->processState.step;
            for(int i = 0; i < buffer.getNumChannels(); i++)
            {
                float oldSample = buffer.getSample(i, sampleNr);
                buffer.setSample(i, sampleNr, (currentSample + oldSample)*0.5);
            }

        }
    }
}

void *DiauproVCOProcessor::getState() {
    return &this->processState;
}

size_t DiauproVCOProcessor::getStateSize() {
    return sizeof(vco_state) ;
}
