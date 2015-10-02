/*
  ==============================================================================

    DiauproVCOProcessor.h
    Created: 30 Sep 2015 3:15:24pm
    Author:  Alexander Gustafson

  ==============================================================================
*/

#ifndef DIAUPROVCOPROCESSOR_H_INCLUDED
#define DIAUPROVCOPROCESSOR_H_INCLUDED

#include "JuceHeader.h"
#include "DiauproProcessor.h"

class DiauproVCOProcessor : public DiauproProcessor
{
public:
    DiauproVCOProcessor(){};

    void localProcess(AudioSampleBuffer &buffer, MidiBuffer &midiMessages);
    String getServiceTag() override { return "_diaprovco._udp"; } ;

private:

    int voice_count = 0;
    double frequency = 1.0;
    double phase = 1.0;
    double step = 1.0;
    double level = 0.7;



    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DiauproVCOProcessor)
};



#endif  // DIAUPROVCOPROCESSOR_H_INCLUDED
