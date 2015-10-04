/*
  ==============================================================================

    Monitor.h
    Created: 9 Aug 2015 1:31:53pm
    Author:  Alexander Gustafson

  ==============================================================================
*/

#ifndef MONITOR_H_INCLUDED
#define MONITOR_H_INCLUDED

#include "JuceHeader.h"
#include <netinet/in.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/select.h>



class FileDescriptorListener
{
public:
    explicit FileDescriptorListener(const String& _listenerName) : listenerName (_listenerName) {};
    virtual ~FileDescriptorListener() {};
    virtual void handleFileDescriptor(int fileDescriptor) = 0;
    String getFileDescriptorListenerName() { return this->listenerName; };
private:
    String listenerName;
};

class Monitor : public FileDescriptorListener, Thread
{
public:
    Monitor();
    ~Monitor();
    
    void initializeControlSocket();
    void addFileDescriptorAndListener(int fileDescriptor, FileDescriptorListener* listener, String debugMessage = "");
    void removeFileDescriptorAndListener(int fileDescriptor, bool shoudlClose=false);
    void startMonitoring();
    void stop();
    
    void handleFileDescriptor(int fileDescriptor) override;
    
private:
    fd_set readset, writeset, exset;
    HashMap<int, FileDescriptorListener *> map;
    int maxfd;
    int control_listener;
    int control_send;
    struct sockaddr control_address;
    socklen_t len_control_address;

    void run() override;
    int control_socket_port;
    
    Array<int> fileDescriptors;
    CriticalSection lock;
    
    ScopedPointer<DatagramSocket> listenSocket, controlSocket;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Monitor)
};

#endif  // MONITOR_H_INCLUDED
