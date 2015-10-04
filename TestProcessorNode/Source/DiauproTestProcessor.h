/*
  ==============================================================================

    DiauproTestProcessor.h
    Created: 2 Oct 2015 4:41:38pm
    Author:  Alexander Gustafson

  ==============================================================================
*/

#ifndef DIAUPROTESTPROCESSOR_H_INCLUDED
#define DIAUPROTESTPROCESSOR_H_INCLUDED

#include "JuceHeader.h"
#include "DiauproProcessor.h"

class DiauproTestProcessor : public DiauproProcessor {
public:
    DiauproTestProcessor() {};

    void localProcess(AudioSampleBuffer &buffer, MidiBuffer &midiMessages) override;

    String getServiceTag() override {
        return "_diaproTest._udp";
    };
    
    int data_returned;
    
    void processAudioWrapper(AudioSampleBuffer &buffer, MidiBuffer &midiMessages);

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DiauproTestProcessor)

};


#endif  // DIAUPROTESTPROCESSOR_H_INCLUDED
