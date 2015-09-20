/*
  ==============================================================================

    AudioProcessorNode.h
    Created: 17 Sep 2015 10:45:07am
    Author:  Alexander Gustafson

  ==============================================================================
*/

#ifndef AUDIOPROCESSORNODE_H_INCLUDED
#define AUDIOPROCESSORNODE_H_INCLUDED

#include "ZeroConfManager.h"

class AudioProcessorNode :  public FileDescriptorListener,
                            public ZeroConfListener
{
public:
    AudioProcessorNode();
    ~AudioProcessorNode() {};
    
    void handleFileDescriptor(int fileDescriptor)
    {
        Logger::writeToLog("notified on input socket");

    }
    
    void handleZeroConfUpdate(OwnedArray<ZeroConfService> *serviceList)
    {
        Logger::writeToLog("notified");

    };
    
    int input_socket;
    
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioProcessorNode)
    int output_socket;
};



#endif  // AUDIOPROCESSORNODE_H_INCLUDED
