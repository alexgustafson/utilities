/*
  ==============================================================================

    DiauproTestProcessor.cpp
    Created: 2 Oct 2015 4:41:38pm
    Author:  Alexander Gustafson

  ==============================================================================
*/

#include "DiauproTestProcessor.h"

void DiauproTestProcessor::localProcess(AudioSampleBuffer &buffer, MidiBuffer &midiMessages) {
    
    for (int i = 0; i < buffer.getNumChannels(); i++) {
        for (int j = 0; j < buffer.getNumSamples(); j++) {
            Logger::writeToLog(String::formatted("sample %d %d value %f",i,j,buffer.getSample(i, j)));
        }
    }
    
    Logger::writeToLog(this->getCurrentMessage()->headerToString());

    MidiBuffer::Iterator midiEventIterator(midiMessages);
    MidiMessage nextMidiEvent;

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
            Logger::writeToLog(String::formatted("Midi Note Found:\n channel: %d\n nr : %d\n vel: %f", nextMidiEvent.getChannel(), nextMidiEvent.getNoteNumber(), nextMidiEvent.getFloatVelocity()));
        }
    }

}

void DiauproTestProcessor::processAudioWrapper(AudioSampleBuffer &buffer, MidiBuffer &midiMessages)
{
    data_returned = 0;
    this->processBlock(buffer, midiMessages);
    data_returned = 1;
}
