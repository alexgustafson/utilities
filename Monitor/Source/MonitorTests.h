/*
  ==============================================================================

    MonitorTests.h
    Created: 9 Aug 2015 1:32:09pm
    Author:  Alexander Gustafson

  ==============================================================================
*/

#ifndef MONITORTESTS_H_INCLUDED
#define MONITORTESTS_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "Monitor.h"

class MonitorTests : public UnitTest
{
public:
    MonitorTests() : UnitTest("") { pool = new ThreadPool(50); }
    
    void firstTest();
    void startUpAndShutDownTest();
    void callBackTest();
    void multiThreadedCallBackTest();
    void runTest();
    
private:
    
    class SocketListener : public ThreadPoolJob, FileDescriptorListener
    {
    public:
        SocketListener() : ThreadPoolJob("Watcher"), FileDescriptorListener("Socket Listener") {}
        ~SocketListener() {
            close(socket_to_trigger);
            close(socket_to_watch);

        }
        
        void initializeSockets(int port, Monitor* monitor, String msg) {
            
            message = msg;
            was_informed = false;
            this->monitor = monitor;
            
            socket_to_watch = socket(AF_INET, SOCK_DGRAM, 0);
            socket_to_trigger = socket(AF_INET, SOCK_DGRAM, 0);
            
            fcntl(socket_to_watch, F_SETFL, O_NONBLOCK);
#ifndef WIN32
            {
                int one = 1;
                setsockopt(socket_to_watch, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one));
            }
#endif
            struct sockaddr_in sin_l, sin_w;
            sin_l.sin_family = AF_INET;
            sin_l.sin_addr.s_addr = 0;
            sin_l.sin_port = htons(port);
            
            sin_w.sin_family = AF_INET;
            sin_w.sin_addr.s_addr = 0;
            sin_w.sin_port = htons(port + 1);
            
            int result;
            result = bind(socket_to_watch, (struct sockaddr*)&sin_l, sizeof(sin_l));
            
            if (result < 0) {
                printf("bind() returned %d errno %d %s\n", result, errno, strerror(errno));
                return;
            }
            
            result = bind(socket_to_trigger, (struct sockaddr*)&sin_w, sizeof(sin_w));
            
            if (result < 0) {
                printf("bind() returned %d errno %d %s\n", result, errno, strerror(errno));
                return;
            }
            
            result = connect(socket_to_trigger, (struct sockaddr*)&sin_l, sizeof(sin_l));
            
            if (result < 0) {
                printf("connect() returned %d errno %d %s\n", result, errno, strerror(errno));
                return;
            }
        }
        void handleFileDescriptor(int fileDescriptor) override
        {
            char buffer[1000];
            int recv_msg_size = recv(socket_to_watch, buffer, sizeof(buffer), 0);
            String response(buffer, recv_msg_size);
            Logger::writeToLog("Listener Expected: " + message + " Recieved: " + response);
            if(!response.equalsIgnoreCase(message) || !was_informed )
            {
                was_informed = false;
            }
        }
        
        void sendMessage()
        {
            write(socket_to_trigger, message.toRawUTF8(), strlen(message.toRawUTF8()));
        }
        
        JobStatus runJob() override
        {
            monitor->addFileDescriptorAndListener(socket_to_watch, this);
            was_informed = true;
            Random random;

            for (int i = 0; i < 10; i++)
            {
                Thread::sleep(random.nextInt(4));
                sendMessage();
            }
            return jobHasFinished;
        }
        
        String message;
        int socket_to_watch;
        int socket_to_trigger;
        bool was_informed;
        Monitor* monitor;
    private:
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SocketListener)
    };

    ScopedPointer<ThreadPool> pool;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MonitorTests)
};




#endif  // MONITORTESTS_H_INCLUDED
