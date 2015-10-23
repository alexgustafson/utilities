/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#ifndef MAINCOMPONENT_H_INCLUDED
#define MAINCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "DiauproProcessor.h"
#include "MidiUtiliy.h"
#include "DiauproVCOProcessor.h"
#include "DiauproVCAProcessor.h"
#include "DiauproNULLProcessor.h"
#include "DiauproAsyncProcessor.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainContentComponent   : public AudioAppComponent
{
public:
    //==============================================================================
    MainContentComponent()
    {
        setSize (600, 250);

        // specify the number of input and output channels that we want to open
        midiCollector = midiUtility.getMidiMessageCollector();
        
        monitor.startMonitoring();

        diauproNullProcessor = new DiauproNullProcessor();
        diauproNullProcessor->setMonitor(&monitor);

        diauproVCOProcessor = new DiauproVCOProcessor();
        diauproVCOProcessor->setMonitor(&monitor);

        diauproVCAProcessor = new DiauproVCAProcessor();
        diauproVCAProcessor->setMonitor(&monitor);
        
        diauproAsyncProcessor = new DiauproAsyncProcessor();
        diauproAsyncProcessor->setMonitor(&monitor);
        diauproAsyncProcessor->initializeRingBuffers(2, 44100);
        setAudioChannels (2, 2);
        
    }

    ~MainContentComponent()
    {
        shutdownAudio();
        monitor.stop();
        

        
    }

    //=======================================================================
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override
    {
        // This function will be called when the audio device is started, or when
        // its settings (i.e. sample rate, block size, etc) are changed.

        // You can use this function to initialise any resources you might need,
        // but be careful - it will be called on the audio thread, not the GUI thread.

        // For more details, see the help for AudioProcessor::prepareToPlay()
        midiCollector->reset (sampleRate);

        diauproNullProcessor->prepareToPlay(sampleRate, samplesPerBlockExpected);
        diauproVCOProcessor->prepareToPlay(sampleRate, samplesPerBlockExpected);
        diauproVCAProcessor->prepareToPlay(sampleRate, samplesPerBlockExpected);
        diauproAsyncProcessor->prepareToPlay(sampleRate, samplesPerBlockExpected);

    }

    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override
    {
        // Your audio-processing code goes here!

        // For more details, see the help for AudioProcessor::getNextAudioBlock()

        // Right now we are not producing any data, in which case we need to clear the buffer
        // (to prevent the output of random noise)
        //bufferToFill.clearActiveBufferRegion();
        MidiBuffer incomingMidi;
        midiCollector->removeNextBlockOfMessages (incomingMidi, bufferToFill.numSamples);

        diauproNullProcessor->processBlock(*bufferToFill.buffer, incomingMidi);
        diauproVCOProcessor->processBlock(*bufferToFill.buffer, incomingMidi);
        diauproVCAProcessor->processBlock(*bufferToFill.buffer, incomingMidi);
        diauproAsyncProcessor->processBlock(*bufferToFill.buffer, incomingMidi);

    }

    void releaseResources() override
    {
        // This will be called when the audio device stops, or when it is being
        // restarted due to a setting change.

        // For more details, see the help for AudioProcessor::releaseResources()

    }

    //=======================================================================
    void paint (Graphics& g) override
    {
        // (Our component is opaque, so we must completely fill the background with a solid colour)
        g.fillAll (Colours::black);


        // You can add your drawing code here!
    }

    void resized() override
    {
        // This is called when the MainContentComponent is resized.
        // If you add any child components, this is where you should
        // update their positions.
    }


private:
    //==============================================================================

    // Your private member variables go here...
    Monitor monitor;
    MidiMessageCollector *midiCollector;
    MidiUtility midiUtility;

    ScopedPointer<DiauproVCOProcessor> diauproVCOProcessor;
    ScopedPointer<DiauproVCAProcessor> diauproVCAProcessor;
    ScopedPointer<DiauproNullProcessor> diauproNullProcessor;
    ScopedPointer<DiauproAsyncProcessor> diauproAsyncProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};


// (This function is called by the app startup code to create our main component)
Component* createMainContentComponent()     { return new MainContentComponent(); }


#endif  // MAINCOMPONENT_H_INCLUDED
