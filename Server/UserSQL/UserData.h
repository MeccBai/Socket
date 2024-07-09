//
// Created by Administrator on 24-5-14.
//

#ifndef SOCKETPROJECT_USERDATA_H
#define SOCKETPROJECT_USERDATA_H
#include <unordered_map>
#include <string>
#include <vector>
#include <memory>
class ClientClass;

class UserData;
using String = std::string;
using MessageBox = std::vector<String>;

class UserData {
public:

    UserData(String _userName,String _passWord,int _fileID,ClientClass * _clientClass);

    UserData(const UserData & _userData) = delete;

    String UserName;

    String PassWord;

    MessageBox Messages;

    bool VerifyPassWord(const String & _passWord);

#ifdef __PW__MD__ENABLE__
    void ModifyPassWord(const String & newpassword);
#endif

    ClientClass * Client;

    int FileID;

    bool LoginStatus;

    ~UserData();

};

#endif //SOCKETPROJECT_USERDATA_H
