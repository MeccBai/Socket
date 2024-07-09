cmake_minimum_required(VERSION 3.22)
project(SocketProject)

set(CMAKE_CXX_STANDARD 23)

#add_definitions(-D DEBUG)


add_executable(
    Server
        Server/ServerSocket.h
        Server/ClientSocket/ClientClass.cpp
        Server/ClientSocket/ClientClass.h
        Server/DataStruct.h
        Server/ServerSocket.cpp
        Server/UserSQL/UserData.cpp
        Server/UserSQL/UserData.h
        Server/GlobalVars.cpp
        Server/UserSQL/UserFlies.cpp
        Server/UserSQL/UserFlies.h
        Server/Command/Commands.cpp
        Server/Command/Commands.h
        Server/Server.cpp
)

target_link_libraries(Server std)

add_executable(
    Client
        Client/Client.cpp
)
