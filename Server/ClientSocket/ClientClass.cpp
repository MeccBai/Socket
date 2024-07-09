//
// Created by Administrator on 24-5-14.
//

#include "../DataStruct.h"
#include<string.h>
#include <unistd.h>

unsigned int addlen = sizeof (struct sockaddr);

ClientClass::ClientClass() :
    ClientSocket({AF_INET, htons(8080), {INADDR_ANY}}),
    ClientSocketI(accept(GlobalData->ServerMain.MainSocketI, (struct sockaddr*)&ClientSocket, &addlen)),
    DetectSocket({ClientSocketI, POLLIN, 0}),
    Buffer(new char[1024]{0}),Ascess(nullptr)
{
    if (ClientSocketI < 0) {
        std::cout << "Error: Unable to create socket" << "\n";
    }
    else {
#if DEBUG
        std::cout << "New Client Socket Created" << "\n";
#endif
    }

}

ClientClass::~ClientClass() {
    delete[] Buffer;
}

void ClientClass::Send() const {
    const auto Result = send(ClientSocketI, Buffer, strlen(Buffer), 0);
    if (Result < 0) {
        std::cout << "Error: Unable to send data" << "\n";
    }
}

bool ClientClass::Recieve() {
#if DEBUG
    std::cout << "Recieving data" << "\n";
#endif
    memset(Buffer, 0, 1024);
    const auto PollResult = poll(&DetectSocket, 1, 1000);
    if (PollResult < 0) {
        std::cout << "Error: Unable to poll socket" << "\n";
        return false;
    }
    if (DetectSocket.revents & POLLIN) {
        const auto Result = recv(ClientSocketI, Buffer, 1024, 0);
        if (Result < 0) {
            std::cout << "Error: Unable to recieve data" << "\n";
            return false;
        }
        return true;
    }
#if DEBUG
    std::cout << "Data recieved" << Buffer << "\n";
#endif
    return false;

}


void ClientClass::ClearBuffer() const {
    memset(Buffer, 0, 1024);
}

void ClientClass::SetString(String _string) const {
    memset(Buffer, 0, 1024);
    strcpy(Buffer, _string.c_str());
}

bool ClientClass::operator > (const ClientClass & clientClass) const {
    return ClientSocketI > clientClass.ClientSocketI;
}

void ClientClass::Close() {
    close(ClientSocketI);
}