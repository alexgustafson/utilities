/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "Monitor.h"
#include "DiauproTestProcessor.h"

//==============================================================================
int main(int argc, char *argv[]) {

    Monitor monitor;
    monitor.startMonitoring();

    ScopedPointer<DiauproTestProcessor> diauproTestProcessor;
    diauproTestProcessor = new DiauproTestProcessor();
    diauproTestProcessor->setMonitor(&monitor, true);


    std::cout << "press enter to exit...";
    getchar();

    monitor.stop();
    return 0;
}
