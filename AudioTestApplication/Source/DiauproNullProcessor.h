/*
  ==============================================================================

    DiauproNullProcessor.h
    Created: 21 Oct 2015 1:41:08pm
    Author:  Alexander Gustafson

  ==============================================================================
*/

#ifndef DIAUPRONULLPROCESSOR_H_INCLUDED
#define DIAUPRONULLPROCESSOR_H_INCLUDED

#include "JuceHeader.h"
//#include "DiauproProcessor.h"
#include "DiauproAsyncProcessor.h"

class DiauproNullProcessor : public DiauproAsyncProcessor
{
public:
    DiauproNullProcessor() {
        this->processState = (null_state*)malloc(sizeof(null_state));
    };
    
    void localProcess(AudioSampleBuffer &buffer, MidiBuffer &midiMessages, void* state);
    String getServiceTag() override { return "_diaupronull._udp"; } ;
    virtual void *getState() override;
    virtual size_t getStateSize() override;
    virtual void setState(void* state) override;
private:
    
    struct null_state {
        double totalProcessTime;
        double nodeProcessTime;
    };
    
    struct null_state *processState;
    

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DiauproNullProcessor)
};



#endif  // DIAUPRONULLPROCESSOR_H_INCLUDED
