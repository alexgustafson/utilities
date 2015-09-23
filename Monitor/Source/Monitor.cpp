
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
    close(control_listener);
    close(control_send);
}

void Monitor::initializeControlSocket()
{
    control_listener = socket(AF_INET, SOCK_DGRAM, 0);
    control_send = socket(AF_INET, SOCK_DGRAM, 0);
    
    make_nonblocking(control_listener);
#ifndef WIN32
    {
        int one = 1;
        setsockopt(control_listener, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one));
        setsockopt(control_send, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one));
    }
#endif
    struct sockaddr_in sin_l, sin_w;
    sin_l.sin_family = AF_INET;
    sin_l.sin_addr.s_addr = 0;
    sin_l.sin_port = 0;
    
    sin_w.sin_family = AF_INET;
    sin_w.sin_addr.s_addr = 0;
    sin_w.sin_port = 0;
    
    int result;
    result = bind(control_listener, (struct sockaddr*)&sin_l, sizeof(sin_l));
    
    if (result < 0) {
        printf("bind() returned %d errno %d %s\n", result, errno, strerror(errno));
        return;
    }
    
    result = bind(control_send, (struct sockaddr*)&sin_w, sizeof(sin_w));
    
    if (result < 0) {
        printf("bind() returned %d errno %d %s\n", result, errno, strerror(errno));
        return;
    }
    
    result = getsockname(control_listener, (struct sockaddr*)&control_address, (socklen_t *)&len_control_address);


}

void Monitor::startMonitoring()
{
    initializeControlSocket();
    addFileDescriptorAndListener(control_listener, this);
    startThread();
    Thread::sleep(200);
}

void Monitor::stop()
{
    sendto(control_send, "shutdown", 9 * sizeof(char), 0, &control_address, len_control_address);
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
                    
                    Logger::writeToLog(String::formatted("update on fd %d with listener: %s",fd, listener->getFileDescriptorListenerName().toRawUTF8()));
                }
            }
        }
        else
        {
            printf("select() returned %d errno %d %s\n", result, errno, strerror(errno));
        }
    }
}

void Monitor::addFileDescriptorAndListener(int fileDescriptor, FileDescriptorListener* listener)
{
    // if this fails, you've passed an invalid fileDescriptor
    jassert(fileDescriptor > 0);
    const ScopedLock myScopedLock (lock);
    
    fileDescriptors.add(fileDescriptor);
    map.set(fileDescriptor , listener);
    
    if (fileDescriptor != control_listener) {
        sendto(control_send, "reset select", 13 * sizeof(char), 0, &control_address, len_control_address);
    }
    struct sockaddr_in sin_addr;
    socklen_t len = sizeof (sin_addr);
    getsockname (fileDescriptor, (struct sockaddr*) &sin_addr, &len);
    
    Logger::writeToLog(String::formatted("registered listener %s for fd %d on port %d",listener->getFileDescriptorListenerName().toRawUTF8(),fileDescriptor, ntohs (sin_addr.sin_port)));
}

void Monitor::removeFileDescriptorAndListener(int fileDescriptor)
{
    const ScopedLock myScopedLock (lock);
    
    map.remove(fileDescriptor);
    fileDescriptors.removeFirstMatchingValue(fileDescriptor);
    
    if (fileDescriptor != control_listener) {
        sendto(control_send, "reset select", 13 * sizeof(char), 0, &control_address, len_control_address);

    }
    struct sockaddr_in sin_addr;
    socklen_t len = sizeof (sin_addr);
    
    getsockname (fileDescriptor, (struct sockaddr*) &sin_addr, &len);
    
    Logger::writeToLog(String::formatted("removed listener for port %d", ntohs (sin_addr.sin_port)));
    
}

void Monitor::handleFileDescriptor(int fileDescriptor)
{
    const ScopedLock myScopedLock (lock);

    char buffer[1000];
    recv(fileDescriptor, buffer, sizeof(buffer), 0);

}


