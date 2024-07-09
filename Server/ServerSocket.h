//
// Created by Administrator on 24-5-14.
//

#ifndef SOCKETPROJECT_SERVERSOCKET_H
#define SOCKETPROJECT_SERVERSOCKET_H

#include <iostream>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <poll.h>

static const int ServerPort =  12345;

using IPV4Socket = struct sockaddr_in;
using IODetect = struct pollfd;

class ServerSocket {
public:

    ServerSocket():
        MainSocket({AF_INET, htons(ServerPort), {INADDR_ANY}, 0}),
        MainSocketI(socket(AF_INET, SOCK_STREAM, 0)),
        DetectSocket({MainSocketI, POLLIN, 0})
    {
        if (MainSocketI < 0) {
            std::cerr << "Error: Unable to create main socket" << std::endl;
        }
    }

    IPV4Socket MainSocket;
    int MainSocketI;

    IODetect DetectSocket;

    void Launch();

    void AcceptClient();
};


#endif //SOCKETPROJECT_SERVERSOCKET_H
