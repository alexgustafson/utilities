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
#include "DiauproAsyncProcessor.h"

class DiauproVCAProcessor : public DiauproAsyncProcessor
{
public:
    DiauproVCAProcessor() {
        this->processState = (vca_state*)malloc(sizeof(vca_state));
        processState->voice_count = 0;
        processState->phase = 0.0;
        processState->vfactor = 0.0;
        processState->attack = 800.0;
        processState->decay = 34000.0;
        processState->sustain = 0.2;
        processState->release = 28000;
        processState->lastVelocity = 0.0f;
        zerostruct(this->processState->noteStates);
    };

    void localProcess(AudioSampleBuffer &buffer, MidiBuffer &midiMessages, void* state) override;
    String getServiceTag() override { return "_diaprovca._udp"; } ;
    virtual void *getState() override;
    virtual size_t getStateSize() override;
    virtual void setState(void* state) override;
private:
    
    struct vca_state {
        int voice_count;
        double phase;
        double vfactor;
        double attack;
        double decay;
        double sustain;
        double release;
        double totalProcessTime;
        double nodeProcessTime;
        uint8 noteStates [128];
        float lastVelocity;
    };
    
    struct vca_state *processState;
    

    void processNote(MidiMessage* message);
    uint8 getHighestNote();
    bool hasNoteOn();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DiauproVCAProcessor)
};



#endif  // DIAUPROVCAPROCESSOR_H_INCLUDED
