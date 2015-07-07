#include"linkednet.h"
#include<QString>

/*#include <iostream>
#include <QTextStream>*/

LinkedNet::~LinkedNet() {
    net.clear();
}

LinkedNet* LinkedNet::clone() const {
    return new LinkedNet(*this);
}

int LinkedNet::size() const {
    return net.size();
}

void LinkedNet::addUser(User* u){
    if(!isInNet(u->account()->username())){
        net.push_back(SmartUser(u));
    }
    else throw MyExc(duplicate, "Friend is already in your personal Net");
}

void LinkedNet::removeUser(const Username& u){
    bool found = false;
    QString s = QString::fromUtf8(u.getLogin().c_str());
//QTextStream(stdout)<<"you are searching for "<<s<<"\n";
    for(std::list<SmartUser>::iterator it = net.begin(); it != net.end() && !found; ++it){
        s = QString::fromUtf8((*it)->account()->username().getLogin().c_str());
//QTextStream(stdout)<<s<<"\n";
        if(((*it)->account()->username().getLogin()) == (u.getLogin())) {
            found = true;
            net.erase(it);
//QTextStream(stdout)<<"found "<<s<<" and removed from friends! \n";
        }
    }
    if(!found) throw MyExc(userNotFound, "Connection not found");
}

std::list<SmartUser> LinkedNet::getUsers() const{
    return net ;
}
bool LinkedNet::isInNet(const Username& us) const{
    for(std::list<SmartUser>::const_iterator it = net.begin(); it != net.end(); ++it){
        if((*it)->account()->username() == us)
            return true;
    }
    return false;
}

std::list<SmartUser>::const_iterator LinkedNet::begin() const {
    return net.begin();
}
std::list<SmartUser>::const_iterator LinkedNet::end() const {
    return net.end();
}
