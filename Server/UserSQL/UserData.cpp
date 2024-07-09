
//
// Created by Administrator on 24-5-14.
//

#include <utility>

#include "../DataStruct.h"

UserData::UserData(String _userName,String _passWord,int _fileID,ClientClass * _clientClass) :
    UserName(std::move(_userName)),PassWord(std::move(_passWord)),FileID(_fileID),Client(_clientClass),LoginStatus(false) {}

bool UserData::VerifyPassWord(const String & _passWord) {
    LoginStatus = (PassWord == _passWord);
    return LoginStatus;
}

#if __PW__MD__ENABLE__
void UserData::ModifyPassWord(const String & newpassword) {
    PassWord = newpassword;
}
#endif

UserData::~UserData() = default;

