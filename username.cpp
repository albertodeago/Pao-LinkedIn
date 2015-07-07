#include "username.h"

Username::Username(const std::string& log, const std::string& pass) : login(log), password(pass) {}

const std::string& Username::getLogin() const {
    return login;
}

const std::string& Username::getPassword() const {
    return password;
}

void Username::setLogin(const std::string& log) {
    login = log;
}

void Username::setPassword(const std::string& pass) {
    password = pass;
}

bool Username::operator==(const Username& usr) const {
    return ((usr.login == login));// && (usr.password == password));
}

bool Username::operator!=(const Username& usr) const {
    return ((usr.login != login));// || (usr.password != password));
}
