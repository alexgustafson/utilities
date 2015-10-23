/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/

#include "JuceHeader.h"
#include "Monitor.h"
#include "DiauproProcessor.h"
#include "DiauproVCAProcessor.h"
#include "DiauproVCOProcessor.h"
#include "DiauproNullProcessor.h"
#include "DiauproAsyncProcessor.h"

//==============================================================================
int main (int argc, char* argv[])
{

    // ..your code goes here!
    Monitor monitor;
    monitor.startMonitoring();

    ScopedPointer<DiauproNullProcessor> diauproNullProcessor;
    diauproNullProcessor = new DiauproNullProcessor();
    diauproNullProcessor->setMonitor(&monitor, true);

    ScopedPointer<DiauproVCOProcessor> diauproVCOProcessor;
    diauproVCOProcessor = new DiauproVCOProcessor();
    diauproVCOProcessor->setMonitor(&monitor, true);

    ScopedPointer<DiauproVCAProcessor> diauproVCAProcessor;
    diauproVCAProcessor = new DiauproVCAProcessor();
    diauproVCAProcessor->setMonitor(&monitor, true);
    
    ScopedPointer<DiauproAsyncProcessor> diauproAsyncProcessor;
    diauproAsyncProcessor = new DiauproAsyncProcessor();
    diauproAsyncProcessor->setMonitor(&monitor, true);
    
    std::cout << "press enter to exit...";
    getchar();
    
    monitor.stop();
    
    return 0;
}
