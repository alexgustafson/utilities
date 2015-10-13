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

    void localProcess(AudioSampleBuffer &buffer, MidiBuffer &midiMessages, void* state);
    String getServiceTag() override { return "_diaprovca._udp"; } ;

private:
    
    struct vca_state {
        int voice_count;
        double phase;
        double attack;
        double decay;
        double sustain;
        double release;
        double totalProcessTime;
        double nodeProcessTime;
    };
    
    struct vca_state processState;
    
    virtual void *getState() override;
    
    virtual size_t getStateSize() override;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DiauproVCAProcessor)
};



#endif  // DIAUPROVCAPROCESSOR_H_INCLUDED
