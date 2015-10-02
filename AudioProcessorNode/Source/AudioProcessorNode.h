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
#include "DiauproMessage.h"


class AudioProcessorNode :  public FileDescriptorListener,
                            public ZeroConfListener
{
public:
    AudioProcessorNode();
    ~AudioProcessorNode() { };
    
    void handleFileDescriptor(int fileDescriptor);
    void handleZeroConfUpdate(OwnedArray<ZeroConfService> *serviceList);
    
    int getPort();
    int getSock();
    
private:
    
    ScopedPointer<DatagramSocket> socket;
    ScopedPointer<AudioSampleBuffer> buffer;
    ScopedPointer<DiauproMessage> message;
    
    int senderPort;
    int bytesRead;
    String senderHost;
    
    int sock;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioProcessorNode)
};



#endif  // AUDIOPROCESSORNODE_H_INCLUDED
