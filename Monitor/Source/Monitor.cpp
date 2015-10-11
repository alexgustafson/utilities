
/*
  ==============================================================================

    Monitor.cpp
    Created: 9 Aug 2015 1:31:53pm
    Author:  Alexander Gustafson

  ==============================================================================
*/

#include "Monitor.h"

void make_nonblocking(int fd)
{
    fcntl(fd, F_SETFL, O_NONBLOCK);
}

Monitor::Monitor() : FileDescriptorListener("Main Monitor"), Thread ("file descriptor monitor server")
{
    maxfd = 0;
}

Monitor::~Monitor() {
    listenSocket->shutdown();
    controlSocket->shutdown();
}

void Monitor::initializeControlSocket()
{
    
    listenSocket = new DatagramSocket(false);
    if(!listenSocket->bindToPort(0))
    {
        Logger::writeToLog("listenSocket could not bind to a port");
    }
    
    controlSocket = new DatagramSocket(false);
    if(!controlSocket->bindToPort(0))
    {
        Logger::writeToLog("controlSocket could not bind to a port");
    }
    
    control_listener = listenSocket->getRawSocketHandle();
    control_send = controlSocket->getRawSocketHandle();

    make_nonblocking(control_listener);
}

void Monitor::startMonitoring()
{
    initializeControlSocket();
    addFileDescriptorAndListener(control_listener, this, "adding monitor control socket");
    startThread();
}

void Monitor::stop()
{
    String msg("trigger update to monitor list");
    controlSocket->write("0.0.0.0", listenSocket->getBoundPort(), msg.toRawUTF8(), sizeof(msg.toRawUTF8()));
    stopThread(500);
    close(control_listener);
    close(control_send);
}

void Monitor::run()
{
    int result;

    while (! threadShouldExit() )
    {
        FD_ZERO(&readset);
        FD_ZERO(&writeset);
        FD_ZERO(&exset);
        
        for (int i = 0; i < fileDescriptors.size(); i++)
        {
            int fd = fileDescriptors[i];
            if (maxfd < fd)
            {
                maxfd = fd;
            }
            FD_SET(fd, &readset);
        }
        
        result = select(maxfd+1, &readset, &writeset, &exset, 0);
        if (result > 0)
        {

            for (int i = 0; i < fileDescriptors.size(); i++) {
                
                int fd = fileDescriptors[i];
                
                if (FD_ISSET(fd, &readset)) {
                    FileDescriptorListener* listener = map[fd];
                    listener->handleFileDescriptor(fd);
                    
                }
            }
        }
        else
        {
            printf("select() returned %d errno %d %s\n", result, errno, strerror(errno));
        }
    }
}

void Monitor::addFileDescriptorAndListener(int fileDescriptor, FileDescriptorListener* listener, String debugMessage)
{
    // if this fails, you've passed an invalid fileDescriptor
    jassert(fileDescriptor > 0);
    const ScopedLock myScopedLock (lock);
    
    fileDescriptors.add(fileDescriptor);
    map.set(fileDescriptor , listener);
    
    if (fileDescriptor != control_listener) {
        String msg("trigger update to monitor list");
        controlSocket->write("0.0.0.0", listenSocket->getBoundPort(), msg.toRawUTF8(), sizeof(msg.toRawUTF8()));
    }
    
    struct sockaddr_in sin_addr;
    socklen_t len = sizeof (sin_addr);
    getsockname (fileDescriptor, (struct sockaddr*) &sin_addr, &len);
    
    Logger::writeToLog(String::formatted("registered listener %s for fd %d on port %d | %s",listener->getFileDescriptorListenerName().toRawUTF8(),fileDescriptor, ntohs (sin_addr.sin_port), debugMessage.toRawUTF8()));
}

void Monitor::removeFileDescriptorAndListener(int fileDescriptor, bool shoudlClose)
{
    const ScopedLock myScopedLock (lock);
    
    map.remove(fileDescriptor);
    fileDescriptors.removeFirstMatchingValue(fileDescriptor);
    
    if (fileDescriptor != control_listener) {
        String msg("trigger update to monitor list");
        controlSocket->write("0.0.0.0", listenSocket->getBoundPort(), msg.toRawUTF8(), sizeof(msg.toRawUTF8()));
    }
    
    struct sockaddr_in sin_addr;
    socklen_t len = sizeof (sin_addr);
    getsockname (fileDescriptor, (struct sockaddr*) &sin_addr, &len);
    
    Logger::writeToLog(String::formatted("removed listener and fd %d on port %d",fileDescriptor, ntohs (sin_addr.sin_port)));
    
    if (shoudlClose) {
        close(fileDescriptor);
    }
    
}

void Monitor::handleFileDescriptor(int fileDescriptor)
{
    const ScopedLock myScopedLock (lock);

    char buffer[1000];
    recv(fileDescriptor, buffer, sizeof(buffer), 0);

}


