/*
  ==============================================================================

    AudioFifoBuffer.h
    Created: 3 Sep 2015 5:04:02pm
    Author:  Alexander Gustafson

  ==============================================================================
*/

#ifndef AUDIOFIFOBUFFER_H_INCLUDED
#define AUDIOFIFOBUFFER_H_INCLUDED

#include "JuceHeader.h"

class AudioFifoBuffer {

private:
    AbstractFifo abstractFifo;
    HeapBlock<float> buffer;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioFifoBuffer);
};

#endif  // AUDIOFIFOBUFFER_H_INCLUDED
