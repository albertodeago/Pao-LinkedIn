#include"linkedclient.h"


LinkedClient::LinkedClient(const Username& u):database(new LinkedDB()){
    usr = database->find(u);
    if(usr == NULL || usr->account()->username() != u)
        throw MyExc(userNotFound,"user not found!");
}
LinkedClient::~LinkedClient(){
    delete database;
}
void LinkedClient::save(){
    database->save();
}

Username& LinkedClient::getUsername() const{
    return usr->account()->username();
}
Info* LinkedClient::getInfo() const{
    return usr->account()->getInfo();
}
LinkedNet* LinkedClient::getNet() const{
    return usr->getNet();
}
std::string LinkedClient::getAvatar() const{
    return usr->account()->getAvatar();
}
void LinkedClient::setAvatar(const std::string& path){
    usr->account()->setAvatar(path);
}
int LinkedClient::getAccType() const{
    return usr->account()->getType();
}
void LinkedClient::setAccType(accountType a){
    usr->account()->setType(a);
}
std::list<User*> LinkedClient::userSearch(const std::string& s) const{
    return usr->userSearch(*database, s);
}
User* LinkedClient::getUserFromUsername(const string& us) const{
    return database->find(Username(us));
}
