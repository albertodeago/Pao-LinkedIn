#include"experience.h"
#include"myexc.h"

Experience::Experience(const string& l, const string& r, const QDate& f, const QDate& t):
    loc(l), role(r){
    if(f<t){
        from=f;
        to=t;
    }
    else
        throw MyExc(date,"invalid dates!");
}
bool Experience::operator==(const Experience& e) const{
    return (loc==(e.loc) && role==e.role && from==e.from && to==e.to);
}

string Experience::getLocation() const{
    return loc;
}
void Experience::setLocation(const string& l){
    loc = l;
}
string Experience::getRole() const{
    return role;
}
void Experience::setRole(const string& r){
    role = r;
}
QDate Experience::getFrom() const{
    return from;
}
void Experience::setFrom(const QDate& f){
    from = f;
}
QDate Experience::getTo() const{
    return to;
}
void Experience::setTo(const QDate& t){
    to=t;
}
