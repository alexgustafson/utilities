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

#ifndef __JUCE_HEADER_21E7EA1F0291AFBC__
#define __JUCE_HEADER_21E7EA1F0291AFBC__

//[Headers]     -- You can add your own extra header files here --
#include "JuceHeader.h"
#include "Monitor.h"
#include "ZeroConfManager.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class NetworkBrowser  : public Component,
                        public ListBoxModel,
                        public ZeroConfListener,
                        public AsyncUpdater
{
public:
    //==============================================================================
    NetworkBrowser ();
    ~NetworkBrowser();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    juce_UseDebuggingNewOperator;
    void initializeWithMonitor(Monitor *mon){

        this->monitor = mon;
        this->zeroconfManager = new ZeroConfManager(mon, this);
        this->zeroconfManager->browseService("_diapro._udp");

    };

    
    class NetworkBrowserListener
    {
    public:
        virtual ~NetworkBrowserListener() {};
        virtual void networkItemChanged(ZeroConfService* serviceThatChanged) = 0;
    };

    int getNumRows () override
    {
        int count = listData.size();
        return count;
    };

    void paintListBoxItem (int rowNumber, Graphics &g, int width, int height, bool rowIsSelected) override
    {
        if (rowIsSelected)
            g.fillAll (Colours::lightblue);

        g.setColour (Colours::black);
        g.drawText (listData.getReference(rowNumber)->getHosttarget(), 4, 0, width - 4, height, Justification::centredLeft, true);
    }

    void handleZeroConfUpdate(OwnedArray<ZeroConfService> *serviceList) override
    {
        listData.clear();
        
        for (int i = 0; i < serviceList->size(); i++) {
            ZeroConfService* service = serviceList->getUnchecked(i);
            listData.add(service);
            listeners.call(&NetworkBrowser::NetworkBrowserListener::networkItemChanged, service);
        }
        triggerAsyncUpdate();
    }

    void handleAsyncUpdate() override{
        listBox.updateContent();
    }
    
    void 	listBoxItemClicked (int row, const MouseEvent &e) override;
    
    void addListener(NetworkBrowserListener* listener);

    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;


private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    Monitor* monitor;
    ScopedPointer<ZeroConfManager> zeroconfManager;
    Array<ZeroConfService *> listData;
    ListBox listBox;
    ListenerList<NetworkBrowserListener> listeners;
    //[/UserVariables]

    //==============================================================================


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NetworkBrowser)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_21E7EA1F0291AFBC__
