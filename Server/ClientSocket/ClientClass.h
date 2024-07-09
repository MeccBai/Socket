//
// Created by Administrator on 24-5-14.
//

#ifndef SOCKETPROJECT_CLIENTCLASS_H
#define SOCKETPROJECT_CLIENTCLASS_H

#include <iostream>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <poll.h>
#include "../UserSQL/UserData.h"

using IPV4Socket = struct sockaddr_in;
using IODetect = struct pollfd;
using String = std::string;

class ClientClass {
public:

    ClientClass();

    IPV4Socket ClientSocket;
    int ClientSocketI;
    IODetect DetectSocket;
    char * Buffer;

    void Send() const;

    UserData * Ascess;

    bool Recieve();

    void ClearBuffer() const;

    void SetString(String _string) const;

    ~ClientClass();

    bool operator > (const ClientClass & _clientClass) const;

    void Close();

};


#endif //SOCKETPROJECT_CLIENTCLASS_H
