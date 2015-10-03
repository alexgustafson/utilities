/*
  ==============================================================================

    DiauproTestProcessor.cpp
    Created: 2 Oct 2015 4:41:38pm
    Author:  Alexander Gustafson

  ==============================================================================
*/

#include "DiauproTestProcessor.h"

void DiauproTestProcessor::localProcess(AudioSampleBuffer &buffer, MidiBuffer &midiMessages) {

    Logger::writeToLog(String::formatted("Audio Channel Count: %d",buffer.getNumChannels()));
    Logger::writeToLog(String::formatted("Audio Sample Count: %d",buffer.getNumSamples()));

    MidiBuffer::Iterator midiEventIterator(midiMessages);
    MidiMessage nextMidiEvent;
    bool hasEvent;
    int nextMidiEventPosition = -1;

    while(midiEventIterator.getNextEvent(nextMidiEvent, nextMidiEventPosition))
    {
        if(nextMidiEvent.isNoteOnOrOff())
        {
            Logger::writeToLog(String::formatted("Midi Note Found:\n channel: %d\n nr : %d\n vel: %d", nextMidiEvent.getChannel(), nextMidiEvent.getNoteNumber(), nextMidiEvent.getFloatVelocity()));
        }
    }

}
