/*
  ==============================================================================

    DiaproMessageTests.h
    Created: 26 Sep 2015 2:10:47pm
    Author:  Alexander Gustafson

  ==============================================================================
*/

#ifndef DIAPROMESSAGETESTS_H_INCLUDED
#define DIAPROMESSAGETESTS_H_INCLUDED

#include "JuceHeader.h"
#include "DiauproMessage.h"

class DiauproMessageTest : public UnitTest
{
public:
    DiauproMessageTest() : UnitTest(""){}
    void firstTest();
    void secondTest();
    void thirdTest();
    void runTest();

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DiauproMessageTest)
};



#endif  // DIAPROMESSAGETESTS_H_INCLUDED
