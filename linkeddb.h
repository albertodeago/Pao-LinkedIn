#ifndef LINKEDDB
#define LINKEDDB

#include <QFile>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QString>
#include <QTextStream>
#include "realuser.h"
#include "myexc.h"

class LinkedDB{
private:
    std::list<SmartUser> users;

public:
    LinkedDB();
    ~LinkedDB();
    void addUser(User*);
    void removeUser(const Username&);
    void load();
    void save() const;
    User* find(const Username &) const;
    int size() const;
    std::list<SmartUser> getUsersDB()const;
    bool isValidCredentials(const Username &) const;
    Username getAdmin() const;

    std::list<SmartUser>::const_iterator begin() const;
    std::list<SmartUser>::const_iterator end() const;
};

#endif // LINKEDDB

