#ifndef LINKEDNET
#define LINKEDNET

#include"user.h"
#include <list>

class SmartUser;
class User;

class LinkedNet {
private:
    std::list<SmartUser> net;
public:
    ~LinkedNet();
    LinkedNet* clone() const;
    void addUser(User*); //throw(MyExc);
    void removeUser(const Username&); //throw(MyExc);
    int size() const;
    bool isInNet(const Username&) const;
    std::list<SmartUser> getUsers() const;
    std::list<SmartUser>::const_iterator begin() const;
    std::list<SmartUser>::const_iterator end() const;
};

#endif // LINKEDNET

