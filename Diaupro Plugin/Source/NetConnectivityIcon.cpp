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

#include "NetConnectivityIcon.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
NetConnectivityIcon::NetConnectivityIcon ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]


    //[UserPreSize]
    stateColour = Colours::white;
    //[/UserPreSize]

    setSize (100, 18);


    //[Constructor] You can add your own custom stuff here..

    //[/Constructor]
}

NetConnectivityIcon::~NetConnectivityIcon()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]



    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void NetConnectivityIcon::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    g.setColour (Colour (0xff40ff00));
    g.fillEllipse (4.0f, 4.0f, 10.0f, static_cast<float> (getHeight() - 8));

    g.setColour (Colour (0xff00cdff));
    g.drawEllipse (4.0f, 4.0f, 10.0f, static_cast<float> (getHeight() - 8), 1.000f);

    g.setColour (Colours::black);
    g.setFont (Font (9.90f, Font::plain));
    g.drawText (TRANS("Network Status"),
                25, 2, 63, getHeight() - 4,
                Justification::centredLeft, true);

    //[UserPaint] Add your own custom painting code here..
    g.setColour (stateColour);
    g.fillEllipse (4.0f, 4.0f, 10.0f, static_cast<float> (getHeight() - 8));
    //[/UserPaint]
}

void NetConnectivityIcon::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void NetConnectivityIcon::setActive(bool state)
{
    if (!state) {
        stateColour = Colours::white;
    }else {
        stateColour = Colour (0xff40ff00);
    }
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="NetConnectivityIcon" componentName=""
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="100" initialHeight="18">
  <BACKGROUND backgroundColour="ffffffff">
    <ELLIPSE pos="4 4 10 8M" fill="solid: ff40ff00" hasStroke="1" stroke="1, mitered, butt"
             strokeColour="solid: ff00cdff"/>
    <TEXT pos="25 2 63 4M" fill="solid: ff000000" hasStroke="0" text="Network Status"
          fontname="Default font" fontsize="9.9000000000000003553" bold="0"
          italic="0" justification="33"/>
  </BACKGROUND>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
