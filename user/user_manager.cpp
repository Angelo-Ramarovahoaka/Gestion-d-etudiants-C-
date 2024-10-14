#include <iostream>
#include <cstdlib>
#include "UserManager.hpp"
using namespace std;

int main() {
    std::cout << "Content-type: text/html\n\n";

    std::string query = std::getenv("QUERY_STRING");
    if (query.empty()) {
        std::cerr << "<p>Aucun paramètre fourni.</p>\n";
        std::cout << "<a href='./inscription.html'>Retour</a>" << std::endl;
        return 1;
    }

    std::string action;
    std::string username;
    std::string password;
    std::string sessionFile;
        

    size_t pos = query.find("action=");
    if (pos != std::string::npos) {
        action = query.substr(pos + 7, query.find('&', pos) - (pos + 7));
    }

    pos = query.find("username=");
    if (pos != std::string::npos) {
        username = query.substr(pos + 9, query.find('&', pos) - (pos + 9));
    }

    pos = query.find("password=");
    if (pos != std::string::npos) {
        password = query.substr(pos + 9, query.find('&', pos) - (pos + 9));
    }

    pos = query.find("sessionFile=");
    if(pos != string::npos) {
        sessionFile = query.substr(pos +12, query.find('&', pos) - (pos + 12));
    }

    UserManager userManager;
    userManager.setSessionFile(username,password);

    if (action == "inscription" && !username.empty() && !password.empty()) {
        userManager.inscription(username,password);
    } else if (action == "connexion") {
        userManager.connexion(username, password);
    } else if (action == "logout") {
        userManager.destroySession(username,password,sessionFile);
        // cout << userManager.getSessionFile() << "ito ge";
    }else {
        std::cerr << "<p>Action ou paramètres non valides.</p>\n";
    }
    return 0;
}
