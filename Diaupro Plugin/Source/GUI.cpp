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
#include "PluginEditor.h"
//[/MiscUserDefs]

//==============================================================================
DiauproGUI::DiauproGUI ()
{
    //[Constructor_pre] You can add your own custom stuff here..

    //[/Constructor_pre]

    addAndMakeVisible (label = new Label ("new label",
                                          TRANS("Round Trip Time:")));
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
                                           TRANS("Max Trip Time:")));
    label3->setFont (Font (15.00f, Font::plain));
    label3->setJustificationType (Justification::centredLeft);
    label3->setEditable (false, false, false);
    label3->setColour (TextEditor::textColourId, Colours::black);
    label3->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label4 = new Label ("new label",
                                           TRANS("Min Trip Time:")));
    label4->setFont (Font (15.00f, Font::plain));
    label4->setJustificationType (Justification::centredLeft);
    label4->setEditable (false, false, false);
    label4->setColour (TextEditor::textColourId, Colours::black);
    label4->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

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
                                           TRANS("Process Time:")));
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
                                           TRANS("Round Trip Time:")));
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
                                           TRANS("Max Trip Time:")));
    label8->setFont (Font (15.00f, Font::plain));
    label8->setJustificationType (Justification::centredLeft);
    label8->setEditable (false, false, false);
    label8->setColour (TextEditor::textColourId, Colours::black);
    label8->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label9 = new Label ("new label",
                                           TRANS("Min Trip Time:")));
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
                                            TRANS("Process Time:")));
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
                                            TRANS("Round Trip Time:")));
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
                                            TRANS("Max Trip Time:")));
    label13->setFont (Font (15.00f, Font::plain));
    label13->setJustificationType (Justification::centredLeft);
    label13->setEditable (false, false, false);
    label13->setColour (TextEditor::textColourId, Colours::black);
    label13->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label14 = new Label ("new label",
                                            TRANS("Min Trip Time:")));
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
                                            TRANS("Process Time:")));
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

    addAndMakeVisible (label16 = new Label ("new label",
                                            TRANS("Round Trip Time:")));
    label16->setFont (Font (15.00f, Font::plain));
    label16->setJustificationType (Justification::centredLeft);
    label16->setEditable (false, false, false);
    label16->setColour (TextEditor::textColourId, Colours::black);
    label16->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (asyncRtTimeDisplay = new Label ("time label",
                                                       TRANS("0ms")));
    asyncRtTimeDisplay->setFont (Font (15.00f, Font::plain));
    asyncRtTimeDisplay->setJustificationType (Justification::centredLeft);
    asyncRtTimeDisplay->setEditable (false, false, false);
    asyncRtTimeDisplay->setColour (TextEditor::textColourId, Colours::black);
    asyncRtTimeDisplay->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label17 = new Label ("new label",
                                            TRANS("AsyncBlock:")));
    label17->setFont (Font (15.00f, Font::bold));
    label17->setJustificationType (Justification::centredLeft);
    label17->setEditable (false, false, false);
    label17->setColour (TextEditor::textColourId, Colours::black);
    label17->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (asyncNetworkStatusComponent = new NetConnectivityIcon());
    addAndMakeVisible (label18 = new Label ("new label",
                                            TRANS("Max Trip Time:")));
    label18->setFont (Font (15.00f, Font::plain));
    label18->setJustificationType (Justification::centredLeft);
    label18->setEditable (false, false, false);
    label18->setColour (TextEditor::textColourId, Colours::black);
    label18->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label19 = new Label ("new label",
                                            TRANS("Min Trip Time:")));
    label19->setFont (Font (15.00f, Font::plain));
    label19->setJustificationType (Justification::centredLeft);
    label19->setEditable (false, false, false);
    label19->setColour (TextEditor::textColourId, Colours::black);
    label19->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (asyncMaxRtTimeLabel = new Label ("time label",
                                                        TRANS("0ms")));
    asyncMaxRtTimeLabel->setFont (Font (15.00f, Font::plain));
    asyncMaxRtTimeLabel->setJustificationType (Justification::centredLeft);
    asyncMaxRtTimeLabel->setEditable (false, false, false);
    asyncMaxRtTimeLabel->setColour (TextEditor::textColourId, Colours::black);
    asyncMaxRtTimeLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (asyncMinRtTimeLabel = new Label ("time label",
                                                        TRANS("0ms")));
    asyncMinRtTimeLabel->setFont (Font (15.00f, Font::plain));
    asyncMinRtTimeLabel->setJustificationType (Justification::centredLeft);
    asyncMinRtTimeLabel->setEditable (false, false, false);
    asyncMinRtTimeLabel->setColour (TextEditor::textColourId, Colours::black);
    asyncMinRtTimeLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label20 = new Label ("new label",
                                            TRANS("Process Time:")));
    label20->setFont (Font (15.00f, Font::plain));
    label20->setJustificationType (Justification::centredLeft);
    label20->setEditable (false, false, false);
    label20->setColour (TextEditor::textColourId, Colours::black);
    label20->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (asyncPrTimeDisplay = new Label ("time label",
                                                       TRANS("0ms")));
    asyncPrTimeDisplay->setFont (Font (15.00f, Font::plain));
    asyncPrTimeDisplay->setJustificationType (Justification::centredLeft);
    asyncPrTimeDisplay->setEditable (false, false, false);
    asyncPrTimeDisplay->setColour (TextEditor::textColourId, Colours::black);
    asyncPrTimeDisplay->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (nullAsyncButton = new TextButton ("nullAsyncButton"));
    nullAsyncButton->setButtonText (TRANS("async"));
    nullAsyncButton->addListener (this);
    nullAsyncButton->setColour (TextButton::buttonColourId, Colour (0xffeaeaff));
    nullAsyncButton->setColour (TextButton::buttonOnColourId, Colour (0xff31ff65));

    addAndMakeVisible (vcoAsyncButton = new TextButton ("vcoAsyncButton"));
    vcoAsyncButton->setButtonText (TRANS("async"));
    vcoAsyncButton->addListener (this);
    vcoAsyncButton->setColour (TextButton::buttonColourId, Colour (0xffeaeaff));
    vcoAsyncButton->setColour (TextButton::buttonOnColourId, Colour (0xff31ff65));

    addAndMakeVisible (vcaAsyncButton = new TextButton ("vcaAsyncButton"));
    vcaAsyncButton->setButtonText (TRANS("async"));
    vcaAsyncButton->addListener (this);
    vcaAsyncButton->setColour (TextButton::buttonColourId, Colour (0xffeaeaff));
    vcaAsyncButton->setColour (TextButton::buttonOnColourId, Colour (0xff31ff65));

    addAndMakeVisible (label21 = new Label ("new label",
                                            TRANS("Total Latency:")));
    label21->setFont (Font (15.00f, Font::plain));
    label21->setJustificationType (Justification::centredLeft);
    label21->setEditable (false, false, false);
    label21->setColour (TextEditor::textColourId, Colours::black);
    label21->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (latencyLabel = new Label ("new label",
                                                 TRANS("0ms")));
    latencyLabel->setFont (Font (15.00f, Font::plain));
    latencyLabel->setJustificationType (Justification::centredLeft);
    latencyLabel->setEditable (false, false, false);
    latencyLabel->setColour (TextEditor::textColourId, Colours::black);
    latencyLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));


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
    label16 = nullptr;
    asyncRtTimeDisplay = nullptr;
    label17 = nullptr;
    asyncNetworkStatusComponent = nullptr;
    label18 = nullptr;
    label19 = nullptr;
    asyncMaxRtTimeLabel = nullptr;
    asyncMinRtTimeLabel = nullptr;
    label20 = nullptr;
    asyncPrTimeDisplay = nullptr;
    nullAsyncButton = nullptr;
    vcoAsyncButton = nullptr;
    vcaAsyncButton = nullptr;
    label21 = nullptr;
    latencyLabel = nullptr;


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
    g.fillRect (20, 220, getWidth() - 45, 100);

    g.setColour (Colour (0xff213e3f));
    g.fillRect (20, 412, getWidth() - 45, 100);

    g.setColour (Colour (0xff213e3f));
    g.fillRect (20, 28, getWidth() - 45, 100);

    g.setColour (Colour (0xff213e3f));
    g.fillRect (20, 604, getWidth() - 45, 100);

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
        g.fillRect(20 + i, 320 - high, 1, 1);
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
        g.fillRect(20 + i, 512 - high, 1, 1);
    }

    // async

    if (asyncNetStatus) {
        g.setColour (Colours::greenyellow);
    }else {
        g.setColour (Colours::orange);
    }

    g.setColour (Colours::orange);
    for (int i = 0; i < asyncTimes.size(); i++) {
        high = int(100 * (asyncTimes[i] / asyncMaxRtTime ));
        g.fillRect(20 + i, 704 - high, 1, 1);
    }
    //[/UserPaint]
}

