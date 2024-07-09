//
// Created by Administrator on 24-5-16.
//

#ifndef SOCKETPROJECT_COMMANDS_H
#define SOCKETPROJECT_COMMANDS_H

#include <unordered_map>
#include <functional>

enum CommandType: unsigned  char {
    Login,
    Logout,
    Register,
    ShowMessages,
    SendMessage,
    FindUser,
    EndServer,
    UnKnown
};



class Commands {
public:

    Commands();

    class CommandPair {
    public:
        CommandPair(String _username,String _target);
        const String UserName;
        const String Target;
    };

    std::unordered_map<CommandType,std::function<bool(UserData*,Commands::CommandPair&)>> CommandMaps;

    void Init();

    static CommandType GetCommandType (const String & _command) ;

    static CommandPair CommandAnlysis (const String & _command) ;
    static bool CommandPreExcute (const CommandPair& _pair) ;

    void CommandExcute () ;

    bool operator = (const Commands & other) = delete;

    static void Resigter(const std::pair<ClientClass *, UserData *> &task,const CommandPair& pair);
};


#endif //SOCKETPROJECT_COMMANDS_H
