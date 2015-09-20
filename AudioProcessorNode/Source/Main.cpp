/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "Monitor.h"
#include "AudioProcessorNode.h"

//==============================================================================
int main (int argc, char* argv[])
{

    // ..your code goes here!
    Monitor monitor;
    monitor.startMonitoring();
    
    AudioProcessorNode audioProcessorNode;
    ScopedPointer<ZeroConfManager> zeroConfManager = new ZeroConfManager(&monitor, &audioProcessorNode);
    ScopedPointer<ZeroConfService> service = new ZeroConfService();
    
    service->setPort(htons(53000));
    service->setServiceName("Audio_Processor_Node");
    service->setRegType("_diapro._udp");
    
    zeroConfManager->registerService(service);
    monitor.addFileDescriptorAndListener(audioProcessorNode.input_socket, &audioProcessorNode);
    
    std::cout << "press enter to exit...";
    getchar();
    
    monitor.stop();
    
    return 0;
}
