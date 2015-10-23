/*
  ==============================================================================

    MidiUtiliy.h
    Created: 30 Sep 2015 9:33:41am
    Author:  Alexander Gustafson

  ==============================================================================
*/

#ifndef MIDIUTILIY_H_INCLUDED
#define MIDIUTILIY_H_INCLUDED

#include "JuceHeader.h"

class MidiUtility : public MidiInputCallback {
public:

    MidiUtility();

    void handleIncomingMidiMessage (MidiInput *source, const MidiMessage &message) override;
    MidiMessageCollector* getMidiMessageCollector();

private:

    MidiMessageCollector midiMessageCollector;
    ScopedPointer<MidiInput> midiInput;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MidiUtility)

};


#endif  // MIDIUTILIY_H_INCLUDED
