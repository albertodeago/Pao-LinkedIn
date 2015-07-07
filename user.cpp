#include"user.h"
#include"iostream"

User::User(Account* account): acc(account->clone()), net(new LinkedNet()){}

User::User(const User& us): acc(us.acc->clone()), net(us.net->clone()) {}

User::~User(){
    delete acc;
    delete net;
}

User& User::operator=(const User& us){
    if(this!= &us){
        delete acc;
        delete net;
        acc = us.acc->clone();
        net = us.net->clone();
    }
    return *this;
}

Account* User::account() const{
    return acc;
}

LinkedNet* User::getNet() const{
    return net;
}
void User::addFriend(User* u){
    net->addUser(u);
}

void User::removeFriend(const Username& u){
    net->removeUser(u);
}

//searchFunctor part
User::searchFunctor::searchFunctor(int a = 0, const string& s = "", const User* call = 0) : aType(a), toSearch(s), caller(call) {
}

void User::searchFunctor::operator()(const SmartUser& us) {
    std::transform(toSearch.begin(), toSearch.end(), toSearch.begin(), ::tolower);
    std::string _name    = us->account()->getInfo()->getName();
    std::transform(_name.begin(), _name.end(), _name.begin(), ::tolower);
    std::string _surname = us->account()->getInfo()->getSurname();
    std::transform(_surname.begin(), _surname.end(), _surname.begin(), ::tolower);
    switch(aType){
        case 0:     //Basic user can just search for names and surnames and have max 10 results
            if(_name == toSearch || _surname == toSearch){
                //check to filter people that are already friend || me
                if(!(caller->getNet()->isInNet(us->account()->username())) && caller->account()->username()!=us->account()->username())
                    if(_result.size()<10)
                        _result.push_back(us.operator ->());
            }
        break;
        case 1:     //Business user can search for name, username or even skills and have max 50 results
            if(_name == toSearch || _surname == toSearch){
                //check to filter people that are already friend || me
                if(!(caller->getNet()->isInNet(us->account()->username())) && caller->account()->username()!=us->account()->username())
                    if(_result.size()<50)
                        _result.push_back(us.operator ->());
            }
            else{
                std::list<std::string> skillList = us->account()->getInfo()->getSkills();
                for(std::list<std::string>::const_iterator it = skillList.begin(); it != skillList.end(); ++it)
                    if(*it == toSearch)
                        //controllo che non sia io o un mio amico
                        if(!(caller->getNet()->isInNet(us->account()->username())) && caller->account()->username() != us->account()->username())
                            if(_result.size()<50)
                                _result.push_back(us.operator ->());
            }
        break;
        case 2:     //Executive user have the same permission of a Business user in terms of searching, but have no cap on results
                    //also he got results if the searched word is 'contained' in the name or surname (i.e. teo contained in matteo)
                    //if(_name == toSearch || _surname == toSearch){
                    if(QString::fromStdString(_name).contains(QString::fromStdString(toSearch)) || QString::fromStdString(_surname).contains(QString::fromStdString(toSearch))){
                        //check to filter people that are already friend || me
                        if(!(caller->getNet()->isInNet(us->account()->username())) && caller->account()->username()!=us->account()->username())
                            _result.push_back(us.operator ->());
                    }
                    else{
                        std::list<std::string> skillList = us->account()->getInfo()->getSkills();
                        for(std::list<std::string>::const_iterator it = skillList.begin(); it != skillList.end(); ++it)
                            if(*it == toSearch)
                                //controllo che non sia io o un mio amico
                                if(!(caller->getNet()->isInNet(us->account()->username())) && caller->account()->username() != us->account()->username())
                                    _result.push_back(us.operator ->());
                    }
        break;
    }
}

std::list<User*> User::searchFunctor::result() const {
    return _result;
}
