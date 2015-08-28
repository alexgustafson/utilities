/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/

#include "JuceHeader.h"
#include "ZeroConfTests.h"

//==============================================================================
int main (int argc, char* argv[])
{

    static ZeroConfTests zeroConfTests;
    UnitTestRunner runner;
    runner.setAssertOnFailure(false);
    runner.runAllTests();

    return 0;
}
