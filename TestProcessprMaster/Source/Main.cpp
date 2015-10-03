/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"

#include "ConsolidatedTests.h"


//==============================================================================
int main (int argc, char* argv[])
{

    static ConsolidatedTests consolidatedTests;
    UnitTestRunner runner;
    runner.setAssertOnFailure(false);
    runner.runAllTests();

    
    return 0;
}
