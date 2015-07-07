#ifndef USER
#define USER

#include"smartuser.h"
#include"account.h"
#include"linkednet.h"

class LinkedNet;
class LinkedDB;

class User{
private:
    Account* acc;
    LinkedNet* net;
protected:
    class searchFunctor {
    private:
        int aType;
        std::string toSearch;
        const User* caller;
        std::list<User*> _result;
    public:
        searchFunctor(int, const string&, const User*);
        void operator()(const SmartUser&);
        std::list<User*> result() const;
    };
public:
    User(Account*);
    User(const User&);
    User& operator=(const User&);
    virtual ~User();
    virtual User* clone() const =0;
    Account* account() const;
    LinkedNet* getNet() const;
    void addFriend(User*);
    void removeFriend(const Username&);
    virtual std::list<User*> userSearch(const LinkedDB&, const std::string& ) const=0;
};
#endif // USER

