#ifndef USERNAME
#define USERNAME

#include<string>

class Username {
private:
    std::string login;
    std::string password;
public:
    Username(const std::string& = "", const std::string& = "");
    const std::string& getLogin() const;
    void setLogin(const std::string&);
    const std::string& getPassword() const;
    void setPassword(const std::string&);
    bool operator==(const Username&) const;
    bool operator!=(const Username&) const;
};

#endif // USERNAME

