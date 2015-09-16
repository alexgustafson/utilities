/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#ifndef MAINCOMPONENT_H_INCLUDED
#define MAINCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "NetworkBrowser.h"
#include "TestProcess.h"

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
        setSize (800, 600);

        // specify the number of input and output channels that we want to open

        
        monitor.startMonitoring();
        
        addAndMakeVisible (networkBrowserComponent);
        networkBrowserComponent.setBounds(0, 0, getWidth(), getHeight());
        networkBrowserComponent.initializeWithMonitor(&monitor);
        
        ioProcIn = new AudioProcessorGraph::AudioGraphIOProcessor (AudioProcessorGraph::AudioGraphIOProcessor::audioInputNode);
        ioProcOut = new AudioProcessorGraph::AudioGraphIOProcessor (AudioProcessorGraph::AudioGraphIOProcessor::audioOutputNode);
        
        ioProcMidiIn = new AudioProcessorGraph::AudioGraphIOProcessor (AudioProcessorGraph::AudioGraphIOProcessor::midiInputNode);
        
        ioProcInNode = graph.addNode(ioProcIn);
        ioProcOutNode = graph.addNode (ioProcOut);
        ioProcMidiInNode = graph.addNode (ioProcMidiIn);
        
        AudioProcessorGraph::Node* sbNode = graph.addNode (testProcess = new TestProcess());
        testProcess->setNodeID (sbNode->nodeId);
        

        setAudioChannels (2, 2);
    }

    ~MainContentComponent()
    {
        monitor.stop();
        
        shutdownAudio();
        
    }

    //=======================================================================
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override
    {
        // This function will be called when the audio device is started, or when
        // its settings (i.e. sample rate, block size, etc) are changed.

        // You can use this function to initialise any resources you might need,
        // but be careful - it will be called on the audio thread, not the GUI thread.

        // For more details, see the help for AudioProcessor::prepareToPlay()
        midiCollector.reset (sampleRate);
        graph.setPlayConfigDetails(2, 2, sampleRate, samplesPerBlockExpected);
        graph.prepareToPlay(sampleRate, samplesPerBlockExpected);
        
        graph.addConnection(testProcess->getNodeID(), 0, ioProcOutNode->nodeId, 0);
        graph.addConnection(testProcess->getNodeID(), 1, ioProcOutNode->nodeId, 1);
        
        //graph.addConnection(ioProcInNode->nodeId, 0, testProcess->getNodeID(), 0);
        //graph.addConnection(ioProcInNode->nodeId, 1, testProcess->getNodeID(), 1);
        
        testProcess->prepareToPlay(sampleRate, samplesPerBlockExpected);
        
    }

    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override
    {
        // Your audio-processing code goes here!

        // For more details, see the help for AudioProcessor::getNextAudioBlock()

        // Right now we are not producing any data, in which case we need to clear the buffer
        // (to prevent the output of random noise)
        //bufferToFill.clearActiveBufferRegion();
        MidiBuffer incomingMidi;
        midiCollector.removeNextBlockOfMessages (incomingMidi, bufferToFill.numSamples);
        //graph.processBlock(*bufferToFill.buffer, incomingMidi);
        testProcess->processBlock(*bufferToFill.buffer, incomingMidi);
        
    }

    void releaseResources() override
    {
        // This will be called when the audio device stops, or when it is being
        // restarted due to a setting change.

        // For more details, see the help for AudioProcessor::releaseResources()
        graph.releaseResources();
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
        networkBrowserComponent.setBounds(0, 0, getWidth(), getHeight());
    }


private:
    //==============================================================================

    // Your private member variables go here...
    NetworkBrowser networkBrowserComponent;
    
    Monitor monitor;
    MidiMessageCollector midiCollector;
    
    AudioProcessorGraph graph;
    
    AudioProcessorGraph::AudioGraphIOProcessor* ioProcIn;
    AudioProcessorGraph::AudioGraphIOProcessor* ioProcOut;
    AudioProcessorGraph::AudioGraphIOProcessor* ioProcMidiIn;
    
    AudioProcessorGraph::Node* ioProcInNode;
    AudioProcessorGraph::Node* ioProcOutNode;
    AudioProcessorGraph::Node* ioProcMidiInNode;
    
    TestProcess *testProcess;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};


// (This function is called by the app startup code to create our main component)
Component* createMainContentComponent()     { return new MainContentComponent(); }


#endif  // MAINCOMPONENT_H_INCLUDED
