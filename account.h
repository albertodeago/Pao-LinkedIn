#ifndef ACCOUNT
#define ACCOUNT

#include"info.h"
#include"username.h"
#include<list>

typedef enum { _basic, _business, _executive } accountType;

class Account{
private:
    Info* info;
    Username credentials;
    std::string avatarPath;
    accountType accType;
public:
    Account(Info*, const Username&, accountType);
    Account(const Account&);
    ~Account();
    Account* clone() const;
    Account& operator=(const Account&);
    Username& username();
    Info* getInfo() const;
    std::string getAvatar() const;
    void setAvatar(const std::string&);
    accountType getType() const;
    void setType(accountType);
};

#endif // ACCOUNT

