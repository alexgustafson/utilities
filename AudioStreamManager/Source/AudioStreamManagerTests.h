/*
  ==============================================================================

    AudioStreamManagerTests.h
    Created: 3 Sep 2015 4:37:03pm
    Author:  Alexander Gustafson

  ==============================================================================
*/

#ifndef AUDIOSTREAMMANAGERTESTS_H_INCLUDED
#define AUDIOSTREAMMANAGERTESTS_H_INCLUDED

#include "JuceHeader.h"

class AudioStreamManagerTests : public UnitTest {
public:
    AudioStreamManagerTests() : UnitTest("") {
        pool = new ThreadPool();
    }

    void firstTest();
    void runTest();

private:
    ScopedPointer<ThreadPool> pool;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AudioStreamManagerTests)
};


#endif  // AUDIOSTREAMMANAGERTESTS_H_INCLUDED
