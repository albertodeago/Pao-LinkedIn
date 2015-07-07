#include"smartuser.h"

SmartUser::SmartUser(): ptr(0) {}

SmartUser::SmartUser(User* u): ptr(u->clone()){}

SmartUser::SmartUser(const SmartUser& su): ptr( (su.ptr)->clone()){}

SmartUser::~SmartUser(){
    delete ptr;
}

SmartUser& SmartUser::operator=(const SmartUser& su){
    if(this != &su){
        delete ptr;
        ptr = (su.ptr)->clone();
    }
    return *this;
}

User& SmartUser::operator*() const{
    return *ptr;
}

User* SmartUser::operator->() const{
    return ptr;
}

bool SmartUser::operator==(const SmartUser& su) const{
    return (ptr == su.ptr);
}
bool SmartUser::operator!=(const SmartUser& su) const{
    return (ptr != su.ptr);
}
