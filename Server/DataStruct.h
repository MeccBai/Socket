//
// Created by Administrator on 24-5-14.
//

#ifndef SOCKETPROJECT_DATASTRUCT_H
#define SOCKETPROJECT_DATASTRUCT_H

#include <unordered_map>
#include <map>

#include "ServerSocket.h"
#include "ClientSocket/ClientClass.h"
#include "UserSQL/UserData.h"
#include "UserSQL/UserFlies.h"
#include "Command/Commands.h"
#include <set>

using String = std::string;
class ClientClass;

class DataStruct {
public:
    DataStruct():
        ServerMain(ServerSocket()),UserFilesSQL(UserFlies()),Run(true),count(0)
    {};

    DataStruct operator = (const DataStruct & dataStruct) = delete;

    int count;

    bool Run;

    ~DataStruct() = default;

    ServerSocket ServerMain;

    UserFlies UserFilesSQL;

    std::set<ClientClass*> ClientSockets;

    std::unordered_map<String,UserData*> UserSQL;

    std::map<int,String> UserPaths;

    std::map <ClientClass*,UserData*> Tasks;

};

extern DataStruct * GlobalData;

extern UserFlies * FileManager;

extern Commands CommandExecute;

#endif //SOCKETPROJECT_DATASTRUCT_H
