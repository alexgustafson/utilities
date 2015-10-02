/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "DiauproTestProcessor"
#include "MidiUtiliy.h"



//==============================================================================
int main (int argc, char* argv[])
{

    Monitor monitor;
    monitor.startMonitoring();
    
    MidiMessageCollector *midiCollector;
    MidiUtility midiUtility;
    
    midiCollector = midiUtility.getMidiMessageCollector();
    
    DiauproTestProcessor *diauproTestProcessor;
    diauproTestProcessor = new DiauproTestProcessor();
    diauproTestProcessor->setMonitor(&monitor);

    
    return 0;
}
