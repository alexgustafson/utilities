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
    
    Logger::writeToLog(this->getCurrentMessage()->headerToString());

    MidiBuffer::Iterator midiEventIterator(midiMessages);
    MidiMessage nextMidiEvent;
    bool hasEvent;
    int nextMidiEventPosition = -1;


    Logger::writeToLog("Midi Dump:");
    for(int i = 0; i < midiMessages.data.size(); i++)
    {
        Logger::writeToLog(String::formatted("  %d", midiMessages.data[i]));
    }
    Logger::writeToLog("End Midi Dump:");

    while(midiEventIterator.getNextEvent(nextMidiEvent, nextMidiEventPosition))
    {
        if(nextMidiEvent.isNoteOnOrOff())
        {
            Logger::writeToLog(String::formatted("Midi Note Found:\n channel: %d\n nr : %d\n vel: %d", nextMidiEvent.getChannel(), nextMidiEvent.getNoteNumber(), nextMidiEvent.getFloatVelocity()));
        }
    }

}

void DiauproTestProcessor::processAudioWrapper(AudioSampleBuffer &buffer, MidiBuffer &midiMessages)
{
    data_returned = 0;
    this->processBlock(buffer, midiMessages);
    data_returned = 1;
}
