/*
  ==============================================================================

  This is an automatically generated GUI class created by the Introjucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Introjucer version: 3.2.0

  ------------------------------------------------------------------------------

  The Introjucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright (c) 2015 - ROLI Ltd.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "GUI.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
DiauproGUI::DiauproGUI ()
{
    //[Constructor_pre] You can add your own custom stuff here..

    //[/Constructor_pre]

    addAndMakeVisible (label = new Label ("new label",
                                          TRANS("Round Trip TIme:")));
    label->setFont (Font (15.00f, Font::plain));
    label->setJustificationType (Justification::centredLeft);
    label->setEditable (false, false, false);
    label->setColour (TextEditor::textColourId, Colours::black);
    label->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (vcoRtTimeDisplay = new Label ("time label",
                                                     TRANS("0ms")));
    vcoRtTimeDisplay->setFont (Font (15.00f, Font::plain));
    vcoRtTimeDisplay->setJustificationType (Justification::centredLeft);
    vcoRtTimeDisplay->setEditable (false, false, false);
    vcoRtTimeDisplay->setColour (TextEditor::textColourId, Colours::black);
    vcoRtTimeDisplay->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label2 = new Label ("new label",
                                           TRANS("VCO Block:")));
    label2->setFont (Font (15.00f, Font::bold));
    label2->setJustificationType (Justification::centredLeft);
    label2->setEditable (false, false, false);
    label2->setColour (TextEditor::textColourId, Colours::black);
    label2->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (vcoNetworkStatusComponent = new NetConnectivityIcon());
    addAndMakeVisible (label3 = new Label ("new label",
                                           TRANS("Max Trip TIme:")));
    label3->setFont (Font (15.00f, Font::plain));
    label3->setJustificationType (Justification::centredLeft);
    label3->setEditable (false, false, false);
    label3->setColour (TextEditor::textColourId, Colours::black);
    label3->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label4 = new Label ("new label",
                                           TRANS("Min Trip TIme:")));
    label4->setFont (Font (15.00f, Font::plain));
    label4->setJustificationType (Justification::centredLeft);
    label4->setEditable (false, false, false);
    label4->setColour (TextEditor::textColourId, Colours::black);
    label4->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (textButton = new TextButton ("new button"));
    textButton->setButtonText (TRANS("reset"));
    textButton->addListener (this);

    addAndMakeVisible (vcoMaxRtTimeLabel = new Label ("time label",
                                                      TRANS("0ms")));
    vcoMaxRtTimeLabel->setFont (Font (15.00f, Font::plain));
    vcoMaxRtTimeLabel->setJustificationType (Justification::centredLeft);
    vcoMaxRtTimeLabel->setEditable (false, false, false);
    vcoMaxRtTimeLabel->setColour (TextEditor::textColourId, Colours::black);
    vcoMaxRtTimeLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (vcoMinRtTimeLabel = new Label ("time label",
                                                      TRANS("0ms")));
    vcoMinRtTimeLabel->setFont (Font (15.00f, Font::plain));
    vcoMinRtTimeLabel->setJustificationType (Justification::centredLeft);
    vcoMinRtTimeLabel->setEditable (false, false, false);
    vcoMinRtTimeLabel->setColour (TextEditor::textColourId, Colours::black);
    vcoMinRtTimeLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label5 = new Label ("new label",
                                           TRANS("Process TIme:")));
    label5->setFont (Font (15.00f, Font::plain));
    label5->setJustificationType (Justification::centredLeft);
    label5->setEditable (false, false, false);
    label5->setColour (TextEditor::textColourId, Colours::black);
    label5->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (vcoPrTimeDisplay = new Label ("time label",
                                                     TRANS("0ms")));
    vcoPrTimeDisplay->setFont (Font (15.00f, Font::plain));
    vcoPrTimeDisplay->setJustificationType (Justification::centredLeft);
    vcoPrTimeDisplay->setEditable (false, false, false);
    vcoPrTimeDisplay->setColour (TextEditor::textColourId, Colours::black);
    vcoPrTimeDisplay->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label6 = new Label ("new label",
                                           TRANS("Round Trip TIme:")));
    label6->setFont (Font (15.00f, Font::plain));
    label6->setJustificationType (Justification::centredLeft);
    label6->setEditable (false, false, false);
    label6->setColour (TextEditor::textColourId, Colours::black);
    label6->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (vcaRtTimeDisplay = new Label ("time label",
                                                     TRANS("0ms")));
    vcaRtTimeDisplay->setFont (Font (15.00f, Font::plain));
    vcaRtTimeDisplay->setJustificationType (Justification::centredLeft);
    vcaRtTimeDisplay->setEditable (false, false, false);
    vcaRtTimeDisplay->setColour (TextEditor::textColourId, Colours::black);
    vcaRtTimeDisplay->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label7 = new Label ("new label",
                                           TRANS("VCA Block:")));
    label7->setFont (Font (15.00f, Font::bold));
    label7->setJustificationType (Justification::centredLeft);
    label7->setEditable (false, false, false);
    label7->setColour (TextEditor::textColourId, Colours::black);
    label7->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (vcaNetworkStatusComponent = new NetConnectivityIcon());
    addAndMakeVisible (label8 = new Label ("new label",
                                           TRANS("Max Trip TIme:")));
    label8->setFont (Font (15.00f, Font::plain));
    label8->setJustificationType (Justification::centredLeft);
    label8->setEditable (false, false, false);
    label8->setColour (TextEditor::textColourId, Colours::black);
    label8->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label9 = new Label ("new label",
                                           TRANS("Min Trip TIme:")));
    label9->setFont (Font (15.00f, Font::plain));
    label9->setJustificationType (Justification::centredLeft);
    label9->setEditable (false, false, false);
    label9->setColour (TextEditor::textColourId, Colours::black);
    label9->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (vcaMaxRtTimeLabel = new Label ("time label",
                                                      TRANS("0ms")));
    vcaMaxRtTimeLabel->setFont (Font (15.00f, Font::plain));
    vcaMaxRtTimeLabel->setJustificationType (Justification::centredLeft);
    vcaMaxRtTimeLabel->setEditable (false, false, false);
    vcaMaxRtTimeLabel->setColour (TextEditor::textColourId, Colours::black);
    vcaMaxRtTimeLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (vcaMinRtTimeLabel = new Label ("time label",
                                                      TRANS("0ms")));
    vcaMinRtTimeLabel->setFont (Font (15.00f, Font::plain));
    vcaMinRtTimeLabel->setJustificationType (Justification::centredLeft);
    vcaMinRtTimeLabel->setEditable (false, false, false);
    vcaMinRtTimeLabel->setColour (TextEditor::textColourId, Colours::black);
    vcaMinRtTimeLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label10 = new Label ("new label",
                                            TRANS("Process TIme:")));
    label10->setFont (Font (15.00f, Font::plain));
    label10->setJustificationType (Justification::centredLeft);
    label10->setEditable (false, false, false);
    label10->setColour (TextEditor::textColourId, Colours::black);
    label10->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (vcaPrTimeDisplay = new Label ("time label",
                                                     TRANS("0ms")));
    vcaPrTimeDisplay->setFont (Font (15.00f, Font::plain));
    vcaPrTimeDisplay->setJustificationType (Justification::centredLeft);
    vcaPrTimeDisplay->setEditable (false, false, false);
    vcaPrTimeDisplay->setColour (TextEditor::textColourId, Colours::black);
    vcaPrTimeDisplay->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label11 = new Label ("new label",
                                            TRANS("Round Trip TIme:")));
    label11->setFont (Font (15.00f, Font::plain));
    label11->setJustificationType (Justification::centredLeft);
    label11->setEditable (false, false, false);
    label11->setColour (TextEditor::textColourId, Colours::black);
    label11->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (nullRtTimeDisplay = new Label ("time label",
                                                      TRANS("0ms")));
    nullRtTimeDisplay->setFont (Font (15.00f, Font::plain));
    nullRtTimeDisplay->setJustificationType (Justification::centredLeft);
    nullRtTimeDisplay->setEditable (false, false, false);
    nullRtTimeDisplay->setColour (TextEditor::textColourId, Colours::black);
    nullRtTimeDisplay->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label12 = new Label ("new label",
                                            TRANS("NULL Block:")));
    label12->setFont (Font (15.00f, Font::bold));
    label12->setJustificationType (Justification::centredLeft);
    label12->setEditable (false, false, false);
    label12->setColour (TextEditor::textColourId, Colours::black);
    label12->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (nullNetworkStatusComponent = new NetConnectivityIcon());
    addAndMakeVisible (label13 = new Label ("new label",
                                            TRANS("Max Trip TIme:")));
    label13->setFont (Font (15.00f, Font::plain));
    label13->setJustificationType (Justification::centredLeft);
    label13->setEditable (false, false, false);
    label13->setColour (TextEditor::textColourId, Colours::black);
    label13->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label14 = new Label ("new label",
                                            TRANS("Min Trip TIme:")));
    label14->setFont (Font (15.00f, Font::plain));
    label14->setJustificationType (Justification::centredLeft);
    label14->setEditable (false, false, false);
    label14->setColour (TextEditor::textColourId, Colours::black);
    label14->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (nullMaxRtTimeLabel = new Label ("time label",
                                                       TRANS("0ms")));
    nullMaxRtTimeLabel->setFont (Font (15.00f, Font::plain));
    nullMaxRtTimeLabel->setJustificationType (Justification::centredLeft);
    nullMaxRtTimeLabel->setEditable (false, false, false);
    nullMaxRtTimeLabel->setColour (TextEditor::textColourId, Colours::black);
    nullMaxRtTimeLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (nullMinRtTimeLabel = new Label ("time label",
                                                       TRANS("0ms")));
    nullMinRtTimeLabel->setFont (Font (15.00f, Font::plain));
    nullMinRtTimeLabel->setJustificationType (Justification::centredLeft);
    nullMinRtTimeLabel->setEditable (false, false, false);
    nullMinRtTimeLabel->setColour (TextEditor::textColourId, Colours::black);
    nullMinRtTimeLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label15 = new Label ("new label",
                                            TRANS("Process TIme:")));
    label15->setFont (Font (15.00f, Font::plain));
    label15->setJustificationType (Justification::centredLeft);
    label15->setEditable (false, false, false);
    label15->setColour (TextEditor::textColourId, Colours::black);
    label15->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (nullPrTimeDisplay = new Label ("time label",
                                                      TRANS("0ms")));
    nullPrTimeDisplay->setFont (Font (15.00f, Font::plain));
    nullPrTimeDisplay->setJustificationType (Justification::centredLeft);
    nullPrTimeDisplay->setEditable (false, false, false);
    nullPrTimeDisplay->setColour (TextEditor::textColourId, Colours::black);
    nullPrTimeDisplay->setColour (TextEditor::backgroundColourId, Colour (0x00000000));


    //[UserPreSize]

    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..

    //[/Constructor]
}

DiauproGUI::~DiauproGUI()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    label = nullptr;
    vcoRtTimeDisplay = nullptr;
    label2 = nullptr;
    vcoNetworkStatusComponent = nullptr;
    label3 = nullptr;
    label4 = nullptr;
    textButton = nullptr;
    vcoMaxRtTimeLabel = nullptr;
    vcoMinRtTimeLabel = nullptr;
    label5 = nullptr;
    vcoPrTimeDisplay = nullptr;
    label6 = nullptr;
    vcaRtTimeDisplay = nullptr;
    label7 = nullptr;
    vcaNetworkStatusComponent = nullptr;
    label8 = nullptr;
    label9 = nullptr;
    vcaMaxRtTimeLabel = nullptr;
    vcaMinRtTimeLabel = nullptr;
    label10 = nullptr;
    vcaPrTimeDisplay = nullptr;
    label11 = nullptr;
    nullRtTimeDisplay = nullptr;
    label12 = nullptr;
    nullNetworkStatusComponent = nullptr;
    label13 = nullptr;
    label14 = nullptr;
    nullMaxRtTimeLabel = nullptr;
    nullMinRtTimeLabel = nullptr;
    label15 = nullptr;
    nullPrTimeDisplay = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void DiauproGUI::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    if (vcoRtTime < 0) vcoRtTime = 0;
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    g.setColour (Colour (0xff213e3f));
    g.fillRect (20, 252, getWidth() - 45, 100);

    g.setColour (Colour (0xff213e3f));
    g.fillRect (20, 468, getWidth() - 45, 100);

    g.setColour (Colour (0xff213e3f));
    g.fillRect (20, 28, getWidth() - 45, 100);

    //[UserPaint] Add your own custom painting code here..
    //null
    if (nullNetStatus) {
        g.setColour (Colours::greenyellow);
    }else {
        g.setColour (Colours::orange);
    }

    int high;
    for (int i = 0; i < nullTimes.size(); i++) {
        high = int(100 * (nullTimes[i] / nullMaxRtTime ));
        g.fillRect(20 + i, 128 - high, 1, 1);
    }

    //vco

    if (vcoNetStatus) {
        g.setColour (Colours::greenyellow);
    }else {
        g.setColour (Colours::orange);
    }

    for (int i = 0; i < vcoTimes.size(); i++) {
        high = int(100 * (vcoTimes[i] / vcoMaxRtTime ));
        g.fillRect(20 + i, 352 - high, 1, 1);
    }

    //vca

    if (vcaNetStatus) {
        g.setColour (Colours::greenyellow);
    }else {
        g.setColour (Colours::orange);
    }

    g.setColour (Colours::orange);
    for (int i = 0; i < vcaTimes.size(); i++) {
        high = int(100 * (vcaTimes[i] / vcaMaxRtTime ));
        g.fillRect(20 + i, 568 - high, 1, 1);
    }
    //[/UserPaint]
}

void DiauproGUI::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    label->setBounds (16, 360, 120, 24);
    vcoRtTimeDisplay->setBounds (144, 360, 128, 24);
    label2->setBounds (16, 224, 72, 24);
    vcoNetworkStatusComponent->setBounds (getWidth() - 17 - 96, 232, 96, 16);
    label3->setBounds (16, 384, 120, 24);
    label4->setBounds (16, 408, 120, 24);
    textButton->setBounds (getWidth() - 13 - 150, getHeight() - 16 - 24, 150, 24);
    vcoMaxRtTimeLabel->setBounds (144, 384, 128, 24);
    vcoMinRtTimeLabel->setBounds (144, 408, 128, 24);
    label5->setBounds (288, 360, 120, 24);
    vcoPrTimeDisplay->setBounds (424, 360, 128, 24);
    label6->setBounds (16, 576, 120, 24);
    vcaRtTimeDisplay->setBounds (144, 576, 128, 24);
    label7->setBounds (16, 440, 72, 24);
    vcaNetworkStatusComponent->setBounds (getWidth() - 17 - 96, 448, 96, 16);
    label8->setBounds (16, 600, 120, 24);
    label9->setBounds (16, 624, 120, 24);
    vcaMaxRtTimeLabel->setBounds (144, 600, 128, 24);
    vcaMinRtTimeLabel->setBounds (144, 624, 128, 24);
    label10->setBounds (288, 576, 120, 24);
    vcaPrTimeDisplay->setBounds (424, 576, 128, 24);
    label11->setBounds (16, 136, 120, 24);
    nullRtTimeDisplay->setBounds (144, 136, 128, 24);
    label12->setBounds (16, 0, 72, 24);
    nullNetworkStatusComponent->setBounds (getWidth() - 17 - 96, 8, 96, 16);
    label13->setBounds (16, 160, 120, 24);
    label14->setBounds (16, 184, 120, 24);
    nullMaxRtTimeLabel->setBounds (144, 160, 128, 24);
    nullMinRtTimeLabel->setBounds (144, 184, 128, 24);
    label15->setBounds (288, 136, 120, 24);
    nullPrTimeDisplay->setBounds (424, 136, 128, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void DiauproGUI::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == textButton)
    {
        //[UserButtonCode_textButton] -- add your button handler code here..
        //[/UserButtonCode_textButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void DiauproGUI::setVcoTime(double pTime, double rtTime, double maxRtTime, double minRtTime )
{
    if (vcoTimes.size() > getWidth() - 45) vcoTimes.remove(0);
    const double filterAmount = 0.05;
    vcoMaxRtTime = maxRtTime;
    vcoMinRtTime = minRtTime;
    vcoRtTime += filterAmount * (rtTime - vcoRtTime);
    vcoPrTime += filterAmount * (pTime - vcoPrTime);

    vcoPrTimeDisplay->setText(String(vcoPrTime), juce::NotificationType::sendNotificationAsync);
    vcoMaxRtTimeLabel->setText(String(maxRtTime), juce::NotificationType::sendNotificationAsync);
    vcoMinRtTimeLabel->setText(String(minRtTime), juce::NotificationType::sendNotificationAsync);
    vcoRtTimeDisplay->setText(String(vcoRtTime), juce::NotificationType::sendNotificationAsync);


    if (rtTime > 0) vcoTimes.add(rtTime);

}

void DiauproGUI::setVcaTime(double pTime, double rtTime, double maxRtTime, double minRtTime )
{
    if (vcaTimes.size() > getWidth() - 45) vcaTimes.remove(0);
    const double filterAmount = 0.05;
    vcaMaxRtTime = maxRtTime;
    vcaMinRtTime = minRtTime;
    vcaRtTime += filterAmount * (rtTime - vcaRtTime);
    vcaPrTime += filterAmount * (pTime - vcaPrTime);
    
    vcaPrTimeDisplay->setText(String(vcaPrTime), juce::NotificationType::sendNotificationAsync);
    vcaMaxRtTimeLabel->setText(String(maxRtTime), juce::NotificationType::sendNotificationAsync);
    vcaMinRtTimeLabel->setText(String(minRtTime), juce::NotificationType::sendNotificationAsync);
    vcaRtTimeDisplay->setText(String(vcaRtTime), juce::NotificationType::sendNotificationAsync);
    
    
    if (rtTime > 0) vcaTimes.add(rtTime);
    
}

void DiauproGUI::setNullTime(double pTime, double rtTime, double maxRtTime, double minRtTime )
{
    if (nullTimes.size() > getWidth() - 45) nullTimes.remove(0);
    const double filterAmount = 0.05;
    nullMaxRtTime = maxRtTime;
    nullMinRtTime = minRtTime;
    nullRtTime += filterAmount * (rtTime - nullRtTime);
    nullPrTime += filterAmount * (pTime - nullPrTime);
    
    nullPrTimeDisplay->setText(String(nullPrTime), juce::NotificationType::sendNotificationAsync);
    nullMaxRtTimeLabel->setText(String(maxRtTime), juce::NotificationType::sendNotificationAsync);
    nullMinRtTimeLabel->setText(String(minRtTime), juce::NotificationType::sendNotificationAsync);
    nullRtTimeDisplay->setText(String(nullRtTime), juce::NotificationType::sendNotificationAsync);
    
    
    if (rtTime > 0) nullTimes.add(rtTime);
    
}

void DiauproGUI::setVcoNetStatus(bool status)
{
    vcoNetworkStatusComponent->setActive(status);
    vcoNetStatus = status;
}
void DiauproGUI::setVcaNetStatus(bool status)
{
    vcaNetworkStatusComponent->setActive(status);
    vcaNetStatus = status;
}
void DiauproGUI::setNullNetStatus(bool status)
{
    nullNetworkStatusComponent->setActive(status);
    nullNetStatus = status;
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="DiauproGUI" componentName=""
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="600" initialHeight="400">
  <BACKGROUND backgroundColour="ffffffff">
    <RECT pos="20 252 45M 100" fill="solid: ff213e3f" hasStroke="0"/>
    <RECT pos="20 468 45M 100" fill="solid: ff213e3f" hasStroke="0"/>
    <RECT pos="20 28 45M 100" fill="solid: ff213e3f" hasStroke="0"/>
  </BACKGROUND>
  <LABEL name="new label" id="b4a91c86af708001" memberName="label" virtualName=""
         explicitFocusOrder="0" pos="16 360 120 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Round Trip TIme:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="time label" id="b89139bf98292531" memberName="vcoRtTimeDisplay"
         virtualName="" explicitFocusOrder="0" pos="144 360 128 24" edTextCol="ff000000"
         edBkgCol="0" labelText="0ms" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="13a5a421710ffa62" memberName="label2" virtualName=""
         explicitFocusOrder="0" pos="16 224 72 24" edTextCol="ff000000"
         edBkgCol="0" labelText="VCO Block:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="1" italic="0" justification="33"/>
  <JUCERCOMP name="" id="90891f4191902732" memberName="vcoNetworkStatusComponent"
             virtualName="" explicitFocusOrder="0" pos="17Rr 232 96 16" sourceFile="NetConnectivityIcon.cpp"
             constructorParams=""/>
  <LABEL name="new label" id="7fb9c58642bcf941" memberName="label3" virtualName=""
         explicitFocusOrder="0" pos="16 384 120 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Max Trip TIme:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="5419d3eca266cd46" memberName="label4" virtualName=""
         explicitFocusOrder="0" pos="16 408 120 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Min Trip TIme:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <TEXTBUTTON name="new button" id="48159015733809ea" memberName="textButton"
              virtualName="" explicitFocusOrder="0" pos="13Rr 16Rr 150 24"
              buttonText="reset" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <LABEL name="time label" id="fce1be55b4011af2" memberName="vcoMaxRtTimeLabel"
         virtualName="" explicitFocusOrder="0" pos="144 384 128 24" edTextCol="ff000000"
         edBkgCol="0" labelText="0ms" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="time label" id="43a24ef8f65340b9" memberName="vcoMinRtTimeLabel"
         virtualName="" explicitFocusOrder="0" pos="144 408 128 24" edTextCol="ff000000"
         edBkgCol="0" labelText="0ms" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="e188f104f73153ba" memberName="label5" virtualName=""
         explicitFocusOrder="0" pos="288 360 120 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Process TIme:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="time label" id="cc5ad605cc6d535f" memberName="vcoPrTimeDisplay"
         virtualName="" explicitFocusOrder="0" pos="424 360 128 24" edTextCol="ff000000"
         edBkgCol="0" labelText="0ms" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="536fe4ed555edbf2" memberName="label6" virtualName=""
         explicitFocusOrder="0" pos="16 576 120 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Round Trip TIme:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="time label" id="50fffa06e01b67be" memberName="vcaRtTimeDisplay"
         virtualName="" explicitFocusOrder="0" pos="144 576 128 24" edTextCol="ff000000"
         edBkgCol="0" labelText="0ms" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="3dc39d5afdf1d1d1" memberName="label7" virtualName=""
         explicitFocusOrder="0" pos="16 440 72 24" edTextCol="ff000000"
         edBkgCol="0" labelText="VCA Block:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="1" italic="0" justification="33"/>
  <JUCERCOMP name="" id="4eb60b0a023245a" memberName="vcaNetworkStatusComponent"
             virtualName="" explicitFocusOrder="0" pos="17Rr 448 96 16" sourceFile="NetConnectivityIcon.cpp"
             constructorParams=""/>
  <LABEL name="new label" id="d19c7891649207bc" memberName="label8" virtualName=""
         explicitFocusOrder="0" pos="16 600 120 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Max Trip TIme:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="2d846e97fa3c48e0" memberName="label9" virtualName=""
         explicitFocusOrder="0" pos="16 624 120 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Min Trip TIme:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="time label" id="563b44c955a58ba7" memberName="vcaMaxRtTimeLabel"
         virtualName="" explicitFocusOrder="0" pos="144 600 128 24" edTextCol="ff000000"
         edBkgCol="0" labelText="0ms" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="time label" id="54005d7999d15b00" memberName="vcaMinRtTimeLabel"
         virtualName="" explicitFocusOrder="0" pos="144 624 128 24" edTextCol="ff000000"
         edBkgCol="0" labelText="0ms" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="82bfe0338bfcdffd" memberName="label10" virtualName=""
         explicitFocusOrder="0" pos="288 576 120 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Process TIme:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="time label" id="31a6b58a7fee2fac" memberName="vcaPrTimeDisplay"
         virtualName="" explicitFocusOrder="0" pos="424 576 128 24" edTextCol="ff000000"
         edBkgCol="0" labelText="0ms" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="7014d9d90067a037" memberName="label11" virtualName=""
         explicitFocusOrder="0" pos="16 136 120 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Round Trip TIme:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="time label" id="fb18e1c383a65669" memberName="nullRtTimeDisplay"
         virtualName="" explicitFocusOrder="0" pos="144 136 128 24" edTextCol="ff000000"
         edBkgCol="0" labelText="0ms" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="7ee7d4586ef243bf" memberName="label12" virtualName=""
         explicitFocusOrder="0" pos="16 0 72 24" edTextCol="ff000000"
         edBkgCol="0" labelText="NULL Block:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="1" italic="0" justification="33"/>
  <JUCERCOMP name="" id="920db8fc93e9b046" memberName="nullNetworkStatusComponent"
             virtualName="" explicitFocusOrder="0" pos="17Rr 8 96 16" sourceFile="NetConnectivityIcon.cpp"
             constructorParams=""/>
  <LABEL name="new label" id="48934800cf6c18eb" memberName="label13" virtualName=""
         explicitFocusOrder="0" pos="16 160 120 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Max Trip TIme:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="a5f3d78b5cbe5a36" memberName="label14" virtualName=""
         explicitFocusOrder="0" pos="16 184 120 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Min Trip TIme:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="time label" id="8da90b4a60fa7db2" memberName="nullMaxRtTimeLabel"
         virtualName="" explicitFocusOrder="0" pos="144 160 128 24" edTextCol="ff000000"
         edBkgCol="0" labelText="0ms" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="time label" id="393a875380fede5b" memberName="nullMinRtTimeLabel"
         virtualName="" explicitFocusOrder="0" pos="144 184 128 24" edTextCol="ff000000"
         edBkgCol="0" labelText="0ms" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="26499660329f0ea9" memberName="label15" virtualName=""
         explicitFocusOrder="0" pos="288 136 120 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Process TIme:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="time label" id="9c62db60cc4abc65" memberName="nullPrTimeDisplay"
         virtualName="" explicitFocusOrder="0" pos="424 136 128 24" edTextCol="ff000000"
         edBkgCol="0" labelText="0ms" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
