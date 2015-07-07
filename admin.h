#ifndef ADMIN
#define ADMIN

#include"linkeddb.h"
#include"user.h"

class Admin{
private:
    LinkedDB* database;
public:
    Admin();
    ~Admin();
    void insertUser(User*);
    void removeUser(const Username&);
    User* findUser(const Username& );
    void save();
};

#endif // ADMIN

