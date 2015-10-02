/*
  ==============================================================================

    MidiUtiliy.cpp
    Created: 30 Sep 2015 9:33:41am
    Author:  Alexander Gustafson

  ==============================================================================
*/

#include "MidiUtiliy.h"

MidiUtility::MidiUtility() {

    StringArray devices = MidiInput::getDevices();

    Logger::writeToLog("** scanning midi ports **");

    for(int i = 0; i < devices.size(); i++)
    {
        Logger::writeToLog(devices[i]);
    }

    if(devices.size() > 1)
    {
        midiInput = MidiInput::openDevice(0, this);
        midiInput->start();
    }

}

void MidiUtility::handleIncomingMidiMessage(MidiInput *source, const MidiMessage &message) {

    midiMessageCollector.addMessageToQueue(message);
}

MidiMessageCollector *MidiUtility::getMidiMessageCollector() {
    return &this->midiMessageCollector;
}
