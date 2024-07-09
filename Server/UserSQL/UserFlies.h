//
// Created by Administrator on 24-5-14.
//

#ifndef SOCKETPROJECT_USERFLIES_H
#define SOCKETPROJECT_USERFLIES_H
#include <fstream>
#include <map>

class UserFlies {
public:

    std::ifstream * DataIn;
    std::ofstream * DataOut;

    std::map<int,String> DataFiles;

    const String DataPath;

    const String Index;

    void AllSave();

    void AllLoad();

    bool FileLoad(String username);

    void FileSave(const String& username);

    ~UserFlies();

    UserFlies();
};


#endif //SOCKETPROJECT_USERFLIES_H
