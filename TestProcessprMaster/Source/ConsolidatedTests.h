/*
  ==============================================================================

    ConsolidatedTests.h
    Created: 3 Oct 2015 12:49:15pm
    Author:  Alexander Gustafson

  ==============================================================================
*/

#ifndef CONSOLIDATEDTESTS_H_INCLUDED
#define CONSOLIDATEDTESTS_H_INCLUDED

#include "JuceHeader.h"
#include "DiauproTestProcessor.h"
#include "DiauproTestProcessor.h"
#include "MidiUtiliy.h"

class ConsolidatedTests : public UnitTest {
public:
    ConsolidatedTests() : UnitTest("") {};

    void firstTest();

    void runTest();

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ConsolidatedTests)
};


#endif  // CONSOLIDATEDTESTS_H_INCLUDED
