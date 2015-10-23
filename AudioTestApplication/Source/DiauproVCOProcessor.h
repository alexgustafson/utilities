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
//#include "DiauproProcessor.h"
#include "DiauproAsyncProcessor.h"




class DiauproVCOProcessor : public DiauproAsyncProcessor
{
public:
    
    DiauproVCOProcessor(){
        
        this->processState = (vco_state*)calloc(1, sizeof(vco_state));
        this->processState->voice_count = 0;
        this->processState->frequency = 1.0;
        this->processState->phase = 0.0;
        this->processState->step = 1.0;
        this->processState->level = 0.95;
        this->processState->totalProcessTime = 0.0;
        this->processState->nodeProcessTime = 0.0;
        zerostruct(this->processState->noteStates);
        this->processState->lastPlayedPitch = (uint8)64;
    };

    virtual void *getState() override;

    virtual size_t getStateSize() override;
    
    virtual void setState(void* state) override;

    void localProcess(AudioSampleBuffer &buffer, MidiBuffer &midiMessages, void* state) override;
    String getServiceTag() override { return "_diaprovco._udp"; } ;
    
    MidiKeyboardState keyboardState;

private:

    struct vco_state {
        int voice_count;
        double frequency;
        double phase;
        double step;
        double level;
        double totalProcessTime;
        double nodeProcessTime;
        uint8 noteStates [128];
        uint8 lastPlayedPitch;
    };

    struct vco_state *processState;
    
    void processNote(MidiMessage* message);
    uint8 getHighestNote();


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DiauproVCOProcessor)
};



#endif  // DIAUPROVCOPROCESSOR_H_INCLUDED
