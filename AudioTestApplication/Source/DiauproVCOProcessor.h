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
    DiauproVCOProcessor(){
        this->processState.voice_count = 0;
        this->processState.frequency = 1.0;
        this->processState.phase = 1.0;
        this->processState.step = 1.0;
        this->processState.level = 0.7;
        this->processState.totalProcessTime = 0.0;
        this->processState.nodeProcessTime = 0.0;
    };

    virtual void *getState() override;

    virtual size_t getStateSize() override;

    void localProcess(AudioSampleBuffer &buffer, MidiBuffer &midiMessages, void* state);
    String getServiceTag() override { return "_diaprovco._udp"; } ;

private:

    struct vco_state {
        int voice_count;
        double frequency;
        double phase;
        double step;
        double level;
        double totalProcessTime;
        double nodeProcessTime;
    };

    struct vco_state processState;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DiauproVCOProcessor)
};



#endif  // DIAUPROVCOPROCESSOR_H_INCLUDED
