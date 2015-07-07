#include"account.h"

Account::Account(Info* i, const Username& u, accountType t): info(i->clone()), credentials(u), accType(t){}

Account::Account(const Account& acc): info(acc.info->clone()), credentials(acc.credentials), avatarPath(acc.avatarPath), accType(acc.accType){}

Account::~Account(){
    delete info;
}

Account* Account::clone() const{
    return new Account(*this);
}

Account& Account::operator=(const Account& acc){
    if(this != &acc){
        delete info;
        info = (acc.info)->clone();
        credentials = acc.credentials;
        avatarPath = acc.avatarPath;
        accType = acc.accType;
    }
    return *this;
}

Username& Account::username(){
    return credentials;
}

Info* Account::getInfo() const{
    return info;
}

std::string Account::getAvatar() const{
    return avatarPath;
}
void Account::setAvatar(const std::string& ap){
    avatarPath = ap;
}
accountType Account::getType() const{
    return accType;
}
void Account::setType(accountType t){
    accType = t;
}
