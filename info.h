#ifndef INFO
#define INFO

#include<string>
#include<list>
#include"experience.h"
#include"myexc.h"

class Info{
private:
    std::string name, surname, email, address, tel;
    std::list<string> languages, skills, interests;
    std::list<Experience> experiences;
    QDate birth;
public:
    Info(const QDate&, const std::string& ="", const std::string& ="", const std::string& ="", const std::string& ="", const std::string& ="");
    Info(const Info&);
    ~Info();
    Info* clone() const;
    Info& operator=(const Info&);

    std::map<std::string,std::string> getAllInfo() const;
    QDate getBirthday()const;
    std::list<string> getLanguages() const;
    std::list<string> getSkills() const;
    std::list<string> getInterests() const;
    std::list<Experience> getExperiences() const;
    std::string getName() const;
    std::string getSurname() const;
    std::string getEmail() const;
    std::string getAddress() const;
    std::string getTel() const;

    void setName(const string&);
    void setSurname(const string&);
    void setBirthdate(const QDate&) throw(MyExc);
    void setEmail(const string&);
    void setAddress(const string&);
    void setTel(const string&);
    bool addLanguage(const string&);
    void removeLanguage(const string&);
    bool addSkill(const string&);
    void removeSkill(const string&);
    bool addInterest(const string&);
    void removeInterest(const string&);
    bool addExperience(const Experience&);
    void removeExperience(const Experience&);
    int age() const;
};
#endif // INFO

