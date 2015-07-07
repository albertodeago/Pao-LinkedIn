#include"realuser.h"
#include"linkeddb.h"

/* BASIC */
BasicUser::BasicUser(Account* a): User(a) {}

BasicUser::BasicUser(const BasicUser& b_u): User(b_u) {}

BasicUser& BasicUser::operator=(const BasicUser& b_u){
    if(this != &b_u){
        this->User::operator =(b_u);
    }
    return *this;
}
User* BasicUser::clone() const{
    return new BasicUser(*this);
}
std::list<User*> BasicUser::userSearch(const LinkedDB& db, const std::string& s) const{
    std::list<User*> temp;
    searchFunctor sf(0,s,this);

    for(std::list<SmartUser>::const_iterator it = db.begin(); it != db.end(); ++it) {
        sf(*it);
    }
    return sf.result();
}


/* BUSINESS */
BusinessUser::BusinessUser(Account* ac) : BasicUser(ac) {}

BusinessUser::BusinessUser(const BusinessUser& b_u) : BasicUser(b_u) {}

/* da fare se si aggiunge qualcosa
BusinessUser::~BusinessUser() {

}*/

BusinessUser& BusinessUser::operator=(const BusinessUser& b_u) {
    if(this != &b_u) {
       this->BasicUser::operator=(b_u);
    }
    return *this;
}

User* BusinessUser::clone() const {
    return new BusinessUser(*this);
}
std::list<User*> BusinessUser::userSearch(const LinkedDB& db, const std::string& s) const{
    std::list<User*> temp;
    searchFunctor sf(1,s,this);

    for(std::list<SmartUser>::const_iterator it = db.begin(); it != db.end(); ++it) {
        sf(*it);
    }
    return sf.result();
}


/* EXECUTIVE */
ExecutiveUser::ExecutiveUser(Account* ac) : BusinessUser(ac) {}

ExecutiveUser::ExecutiveUser(const ExecutiveUser& e_u) : BusinessUser(e_u) {}

/*da fare se si aggiunge
ExecutiveUser::~ExecutiveUser() {}*/

ExecutiveUser& ExecutiveUser::operator=(const ExecutiveUser& e_u) {
    if(this != &e_u) {
        this->BusinessUser::operator=(e_u);
    }
    return *this;
}

User* ExecutiveUser::clone() const {
    return new ExecutiveUser(*this);
}
std::list<User*> ExecutiveUser::userSearch(const LinkedDB& db, const std::string& s) const{
    std::list<User*> temp;
    searchFunctor sf(2,s,this);

    for(std::list<SmartUser>::const_iterator it = db.begin(); it != db.end(); ++it) {
        sf(*it);
    }
    return sf.result();
}
