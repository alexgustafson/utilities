/*
  ==============================================================================

    This file was auto-generated by the Introjucer!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
DiauproPluginAudioProcessorEditor::DiauproPluginAudioProcessorEditor (DiauproPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    addAndMakeVisible(gui = new DiauproGUI());
    setSize (400, 300);
}

DiauproPluginAudioProcessorEditor::~DiauproPluginAudioProcessorEditor()
{
}

//==============================================================================
void DiauproPluginAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll (Colours::white);

    g.setColour (Colours::black);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), Justification::centred, 1);
}

void DiauproPluginAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    gui->setSize(getWidth(), getHeight());
    // subcomponents in your editor..
}
