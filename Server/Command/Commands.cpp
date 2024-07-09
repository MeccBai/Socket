//
// Created by Administrator on 24-5-16.
//

#include <utility>

#include "../DataStruct.h"

#if 0
Commands:
login --username --password
logot --username
regst --username --password
showm --username
sendm --username --message
findu --username
endse --rootname --password
#endif

CommandType Commands::GetCommandType(const String & _command) {
    if (_command.find("login") != String::npos) {
        return Login;
    }
    if (_command.find("logot") != String::npos) {
        return Logout;
    }
    if (_command.find("regst") != String::npos) {
        return Register;
    }
    if (_command.find("showm") != String::npos) {
        return ShowMessages;
    }
    if (_command.find("sendm") != String::npos) {
        return SendMessage;
    }
    if (_command.find("findu") != String::npos) {
        return FindUser;
    }
    if (_command.find("endse") != String::npos) {
        return EndServer;
    }
    return UnKnown;
}

Commands::CommandPair::CommandPair(String username,String target) :
    UserName(std::move(username)),Target(std::move(target)) {}

Commands::CommandPair Commands::CommandAnlysis(const String & _command) {
    int i = 6;
    String userName {}; String target {};
    for (;i<_command.size();i++) {
        if (_command[i] == ' ') {
            break;
        }
        userName += _command[i];
    }
    i++;
    for (;i<_command.size();i++) {
        if (_command[i] == ' ') {
            break;
        }
        target += _command[i];
    }
    return {userName,target};
}

void Commands::Init() {
    CommandMaps[Login] = [](UserData * user,const CommandPair& pair) -> bool {
        auto it = GlobalData->UserSQL.find(pair.UserName);
        if (it != GlobalData->UserSQL.end()) {
            if (it->second->LoginStatus) {
                it->second->Client->SetString("User Already Login");
                return false;
            }
            auto temp = it->second;
            if (temp->VerifyPassWord(pair.Target)) {
                temp->Client->SetString("Login Success");
                temp->Client->Ascess = temp;
                return true;
            }
            temp->Client->SetString("Login Failed");
            return false;
        }
        it->second->Client->SetString("User Not Found");
        return false;
    };

    CommandMaps[Logout] = [](UserData * user,const CommandPair& pair) -> bool {
        auto it = GlobalData->UserSQL.find(pair.UserName);
        if (it != GlobalData->UserSQL.end()) {
            auto temp = it->second;
            temp->Client->SetString("Logout Success");
            GlobalData->UserFilesSQL.FileSave(pair.UserName);

            GlobalData->UserSQL.erase(it);
            delete user;

            GlobalData->ClientSockets.erase(temp->Client);

            return true;
        }
        it->second->Client->SetString("User Not Found");
        return false;
    };

    CommandMaps[ShowMessages] = [](UserData * user,CommandPair& pair) -> bool {
        auto it = GlobalData->UserSQL.find(pair.UserName);
        if (user != it->second) {
            it->second->Client->SetString("User Not Match");
            return false;
        }
        if (it->second->LoginStatus) {
            String result;
            for (auto & i : it->second->Messages) {
                result += i + "\n";
            }
            it->second->Client->SetString(result);
            return true;
        }
        it->second->Client->SetString("User Not Login");
        return false;
    };

    CommandMaps[FindUser] = [](UserData * user,CommandPair& pair) -> bool {
        auto it = GlobalData->UserSQL.find(pair.UserName);
        if (it != GlobalData->UserSQL.end()) {
            it->second->Client->SetString("User Found");
            return true;
        }
        it->second->Client->SetString("User Not Found");
        return false;
    };

    CommandMaps[SendMessage] = [](UserData * user,CommandPair& pair) -> bool {
        auto it = GlobalData->UserSQL.find(pair.UserName);
        if (it != GlobalData->UserSQL.end()) {
            if (it->second->LoginStatus) {
                it->second->Messages.push_back(pair.Target);
                it->second->Client->SetString("Message Send Success");
                return true;
            }
            it->second->Client->SetString("User Not Login");
            return false;
        }
        it->second->Client->SetString("User Not Found");
        return false;
    };

    CommandMaps[EndServer] = [](UserData * user,CommandPair& pair) -> bool {
        if (pair.UserName == "root") {
            if (pair.Target == "123456") {
                auto temp = user->Client;
                GlobalData->Run = false;
                temp->SetString("Server Will Closed");
                return true;
            }
        }
        user->Client->SetString("Root Verify Error");
        return false;
    };

    CommandMaps[UnKnown] = [](UserData * user,CommandPair& pair) -> bool {
        user->Client->SetString("UnKnown Command");
        return true;
    };


}


Commands::Commands() {
    Init();
#if DEBUG
    std::cout << "Command Inited" << std::endl;
#endif
}

bool Commands::CommandPreExcute(const CommandPair& _pair) {
    auto it = GlobalData->UserSQL.find(_pair.UserName);
    if (it != GlobalData->UserSQL.end() || GlobalData->UserFilesSQL.FileLoad(_pair.UserName)) {
        return true;
    }
    return false;
}

void Commands::Resigter(const std::pair<ClientClass *, UserData *> & _task,const CommandPair& _pair) {
    auto * temp = new UserData(_pair.UserName,_pair.Target,(GlobalData->count)++,_task.first);
    GlobalData->UserSQL[_pair.UserName] = temp;
    GlobalData->UserFilesSQL.FileSave(_pair.UserName);
    _task.first->SetString("Register Success");
}

void Commands::CommandExcute() {
    for (auto & task : GlobalData->Tasks) {
        CommandType type = GetCommandType(task.first->Buffer);
        if (!CommandPreExcute(CommandAnlysis(task.first->Buffer))) {
            if (type == Register) {
                Resigter(task,CommandAnlysis(task.first->Buffer));
                continue;
            }
        }
        CommandPair pair = CommandAnlysis(task.first->Buffer);
        CommandMaps[type](task.second,pair);
#if DEBUG
        std::cout << "Command Excute " << task.second->Client->Buffer << std::endl;
#endif
    }
}