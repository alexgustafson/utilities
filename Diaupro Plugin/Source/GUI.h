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

#ifndef __JUCE_HEADER_5290F0CE3B9D4392__
#define __JUCE_HEADER_5290F0CE3B9D4392__

//[Headers]     -- You can add your own extra header files here --
#include "JuceHeader.h"
//[/Headers]

#include "NetConnectivityIcon.h"


//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class DiauproGUI  : public Component,
                    public ButtonListener
{
public:
    //==============================================================================
    DiauproGUI ();
    ~DiauproGUI();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void setVcoTime(double pTime, double rtTime, double maxRtTime, double minRtTime );
    void setVcoNetStatus(bool status);
    void setVcaTime(double pTime, double rtTime, double maxRtTime, double minRtTime );
    void setVcaNetStatus(bool status);
    void setNullTime(double pTime, double rtTime, double maxRtTime, double minRtTime );
    void setNullNetStatus(bool status);
    void setAsyncTime(double pTime, double rtTime, double maxRtTime, double minRtTime );
    void setAsyncNetStatus(bool status);
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void buttonClicked (Button* buttonThatWasClicked);



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    double vcoRtTime = 0;
    double vcoPrTime = 0;
    double vcoMaxRtTime = 0;
    double vcoMinRtTime = 0;
    Array<double> vcoTimes;
    bool vcoNetStatus = false;

    double vcaRtTime = 0;
    double vcaPrTime = 0;
    double vcaMaxRtTime = 0;
    double vcaMinRtTime = 0;
    Array<double> vcaTimes;
    bool vcaNetStatus = false;

    double nullRtTime = 0;
    double nullPrTime = 0;
    double nullMaxRtTime = 0;
    double nullMinRtTime = 0;
    Array<double> nullTimes;
    bool nullNetStatus = false;

    double asyncRtTime = 0;
    double asyncPrTime = 0;
    double asyncMaxRtTime = 0;
    double asyncMinRtTime = 0;
    Array<double> asyncTimes;
    bool asyncNetStatus = false;

    bool nullAsync = false;
    bool vcoAsync = false;
    bool vcaAsync = false;
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<Label> label;
    ScopedPointer<Label> vcoRtTimeDisplay;
    ScopedPointer<Label> label2;
    ScopedPointer<NetConnectivityIcon> vcoNetworkStatusComponent;
    ScopedPointer<Label> label3;
    ScopedPointer<Label> label4;
    ScopedPointer<Label> vcoMaxRtTimeLabel;
    ScopedPointer<Label> vcoMinRtTimeLabel;
    ScopedPointer<Label> label5;
    ScopedPointer<Label> vcoPrTimeDisplay;
    ScopedPointer<Label> label6;
    ScopedPointer<Label> vcaRtTimeDisplay;
    ScopedPointer<Label> label7;
    ScopedPointer<NetConnectivityIcon> vcaNetworkStatusComponent;
    ScopedPointer<Label> label8;
    ScopedPointer<Label> label9;
    ScopedPointer<Label> vcaMaxRtTimeLabel;
    ScopedPointer<Label> vcaMinRtTimeLabel;
    ScopedPointer<Label> label10;
    ScopedPointer<Label> vcaPrTimeDisplay;
    ScopedPointer<Label> label11;
    ScopedPointer<Label> nullRtTimeDisplay;
    ScopedPointer<Label> label12;
    ScopedPointer<NetConnectivityIcon> nullNetworkStatusComponent;
    ScopedPointer<Label> label13;
    ScopedPointer<Label> label14;
    ScopedPointer<Label> nullMaxRtTimeLabel;
    ScopedPointer<Label> nullMinRtTimeLabel;
    ScopedPointer<Label> label15;
    ScopedPointer<Label> nullPrTimeDisplay;
    ScopedPointer<Label> label16;
    ScopedPointer<Label> asyncRtTimeDisplay;
    ScopedPointer<Label> label17;
    ScopedPointer<NetConnectivityIcon> asyncNetworkStatusComponent;
    ScopedPointer<Label> label18;
    ScopedPointer<Label> label19;
    ScopedPointer<Label> asyncMaxRtTimeLabel;
    ScopedPointer<Label> asyncMinRtTimeLabel;
    ScopedPointer<Label> label20;
    ScopedPointer<Label> asyncPrTimeDisplay;
    ScopedPointer<TextButton> nullAsyncButton;
    ScopedPointer<TextButton> vcoAsyncButton;
    ScopedPointer<TextButton> vcaAsyncButton;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DiauproGUI)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_5290F0CE3B9D4392__
