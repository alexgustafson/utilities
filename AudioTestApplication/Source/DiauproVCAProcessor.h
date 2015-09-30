/*
  ==============================================================================

    DiauproVCAProcessor.h
    Created: 30 Sep 2015 5:24:02pm
    Author:  Alexander Gustafson

  ==============================================================================
*/

#ifndef DIAUPROVCAPROCESSOR_H_INCLUDED
#define DIAUPROVCAPROCESSOR_H_INCLUDED

#include "JuceHeader.h"
#include "DiauproProcessor.h"

class DiauproVCAProcessor : public DiauproProcessor
{
public:
    DiauproVCAProcessor() {};

    void localProcess(AudioSampleBuffer &buffer, MidiBuffer &midiMessages);

private:
    double attackTimeInSamples = 300.0;
    double decayTimeInSamples = 3000.0;
    double sustainLevel = 0.2;
    double releaseTimeInSamples = 22050.0;

    double phase = 0.0;

    int voice_count = 0;

    String service_tag = "_vca_diapro._udp";

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DiauproVCAProcessor)
};



#endif  // DIAUPROVCAPROCESSOR_H_INCLUDED
