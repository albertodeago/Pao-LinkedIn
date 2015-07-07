#ifndef MYEXC
#define MYEXC

#include <string>

enum excType{date , username, database, userNotFound, duplicate};

class MyExc {
private:
    excType type;
    std::string msg;
public:
    MyExc(excType t, const string& m = "") : type(t), msg(m) {}
    excType Type() const {
        return type;
    }
    std::string errorMsg() const {
        return msg;
    }
};
#endif // MYEXC

