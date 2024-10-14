#ifndef USERMANAGER_HPP
#define USERMANAGER_HPP

#include <string>
#include <iostream>
using namespace std;

class UserManager {
public:
    UserManager(){};
    void inscription(const string& username, const string& password);
    void connexion(const string& username, const string& password);
    void connexionError(const string& username, const string& password);
    void inscriptionError(const string& username, const string& password);
    void destroySession(const string& username, const string& password, const string& sessionFile);
    bool isSessionValid() const;
    void setSession();
    string getSessionFile();
    void setSessionFile(const string& username, const string& password);

private:
    string sessionFile ,username,password;
};

#endif // USERMANAGER_HPP
