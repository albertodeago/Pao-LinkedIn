#include"admin.h"

Admin::Admin(){ database = new LinkedDB();}

Admin::~Admin() { delete database; }

void Admin::insertUser(User* usr){
    database->addUser(usr);
    save();
}

void Admin::removeUser(const Username& usr){
    database->removeUser(usr);
}

User* Admin::findUser(const Username& usr){
    return database->find(usr);
}
void Admin::save(){
    database->save();
}
