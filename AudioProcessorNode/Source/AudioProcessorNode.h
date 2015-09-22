/*
  ==============================================================================

    AudioProcessorNode.h
    Created: 17 Sep 2015 10:45:07am
    Author:  Alexander Gustafson

  ==============================================================================
*/

#ifndef AUDIOPROCESSORNODE_H_INCLUDED
#define AUDIOPROCESSORNODE_H_INCLUDED

#include "../../ZeroConf/Source/ZeroConfManager.h"

class AudioProcessorNode :  public FileDescriptorListener,
                            public ZeroConfListener
{
public:
    AudioProcessorNode();
    ~AudioProcessorNode() {};
    
    void handleFileDescriptor(int fileDescriptor)
    {
        
        bytesRead = sock_in->read(buffer->getWritePointer(0), buffer->getNumChannels() * buffer->getNumSamples() + sizeof(float), false, senderHost, senderPort);
        
        sock_in->write(senderHost, senderPort, buffer->getReadPointer(0), bytesRead);

    }
    
    void handleZeroConfUpdate(OwnedArray<ZeroConfService> *serviceList)
    {
        Logger::writeToLog("notified");
    };
    
    int input_socket;
    
    
private:
    
    int output_socket;
    ScopedPointer<DatagramSocket> sock_in;
    ScopedPointer<AudioSampleBuffer> buffer;
    
    int senderPort;
    int bytesRead;
    String senderHost;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioProcessorNode)
};



#endif  // AUDIOPROCESSORNODE_H_INCLUDED
