#ifndef SMARTUSER
#define SMARTUSER

#include"user.h"

class User;

class SmartUser {
private:
    User* ptr;
public:
    SmartUser();
    SmartUser(User*);
    SmartUser(const SmartUser&);
    ~SmartUser();
    SmartUser& operator=(const SmartUser&);
    User& operator*() const;
    User* operator->() const;
    bool operator==(const SmartUser&) const;
    bool operator!=(const SmartUser&) const;
};

#endif // SMARTUSER

