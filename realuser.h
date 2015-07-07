#ifndef REALUSER
#define REALUSER

#include"user.h"

class BasicUser : public User {
public:
    BasicUser(Account *);
    BasicUser(const BasicUser&);
    BasicUser& operator=(const BasicUser&);
    virtual User* clone() const;
    virtual std::list<User*> userSearch(const LinkedDB&, const std::string& ) const;
};


class BusinessUser : public BasicUser {
public:
    BusinessUser(Account*);
    BusinessUser(const BusinessUser&);
    BusinessUser& operator=(const BusinessUser&);
    //virtual ~BusinessUser();
    virtual User* clone() const;
    virtual std::list<User*> userSearch(const LinkedDB&, const std::string& ) const;
};


class ExecutiveUser : public BusinessUser {
public:
    ExecutiveUser(Account*);
    ExecutiveUser(const ExecutiveUser&);
    ExecutiveUser& operator=(const ExecutiveUser&);
   // virtual ~ExecutiveUser();
    virtual User* clone() const;
    virtual std::list<User*> userSearch(const LinkedDB&, const std::string& ) const;
};

#endif // REALUSER

