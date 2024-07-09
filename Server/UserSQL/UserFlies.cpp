//
// Created by Administrator on 24-5-14.
//

#include "../DataStruct.h"
#include <fstream>
#include <string>

#if 0
Index:
--username
    --
    --
    --
    --

files
--username
--password
--messages
    --
    --
    --
    --

#endif

UserFlies::UserFlies():
    DataIn(new std::ifstream),DataOut(new std::ofstream),
    DataPath("UserData/"),Index("UserData/Index.txt"){}

bool UserFlies::FileLoad(String username) {
#if DEBUG
    std::cout << "Loading " << username << std::endl;
#endif
    DataIn->open(DataPath + username);
    if(DataIn->is_open()) {
        std::getline(*DataIn,username);
        std::getline(*DataIn,GlobalData->UserSQL[username]->PassWord);
        while(!DataIn->eof()) {
            String temp;
            std::getline(*DataIn,temp);
            GlobalData->UserSQL[username]->Messages.push_back(temp);
        }
        return true;
    }
    else {
        return false;
    }
}

void UserFlies::FileSave(const String& username) {
    DataOut->open(DataPath + username);
    if(DataOut->is_open()) {
        *DataOut << GlobalData->UserSQL[username]->UserName << "\n";
        *DataOut << GlobalData->UserSQL[username]->PassWord << "\n";
        for(auto & i : GlobalData->UserSQL[username]->Messages) {
            *DataOut << i << "\n";
        }
    }
}

UserFlies::~UserFlies() {
    DataIn->close();
    DataOut->close();
    delete DataIn;
    delete DataOut;
}

#if __FILE__ALL__ENABLE__
void UserFlies::AllLoad() {
    DataIn->open(Index);
    if(DataIn->is_open()) {
        while(!DataIn->eof()) {
            int temp;
            String temp2;
            *DataIn >> temp >> temp2;
            DataFiles[temp] = temp2;
        }
    }
    for(auto & i : DataFiles) {
        FileLoad(i.second);
    }
}
#endif

void UserFlies::AllSave() {
    DataOut->open(Index);
    if(DataOut->is_open()) {
        for(auto & i : DataFiles) {
            *DataOut << i.first << " " << i.second << std::endl;
        }
    }
    for(auto & i : DataFiles) {
        FileSave(i.second);
    }
}