#include "UserManager.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;

void UserManager::inscription(const string& username, const string& password) {
    ofstream file("users.txt", ios::app);
    ifstream verifyFile("users.txt");
    string line;
    bool exists = false;
    while (getline(verifyFile, line)) {
        string name, word;
        stringstream ss(line);
        getline(ss, name, ',');
        getline(ss, word, ',');

        if (name == username) {
            exists = true;
            break;
        }
    }
    
    if (!exists) {
        file << username << "," << password << endl;
        file.close();
        std::cout << "<meta http-equiv='refresh' content='0;url=http://www.site1.mg/index.html'>" << std::endl;
    } else {
        cout << "le nom d'utilisateur est déja utilisée";
        inscriptionError(username,password);
    }
    file.close();
    verifyFile.close();
}

void UserManager::connexion(const string& username, const string& password) {
    ifstream file("./users.txt");
    string line;
    bool errorconnexion=true ;
    
    while (getline(file, line)) {
        stringstream ss(line);
        string storedUsername, storedPassword;
        getline(ss, storedUsername, ',');
        getline(ss, storedPassword);
        if (storedUsername == username && storedPassword == password) {
            errorconnexion = false;
            break;
        }

    }
        file.close();
    if(errorconnexion){
        cout << " erreur mot de passe ou nom d'utlisateur " << endl;
        connexionError(username,password);
    }
    
    if (!isSessionValid()) {
        cout << "iroron" << endl;
        setSession();  // Crée la session uniquement si elle n'existe pas déjà      
    } else {
            std::cout << "<meta http-equiv='refresh' content='0;url=http://www.site1.mg/student/student_manager.cgi?action=student&sessionFile=" << sessionFile << "'>" << std::endl;
    }
    // isSessionValid();
 
}

void UserManager::connexionError(const string& username, const string& password){
    cout << "<!DOCTYPE html>"; 
    cout << "<html><head><title>Gestion des Utilisateurs</title></head>";
    cout << "<body><h1>Gestion des Utilisateurs</h1><form action='./user_manager.cgi'  method='get'><input type='hidden' name='action' value='connexion'><label for='username'>Nom d'utilisateur:</label>";
    cout << "<input type='text' id='username' name='username' value='" << username << "' required><br><br><label for='password'>Mot de passe:</label><input type='password' id='assword' name='password' value='" << password << "' required><br><br>";   

    cout << "<input type='submit' value='connexion'></form><a href='./inscription.html'>inscription</a></body></html>";
}
void UserManager::inscriptionError(const string& username, const string& password){
   cout << R"( <!DOCTYPE html>
    <html lang="fr">

    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <title>Gestion des Utilisateurs</title>
        <!-- <script src="https://cdn.tailwindcss.com"></script> -->
    </head>

    <body class="flex flex-col items-center justify-center min-h-screen bg-gray-100">
        <h1 class="text-3xl font-bold mb-8 text-red-600">MISA</h1>

        <button class="mb-4 bg-blue-500 hover:bg-blue-700 text-white font-bold py-2 px-4 rounded focus:outline-none focus:shadow-outline">
            <a href="../index.html">Connexion</a>
        </button>

        <form action="./user_manager.cgi" method="get" class="bg-white shadow-md rounded px-8 pt-6 pb-8 w-full max-w-xs">
            <input type="hidden" name="action" value="inscription">

            <div class="mb-4">
                <label for="username" class="block text-gray-700 text-sm font-bold mb-2">Nom d'utilisateur :</label>
                <input type="text" id="username" value=")" << username << R"(" name="username" required
                    class="shadow appearance-none border rounded w-full py-2 px-3 text-gray-700 leading-tight focus:outline-none focus:shadow-outline">
            </div>

            <div class="mb-6">
                <label for="password" class="block text-gray-700 text-sm font-bold mb-2">Mot de passe :</label>
                <input type="password" id="password" value=")" << password << R"(" name="password"
                    class="shadow appearance-none border rounded w-full py-2 px-3 text-gray-700 mb-3 leading-tight focus:outline-none focus:shadow-outline">
            </div>

            <input type="submit" value="Inscription"
                class="bg-red-500 hover:bg-red-700 text-white font-bold py-2 px-4 rounded focus:outline-none focus:shadow-outline w-full">
        </form>
    </body>

    </html>)";
}
void UserManager::setSessionFile(const string& username, const string& password){
    sessionFile = username + password + ".txt";
    // cout << sessionFile;
}
string UserManager::getSessionFile(){
    return this->sessionFile;
}
void UserManager::destroySession(const string& username, const string& password, const string& sessionFile) {
    cout << "itods";
    // cout << username << password << endl;
    cout << sessionFile << "rtrt";
    string file = string ("../sessionFile/") + sessionFile;
    if(remove(file.c_str())){
        // std::cout << "<p>Déconnexion réussie.</p>\n";
        std::cout << "<meta http-equiv='refresh' content='0;url=http://www.site1.mg/../index.html'>" << std::endl;
    }
    else {
        std::cerr << "Erreur lors de la suppression du fichier." << std::endl;
    }
    
    // std::cout << "<meta http-equiv='refresh' content='0;url=http://www.site1.mg/../index.html'>" << std::endl;
}

bool  UserManager::isSessionValid() const {
    cout << sessionFile ;
    // Vérifier si une session valide existe
    std::ifstream file("../sessionFile/" + sessionFile);
    if (file.is_open()) {
        return true;
    } else {
        return false;
    }
}

void UserManager::setSession() {
    std::ofstream file( "../sessionFile/" + sessionFile );
    // cout << sessionFile << endl;
    cout << getSessionFile() << endl;
    std::cout << "<meta http-equiv='refresh' content='0;url=http://www.site1.mg/student/student_manager.cgi?action=student&sessionFile=" << sessionFile << "'>" << std::endl;
    // file << username << std::endl;
    file.close();
}
