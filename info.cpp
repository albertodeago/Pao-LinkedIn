#include"info.h"

Info::Info(const QDate& d, const std::string& n, const std::string& s, const std::string& e, const std::string& a, const std::string& t):
    name(n),surname(s),email(e),address(a),tel(t){
    if(d > QDate::currentDate())
        throw MyExc(date, "Invalid date, you can't be unborn!");
    else
        birth = d;
}

Info::Info(const Info& i):
    name(i.name),surname(i.surname),email(i.email),address(i.address),tel(i.tel),birth(i.birth),skills(i.skills),interests(i.interests),languages(i.languages),experiences(i.experiences)
{
}

Info::~Info(){
    skills.clear();
    interests.clear();
    languages.clear();

    experiences.clear();
}

Info* Info::clone() const{
    return new Info(*this);
}
Info& Info::operator=(const Info& i ){
    if(this != &i) {
        name = i.name;
        surname = i.surname;
        address = i.address;
        email = i.email;
        tel = i.tel;
        birth = i.birth;
        languages = i.languages;
        skills = i.skills;
        interests = i.interests;
        experiences = i.experiences;
    }
    return *this;
}

void Info::setName(const string& n){name = n;}
void Info::setSurname(const string& s){surname=s;}
void Info::setBirthdate(const QDate& d) throw(MyExc){
    if(d>QDate::currentDate())
        throw MyExc(date, "Invalid date, you can't be unborn!");
    else
        birth = d;
}
void Info::setEmail(const string& e){email=e;}
void Info::setAddress(const string& a){address=a;}
void Info::setTel(const string& t){tel=t;}


bool Info::addLanguage(const string& l){
    bool isIn = false;
    for(std::list<string>::iterator it = languages.begin(); it!= languages.end() && !isIn ;++it){
        if(*it == l){
            isIn=true;
        }
    }
    if(!isIn)   {languages.push_back(l); return true;}
    return false ;
}
void Info::removeLanguage(const string& l){
    languages.remove(l);
}


bool Info::addSkill(const string& s){
    bool isIn = false;
    for(std::list<string>::iterator it = skills.begin(); it!= skills.end() && !isIn;++it){
        if(*it == s){
            isIn=true;
        }
    }
    if(!isIn)   {skills.push_back(s);return true;}
    return false;
}
void Info::removeSkill(const string& s){
    skills.remove(s);
}


bool Info::addInterest(const string& i){
    bool isIn = false;
    for(std::list<string>::iterator it = interests.begin(); it!= interests.end() && !isIn ;++it){
        if(*it == i){
            isIn=true;
        }
    }
    if(!isIn)   {interests.push_back(i); return true;}
    return false ;
}
void Info::removeInterest(const string& i){
    interests.remove(i);
}


bool Info::addExperience(const Experience& e){
    experiences.push_back(e);
    return true;
}
void Info::removeExperience(const Experience& e){
    bool found = false;
    for(std::list<Experience>::iterator it = experiences.begin(); it != experiences.end() && !found; ++it)
        if(*it == e) {
            experiences.erase(it);
            found = true;
        }
}

int Info::age() const{
    return ((QDate::currentDate().toJulianDay() - birth.toJulianDay())/365);
}

std::map<std::string , std::string> Info::getAllInfo() const{
    std::map<std::string,std::string> ret;
    if(name!="")
        ret["name"]= name;
    if(surname!="")
        ret["surname"]= surname;
    if(email!="")
        ret["email"]= email;
    if(address!="")
        ret["address"]= address;
    if(tel!="")
        ret["telephon"]= tel;
    return ret;
}

QDate Info::getBirthday() const{
    return birth;
}
std::list<string> Info::getLanguages() const{
    return languages;
}
std::list<string> Info::getSkills() const{
    return skills;
}
std::list<string> Info::getInterests() const{
    return interests;
}
std::list<Experience> Info::getExperiences() const{
    return experiences;
}
std::string Info::getName() const{return name;}
std::string Info::getSurname() const{return surname;}
std::string Info::getEmail() const{return email;}
std::string Info::getAddress() const{return address;}
std::string Info::getTel() const{return tel;}
