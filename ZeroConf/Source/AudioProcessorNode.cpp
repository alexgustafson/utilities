/*
  ==============================================================================

    AudioProcessorNode.cpp
    Created: 17 Sep 2015 10:45:07am
    Author:  Alexander Gustafson

  ==============================================================================
*/

#include "AudioProcessorNode.h"



AudioProcessorNode::AudioProcessorNode()
{
    input_socket = socket(AF_INET, SOCK_DGRAM, 0);
    output_socket = socket(AF_INET, SOCK_DGRAM, 0);
    
    fcntl(input_socket, F_SETFL, O_NONBLOCK);
#ifndef WIN32
    {
        int one = 1;
        setsockopt(input_socket, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one));
        setsockopt(output_socket, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one));
    }
#endif
    struct sockaddr_in sin_l, sin_w;
    sin_l.sin_family = AF_INET;
    sin_l.sin_addr.s_addr = 0;
    sin_l.sin_port = htons(53000);
    
    sin_w.sin_family = AF_INET;
    sin_w.sin_addr.s_addr = 0;
    sin_w.sin_port = htons(0);
    
    int result;
    result = bind(input_socket, (struct sockaddr*)&sin_l, sizeof(sin_l));
    
    if (result < 0) {
        printf("bind() returned %d errno %d %s\n", result, errno, strerror(errno));
        return;
    }
    
    result = bind(output_socket, (struct sockaddr*)&sin_w, sizeof(sin_w));
    
    if (result < 0) {
        printf("bind() returned %d errno %d %s\n", result, errno, strerror(errno));
        return;
    }
    
    //struct sockaddr_in get_port;
    //int len_inet;
    
    //result = getsockname(input_socket, (struct sockaddr*)&get_port, (socklen_t *)&len_inet);
    //result = connect(output_socket, (struct sockaddr*)&get_port, sizeof(sin_l));
    
    if (result < 0) {
        printf("connect() returned %d errno %d %s\n", result, errno, strerror(errno));
        return;
    }
};

