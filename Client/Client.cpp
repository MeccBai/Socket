//
// Created by Mecc on 24-5-12.
//

#include <iostream>
#include <string>
#include <cstring>  // 用于处理C风格字符串操作
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>  // 用于close()

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 12345
using IPV4Socket = struct sockaddr_in;

int main() {
    int sock;
    IPV4Socket server_addr;
    std::string input;
    char buffer[1024];

    // 创建socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        std::cerr << "Failed to create socket: " << strerror(errno) << std::endl;
        return 1;
    }

    // 设置服务器地址
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);

    // 连接到服务器
    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Failed to connect to the server: " << strerror(errno) << std::endl;
        close(sock);
        return 1;
    }

    std::cout << "Connected to " << SERVER_IP << ":" << SERVER_PORT << std::endl;

    while (true) {
        std::cout << "Enter message: \n";
        std::getline(std::cin, input);

        if (input.empty()) break;

        // 发送数据
        send(sock, input.c_str(), input.size(), 0);

        // 清空缓冲区接收响应
        memset(buffer, 0, sizeof(buffer));
        auto bytes_received = recv(sock, buffer, sizeof(buffer) - 1, 0);
        if (bytes_received <= 0) {
            std::cout << "Server closed the connection or recv failed." << std::endl;
            break;
        }

        std::cout << "Server > " << buffer << std::endl;
    }

    // 关闭socket
    close(sock);
    return 0;
}
