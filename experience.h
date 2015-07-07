#ifndef EXPERIENCE
#define EXPERIENCE

#include <string>
#include <QDate>

using std::string;

class Experience {
private:
    string loc, role;
    QDate from, to;
public:
    Experience(const string& ="", const string& ="", const QDate& = QDate::currentDate(), const QDate& = QDate::currentDate());
    bool operator==(const Experience&) const;
    string getLocation() const;
    void setLocation(const string&);
    string getRole() const;
    void setRole(const string&);
    QDate getFrom() const;
    void setFrom(const QDate&);
    QDate getTo() const;
    void setTo(const QDate&);
};

#endif // EXPERIENCE