void DiauproGUI::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    label->setBounds (16, 320, 120, 24);
    vcoRtTimeDisplay->setBounds (144, 320, 128, 24);
    label2->setBounds (16, 196, 72, 24);
    vcoNetworkStatusComponent->setBounds (getWidth() - 21 - 96, 200, 96, 16);
    label3->setBounds (16, 336, 120, 24);
    label4->setBounds (16, 352, 120, 24);
    vcoMaxRtTimeLabel->setBounds (144, 336, 128, 24);
    vcoMinRtTimeLabel->setBounds (144, 352, 128, 24);
    label5->setBounds (288, 320, 120, 24);
    vcoPrTimeDisplay->setBounds (400, 320, 128, 24);
    label6->setBounds (16, 512, 120, 24);
    vcaRtTimeDisplay->setBounds (144, 512, 128, 24);
    label7->setBounds (16, 388, 72, 24);
    vcaNetworkStatusComponent->setBounds (getWidth() - 21 - 96, 392, 96, 16);
    label8->setBounds (16, 528, 120, 24);
    label9->setBounds (16, 544, 120, 24);
    vcaMaxRtTimeLabel->setBounds (144, 528, 128, 24);
    vcaMinRtTimeLabel->setBounds (144, 544, 128, 24);
    label10->setBounds (288, 512, 120, 24);
    vcaPrTimeDisplay->setBounds (400, 512, 128, 24);
    label11->setBounds (16, 128, 120, 24);
    nullRtTimeDisplay->setBounds (144, 128, 128, 24);
    label12->setBounds (16, 4, 72, 24);
    nullNetworkStatusComponent->setBounds (getWidth() - 17 - 96, 8, 96, 16);
    label13->setBounds (16, 144, 120, 24);
    label14->setBounds (16, 160, 120, 24);
    nullMaxRtTimeLabel->setBounds (144, 144, 128, 24);
    nullMinRtTimeLabel->setBounds (144, 160, 128, 24);
    label15->setBounds (288, 128, 120, 24);
    nullPrTimeDisplay->setBounds (400, 128, 128, 24);
    label16->setBounds (16, 704, 120, 24);
    asyncRtTimeDisplay->setBounds (152, 704, 128, 24);
    label17->setBounds (16, 580, 104, 24);
    asyncNetworkStatusComponent->setBounds (getWidth() - 21 - 96, 584, 96, 16);
    label18->setBounds (16, 720, 120, 24);
    label19->setBounds (16, 736, 120, 24);
    asyncMaxRtTimeLabel->setBounds (152, 720, 128, 24);
    asyncMinRtTimeLabel->setBounds (152, 736, 128, 24);
    label20->setBounds (296, 704, 120, 24);
    asyncPrTimeDisplay->setBounds (400, 704, 128, 24);
    nullAsyncButton->setBounds (getWidth() - 157, 8, 32, 16);
    vcoAsyncButton->setBounds (getWidth() - 157, 200, 32, 16);
    vcaAsyncButton->setBounds (getWidth() - 157, 392, 32, 16);
    label21->setBounds (16, 768, 96, 24);
    latencyLabel->setBounds (112, 768, 96, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void DiauproGUI::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == nullAsyncButton)
    {
        //[UserButtonCode_nullAsyncButton] -- add your button handler code here..
        nullAsync = !nullAsync;
        nullAsyncButton->setToggleState(nullAsync, juce::NotificationType::dontSendNotification);
        (findParentComponentOfClass<DiauproPluginAudioProcessorEditor>())->setNullAsync(nullAsync);

        //[/UserButtonCode_nullAsyncButton]
    }
    else if (buttonThatWasClicked == vcoAsyncButton)
    {
        //[UserButtonCode_vcoAsyncButton] -- add your button handler code here..
        vcoAsync = !vcoAsync;
        vcoAsyncButton->setToggleState(vcoAsync, juce::NotificationType::dontSendNotification);
        (findParentComponentOfClass<DiauproPluginAudioProcessorEditor>())->setVcoAsync(vcoAsync);
        //[/UserButtonCode_vcoAsyncButton]
    }
    else if (buttonThatWasClicked == vcaAsyncButton)
    {
        //[UserButtonCode_vcaAsyncButton] -- add your button handler code here..
        vcaAsync = !vcaAsync;
        vcaAsyncButton->setToggleState(vcaAsync, juce::NotificationType::dontSendNotification);
        (findParentComponentOfClass<DiauproPluginAudioProcessorEditor>())->setVcaAsync(vcaAsync);

        //[/UserButtonCode_vcaAsyncButton]
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

void DiauproGUI::setAsyncTime(double pTime, double rtTime, double maxRtTime, double minRtTime )
{
    if (asyncTimes.size() > getWidth() - 45) asyncTimes.remove(0);
    const double filterAmount = 0.05;
    asyncMaxRtTime = maxRtTime;
    asyncMinRtTime = minRtTime;
    asyncRtTime += filterAmount * (rtTime - asyncRtTime);
    asyncPrTime += filterAmount * (pTime - asyncPrTime);

    asyncPrTimeDisplay->setText(String(asyncPrTime), juce::NotificationType::sendNotificationAsync);
    asyncMaxRtTimeLabel->setText(String(maxRtTime), juce::NotificationType::sendNotificationAsync);
    asyncMinRtTimeLabel->setText(String(minRtTime), juce::NotificationType::sendNotificationAsync);
    asyncRtTimeDisplay->setText(String(asyncRtTime), juce::NotificationType::sendNotificationAsync);
    
    latencyLabel->setText(String((findParentComponentOfClass<DiauproPluginAudioProcessorEditor>())->getLatency()), juce::NotificationType::sendNotificationAsync);

    if (rtTime > 0) asyncTimes.add(rtTime);

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
void DiauproGUI::setAsyncNetStatus(bool status)
{
    asyncNetworkStatusComponent->setActive(status);
    asyncNetStatus = status;
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
    <RECT pos="20 220 45M 100" fill="solid: ff213e3f" hasStroke="0"/>
    <RECT pos="20 412 45M 100" fill="solid: ff213e3f" hasStroke="0"/>
    <RECT pos="20 28 45M 100" fill="solid: ff213e3f" hasStroke="0"/>
    <RECT pos="20 604 45M 100" fill="solid: ff213e3f" hasStroke="0"/>
  </BACKGROUND>
  <LABEL name="new label" id="b4a91c86af708001" memberName="label" virtualName=""
         explicitFocusOrder="0" pos="16 320 120 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Round Trip Time:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="time label" id="b89139bf98292531" memberName="vcoRtTimeDisplay"
         virtualName="" explicitFocusOrder="0" pos="144 320 128 24" edTextCol="ff000000"
         edBkgCol="0" labelText="0ms" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="13a5a421710ffa62" memberName="label2" virtualName=""
         explicitFocusOrder="0" pos="16 196 72 24" edTextCol="ff000000"
         edBkgCol="0" labelText="VCO Block:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="1" italic="0" justification="33"/>
  <JUCERCOMP name="" id="90891f4191902732" memberName="vcoNetworkStatusComponent"
             virtualName="" explicitFocusOrder="0" pos="21Rr 200 96 16" sourceFile="NetConnectivityIcon.cpp"
             constructorParams=""/>
  <LABEL name="new label" id="7fb9c58642bcf941" memberName="label3" virtualName=""
         explicitFocusOrder="0" pos="16 336 120 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Max Trip Time:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="5419d3eca266cd46" memberName="label4" virtualName=""
         explicitFocusOrder="0" pos="16 352 120 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Min Trip Time:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="time label" id="fce1be55b4011af2" memberName="vcoMaxRtTimeLabel"
         virtualName="" explicitFocusOrder="0" pos="144 336 128 24" edTextCol="ff000000"
         edBkgCol="0" labelText="0ms" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="time label" id="43a24ef8f65340b9" memberName="vcoMinRtTimeLabel"
         virtualName="" explicitFocusOrder="0" pos="144 352 128 24" edTextCol="ff000000"
         edBkgCol="0" labelText="0ms" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="e188f104f73153ba" memberName="label5" virtualName=""
         explicitFocusOrder="0" pos="288 320 120 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Process Time:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="time label" id="cc5ad605cc6d535f" memberName="vcoPrTimeDisplay"
         virtualName="" explicitFocusOrder="0" pos="400 320 128 24" edTextCol="ff000000"
         edBkgCol="0" labelText="0ms" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="536fe4ed555edbf2" memberName="label6" virtualName=""
         explicitFocusOrder="0" pos="16 512 120 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Round Trip Time:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="time label" id="50fffa06e01b67be" memberName="vcaRtTimeDisplay"
         virtualName="" explicitFocusOrder="0" pos="144 512 128 24" edTextCol="ff000000"
         edBkgCol="0" labelText="0ms" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="3dc39d5afdf1d1d1" memberName="label7" virtualName=""
         explicitFocusOrder="0" pos="16 388 72 24" edTextCol="ff000000"
         edBkgCol="0" labelText="VCA Block:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="1" italic="0" justification="33"/>
  <JUCERCOMP name="" id="4eb60b0a023245a" memberName="vcaNetworkStatusComponent"
             virtualName="" explicitFocusOrder="0" pos="21Rr 392 96 16" sourceFile="NetConnectivityIcon.cpp"
             constructorParams=""/>
  <LABEL name="new label" id="d19c7891649207bc" memberName="label8" virtualName=""
         explicitFocusOrder="0" pos="16 528 120 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Max Trip Time:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="2d846e97fa3c48e0" memberName="label9" virtualName=""
         explicitFocusOrder="0" pos="16 544 120 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Min Trip Time:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="time label" id="563b44c955a58ba7" memberName="vcaMaxRtTimeLabel"
         virtualName="" explicitFocusOrder="0" pos="144 528 128 24" edTextCol="ff000000"
         edBkgCol="0" labelText="0ms" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="time label" id="54005d7999d15b00" memberName="vcaMinRtTimeLabel"
         virtualName="" explicitFocusOrder="0" pos="144 544 128 24" edTextCol="ff000000"
         edBkgCol="0" labelText="0ms" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="82bfe0338bfcdffd" memberName="label10" virtualName=""
         explicitFocusOrder="0" pos="288 512 120 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Process Time:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="time label" id="31a6b58a7fee2fac" memberName="vcaPrTimeDisplay"
         virtualName="" explicitFocusOrder="0" pos="400 512 128 24" edTextCol="ff000000"
         edBkgCol="0" labelText="0ms" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="7014d9d90067a037" memberName="label11" virtualName=""
         explicitFocusOrder="0" pos="16 128 120 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Round Trip Time:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="time label" id="fb18e1c383a65669" memberName="nullRtTimeDisplay"
         virtualName="" explicitFocusOrder="0" pos="144 128 128 24" edTextCol="ff000000"
         edBkgCol="0" labelText="0ms" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="7ee7d4586ef243bf" memberName="label12" virtualName=""
         explicitFocusOrder="0" pos="16 4 72 24" edTextCol="ff000000"
         edBkgCol="0" labelText="NULL Block:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="1" italic="0" justification="33"/>
  <JUCERCOMP name="" id="920db8fc93e9b046" memberName="nullNetworkStatusComponent"
             virtualName="" explicitFocusOrder="0" pos="17Rr 8 96 16" sourceFile="NetConnectivityIcon.cpp"
             constructorParams=""/>
  <LABEL name="new label" id="48934800cf6c18eb" memberName="label13" virtualName=""
         explicitFocusOrder="0" pos="16 144 120 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Max Trip Time:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="a5f3d78b5cbe5a36" memberName="label14" virtualName=""
         explicitFocusOrder="0" pos="16 160 120 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Min Trip Time:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="time label" id="8da90b4a60fa7db2" memberName="nullMaxRtTimeLabel"
         virtualName="" explicitFocusOrder="0" pos="144 144 128 24" edTextCol="ff000000"
         edBkgCol="0" labelText="0ms" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="time label" id="393a875380fede5b" memberName="nullMinRtTimeLabel"
         virtualName="" explicitFocusOrder="0" pos="144 160 128 24" edTextCol="ff000000"
         edBkgCol="0" labelText="0ms" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="26499660329f0ea9" memberName="label15" virtualName=""
         explicitFocusOrder="0" pos="288 128 120 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Process Time:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="time label" id="9c62db60cc4abc65" memberName="nullPrTimeDisplay"
         virtualName="" explicitFocusOrder="0" pos="400 128 128 24" edTextCol="ff000000"
         edBkgCol="0" labelText="0ms" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="2033bda17732b96" memberName="label16" virtualName=""
         explicitFocusOrder="0" pos="16 704 120 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Round Trip Time:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="time label" id="f5713b4601a11e61" memberName="asyncRtTimeDisplay"
         virtualName="" explicitFocusOrder="0" pos="152 704 128 24" edTextCol="ff000000"
         edBkgCol="0" labelText="0ms" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="226c45042216d90e" memberName="label17" virtualName=""
         explicitFocusOrder="0" pos="16 580 104 24" edTextCol="ff000000"
         edBkgCol="0" labelText="AsyncBlock:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="1" italic="0" justification="33"/>
  <JUCERCOMP name="" id="56acad658803f4c2" memberName="asyncNetworkStatusComponent"
             virtualName="" explicitFocusOrder="0" pos="21Rr 584 96 16" sourceFile="NetConnectivityIcon.cpp"
             constructorParams=""/>
  <LABEL name="new label" id="cc7b7713544026a9" memberName="label18" virtualName=""
         explicitFocusOrder="0" pos="16 720 120 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Max Trip Time:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="b6d380426a0ea244" memberName="label19" virtualName=""
         explicitFocusOrder="0" pos="16 736 120 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Min Trip Time:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="time label" id="f6c70d43a3724086" memberName="asyncMaxRtTimeLabel"
         virtualName="" explicitFocusOrder="0" pos="152 720 128 24" edTextCol="ff000000"
         edBkgCol="0" labelText="0ms" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="time label" id="607fffc5af7a5e30" memberName="asyncMinRtTimeLabel"
         virtualName="" explicitFocusOrder="0" pos="152 736 128 24" edTextCol="ff000000"
         edBkgCol="0" labelText="0ms" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="b824eca14d50087e" memberName="label20" virtualName=""
         explicitFocusOrder="0" pos="296 704 120 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Process Time:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="time label" id="11b505d20c77eef8" memberName="asyncPrTimeDisplay"
         virtualName="" explicitFocusOrder="0" pos="400 704 128 24" edTextCol="ff000000"
         edBkgCol="0" labelText="0ms" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <TEXTBUTTON name="nullAsyncButton" id="8627ddc967c2a73a" memberName="nullAsyncButton"
              virtualName="" explicitFocusOrder="0" pos="157R 8 32 16" bgColOff="ffeaeaff"
              bgColOn="ff31ff65" buttonText="async" connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
  <TEXTBUTTON name="vcoAsyncButton" id="c1a5c5fe06737900" memberName="vcoAsyncButton"
              virtualName="" explicitFocusOrder="0" pos="157R 200 32 16" bgColOff="ffeaeaff"
              bgColOn="ff31ff65" buttonText="async" connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
  <TEXTBUTTON name="vcaAsyncButton" id="111d9318d310c969" memberName="vcaAsyncButton"
              virtualName="" explicitFocusOrder="0" pos="157R 392 32 16" bgColOff="ffeaeaff"
              bgColOn="ff31ff65" buttonText="async" connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
  <LABEL name="new label" id="a21f824e5df8e0e5" memberName="label21" virtualName=""
         explicitFocusOrder="0" pos="16 768 96 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Total Latency:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="c565df5b52f472a8" memberName="latencyLabel"
         virtualName="" explicitFocusOrder="0" pos="112 768 96 24" edTextCol="ff000000"
         edBkgCol="0" labelText="0ms" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
