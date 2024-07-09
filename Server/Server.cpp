//
// Created by Administrator on 24-5-14.
//

#include "ServerSocket.h"
#include "DataStruct.h"

int main() {

    GlobalData = new DataStruct();

    GlobalData->ServerMain.Launch();

    CommandExecute.Init();

    while (GlobalData->Run) {

        GlobalData->ServerMain.AcceptClient();

        for (auto client : GlobalData->ClientSockets) {
            if (client->Recieve()) {
                GlobalData->Tasks.emplace(client,client->Ascess);
            }
        }

        CommandExecute.CommandExcute();

        for (const auto & client : GlobalData->Tasks) {
            client.first->Send();
        }

        GlobalData->Tasks.clear();
    }

    GlobalData->UserFilesSQL.AllSave();

    delete GlobalData;

    return 0;
}