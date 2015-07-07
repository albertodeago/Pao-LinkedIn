#ifndef LINKEDCLIENT_H
#define LINKEDCLIENT_H

#include"realuser.h"
#include"linkeddb.h"

class LinkedClient{
private:
    User* usr;
    LinkedDB* database;
public:
    LinkedClient(const Username&);
    ~LinkedClient();
    void save();
    Username& getUsername() const;
    Info* getInfo() const;
    LinkedNet* getNet() const;
    std::string getAvatar() const;
    void setAvatar(const std::string& );
    int getAccType() const;
    void setAccType(accountType);
    std::list<User*> userSearch(const string&) const;
    User* getUserFromUsername(const string&) const;
};

#endif // LINKEDCLIENT_H

