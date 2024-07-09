//
// Created by Administrator on 24-5-14.
//
#include "DataStruct.h"
#include <iostream>

void ServerSocket::Launch() {
#if DEBUG
    std::cout << "Launching server" << "\n";
#endif
    for (int i = 0; i <3 ; i++) {
        if (bind(MainSocketI, (sockaddr *) &MainSocket, sizeof(MainSocket)) < 0) {
            std::cerr << "Error: Unable to bind socket" << "\n";
            sleep(1);
        }
        else {
            break;
        }
    }
    for (int i = 0; i<3; i++) {
        if (listen(MainSocketI, 5) < 0) {
            std::cerr << "Error: Unable to listen on socket" << "\n";
            sleep(1);
        }
#if DEBUG
        else {
            std::cout << "Server launched" << "\n";
            break;
        }
#endif
    }
}

void ServerSocket::AcceptClient() {
    int PollResult = poll(&DetectSocket, 1, 1000);
    for (int i = 0; i < PollResult; i++) {
        if (PollResult < 0) {
            std::cout << "Error: Unable to poll socket" << "\n";
            break;
        }
        if (PollResult == 0) {
            break;
        }
        if (DetectSocket.revents & POLLIN) {
            auto temp = new ClientClass();
            GlobalData->ClientSockets.emplace(temp);
            if (temp->ClientSocketI < 0) {
                delete temp;
                GlobalData->ClientSockets.erase(temp);
            }
            GlobalData->count++;
#if DEBUG
            std::cout << "Client accepted" << "\n";
#endif
        }
    }
}