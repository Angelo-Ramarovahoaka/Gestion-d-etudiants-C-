#include "StudentManager.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <sys/stat.h> //Pour la fonction chmod 
#include <algorithm>
#include <regex>

using namespace std;

bool StudentManager::validateEmail(const std::string& email){
    std::regex emailPattern(R"(^[a-zA-Z0-9._%+-]+@gmail\.com$)");
    return std::regex_match(email, emailPattern);
}

bool StudentManager::validatePhoneNumber(const std::string& numberTel){
    std::regex phonePattern(R"(^\d{9}$)");
    return std::regex_match(numberTel, phonePattern);
}

void StudentManager::addStudent(const string& firstname, const string& lastname, int age, const string& email, const string& adresse, const string& numberTel, const string& classe, const string& numberCard) {
    ofstream file("students.txt", ios::app);
    ifstream verifyFile("students.txt");
    string line;
    bool exists = false;
    while (getline(verifyFile, line)) {
        string first, last, ageStr, email1, adresse1, numberTel1, classe1, numberCard1;
        stringstream ss(line);
        getline(ss, first, ',');
        getline(ss, last, ',');
        getline(ss, ageStr, ',');
        getline(ss, email1, ',');
        getline(ss, adresse1, ',');
        getline(ss, numberTel1, ',');
        getline(ss, classe1, ',');
        getline(ss, numberCard1, ',');

        if (first == firstname && last == lastname) {
            cout << "Nom et prénom déjà existants" << endl;
            exists = true;
            break;
        }

        if (email == email1 || numberCard == numberCard1) {
            cout << "Email ou numéro de carte déjà utilisé" << endl;
            exists = true;
            break;
        }

    }

    if (!exists) {
        if (!validateEmail(email)) {
            std::cout << "Email invalide ! Doit se terminer par @gmail.com" << std::endl;
            formInscription(firstname, lastname, age, email, adresse, numberTel, classe, numberCard);
        }

        if (!validatePhoneNumber(numberTel)) {
            std::cout << "Numéro de téléphone invalide ! Doit comporter 9 chiffres" << std::endl;
            formInscription(firstname, lastname, age, email, adresse, numberTel, classe, numberCard);
        }
        
        file << firstname << "," << lastname << "," << age << "," << email << "," << adresse << ",";
        file << numberTel << "," << classe << "," << numberCard << endl;
        file.close();
        std::cout << "<meta http-equiv='refresh' content='0;url=http://www.site1.mg/student/student_manager.cgi?action=view'>" << std::endl;
    } else {
        formInscription(firstname, lastname, age, email, adresse, numberTel, classe, numberCard);
    }
    file.close();
    verifyFile.close();
}

void StudentManager::formInscription(const string& firstname , const string& lastname, int age, const string& email, const string& adresse, const string& numberTel, const string& classe, const string& numberCard) const{
    cout << R"(<!DOCTYPE html>
<html lang="fr">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Modifier un étudiant</title>
</head>
<body>
    <h1>Modifier un étudiant</h1>
    <form action="student_manager.cgi" method="get" >
        <input type="hidden" name="action" value="create">

        <label for="name">lastname:</label>
        <input type="text" id="lastname" name="lastname" value=")" << lastname << R"(" required><br><br>
        
        <label for="prenom">firstname:</label>
        <input type="text" id="firstname" name="firstname" value=")" << firstname << R"(" required><br><br>
        
        <label for="age">age:</label>
        <input type="number" id="age" name="age" value=")" << age << R"(" required><br><br>

        <label for="email">Email:</label>
        <input type="email" id="email" name="email" value=")" << email << R"(" required><br><br>

        
        <label for="Adresse">Adresse:</label>
        <input type="text" id="adresse" name="adresse" value=")" << adresse << R"(" required><br><br>

        <label for="number">tel:</label>
        <input type="text" id="numberTel" name="numberTel" value=")" << numberTel << R"(" required><br><br>

        <label for="classe">Class:</label>
        <input type="text" id="classe" name="classe" value=")" << classe << R"(" required><br><br>

        <label for="numberCard">Numéros de carte:</label>
        <input type="text" id="numberCard" name="numberCard" value=")" << numberCard << R"(" required><br><br>
        <input type="submit" value="Envoyer">
    </form>)";
cout << "</body>";
cout << "</html>";
}
void StudentManager::displayStudents() const {
    std::ifstream file("./students.txt");
    if (!file)
    {
        std::cout << "<p>Erreur lors de l'ouverture du fichier data.txt.</p>\n";
    }
    else
    {
        std::cout << "<table border='1'>\n";
        int id = 1;

        std::string line;
        while (std::getline(file, line))
        {
            std::cout << "<tr>";
            size_t start = 0, end = 0;

            for (size_t i = 0; i < 2; i++)
            {
                end = line.find(',', start);
                {
                    std::cout << "<td>" << line.substr(start, end - start) << "</td>";
                    start = end + 1;
                }
            }
            std::cout << "<td> <a href=\"./student_manager.cgi?action=detail&id=" << id << "\"" << ">Detail</a> </td>" << std::endl;
            std::cout << "<td> <a href=\"./student_manager.cgi?action=modify&id=" << id << "\"" << ">Modify</a> </td>" << std::endl;
            std::cout << "<td> <a href=\"./student_manager.cgi?action=delete&id=" << id << "\"" << ">Delete</a> </td>" << std::endl;

            id += 1;

            std::cout << "</tr>\n";
        }
        std::cout << "</table>\n";
        file.close();
    }

    std::cout << "<a href='./student_form.html'>s'inscrire</a>" << std::endl;
    std::cout << "</body>\n</html>\n";
}

void StudentManager::deleteStudent(int id) const {
    std::ifstream dataFile("./students.txt");
    std::ofstream tempFile("./temp.txt");

    if ( !dataFile.is_open() || !tempFile.is_open()) {
        std::cout << "<p>Erreur lors de l'ouverture du fichier.</p>\n";
    } 
    else {
        std::string line;
        int current_id = 1;
        while (std::getline(dataFile, line)) {
            if (current_id != id) {
                tempFile << line << "\n";
            }
            current_id++;
        }
        dataFile.close();
        tempFile.close();

        // Remplacer l'ancien fichier par le nouveau
        std::remove("./data.txt");
        std::rename("./temp.txt", "./students.txt");

        cout << "<meta http-equiv='refresh' content='0;url=http://www.site1.mg/student/student_manager.cgi?action=view' >" << std::endl;
    }
}

void StudentManager::detailStudents( int id) {
    std::ifstream file("./students.txt");
    if (!file) {
        std::cout << "<p>Erreur lors de l'ouverture du fichier students.txt.</p>\n";
    } else {
        std::string line;
        int current_id = 1;
        while (std::getline(file, line)) {
            if (current_id == id) {
                stringstream ss(line);
                string firstname, lastname , ageStr, email, adresse,numberTel,classe,numberCard;
                getline(ss, firstname, ',');
                getline(ss, lastname, ',');
                getline(ss, ageStr);
                getline(ss, email, ',');
                getline(ss, adresse, ',');
                getline(ss, numberTel, ',');
                getline(ss, classe, ',');
                getline(ss, numberCard, ',');
                int age = std::stoi(ageStr);
                formDetail(firstname,lastname,age,email,adresse,numberTel,classe,numberCard);
                break;
            }
            current_id++;
        }
        file.close();
    }

    std::cout << "<a href='//www.site1.mg/student/student_manager.cgi?action=view'>Retour</a>" << std::endl;
}

void StudentManager::formDetail(const string& firstname , const string& lastname, int age, const string& email, const string& adresse, const string& numberTel, const string& classe, const string& numberCard)  const{
    cout << R"(
        <!DOCTYPE html>
<html lang="fr">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Liste des Utilisateurs</title>
    <script src="https://cdn.tailwindcss.com"></script>
</head>

<body class="bg-gray-100 p-10">
    <div class="container mx-auto">
        <h1 class="text-3xl font-bold text-center mb-8 text-red-600">Liste des Utilisateurs</h1>
        <table class="table-auto w-full bg-white shadow-md rounded">
            <thead>
                <tr class="bg-gray-200 text-gray-600 uppercase text-sm leading-normal">
                    <th class="py-3 px-6 text-left">Prénom</th>
                    <th class="py-3 px-6 text-left">Nom</th>
                    <th class="py-3 px-6 text-left">age</th>
                    <th class="py-3 px-6 text-left">Email</th>
                    <th class="py-3 px-6 text-left">Adresse</th>
                    <th class="py-3 px-6 text-left">Téléphone</th>
                    <th class="py-3 px-6 text-left">Classe</th>
                    <th class="py-3 px-6 text-left">Numéro de Carte</th>
                </tr>
            </thead>
            <tbody class="text-gray-700 text-sm">
                <tr class="border-b border-gray-200 hover:bg-gray-100">
                    <td class="py-3 px-6 text-left">)" << firstname << R"(</td>
                    <td class="py-3 px-6 text-left">)" << lastname << R"(</td>
                    <td class="py-3 px-6 text-left">)" << age << R"(</td>
                    <td class="py-3 px-6 text-left">)" << email << R"(</td>
                    <td class="py-3 px-6 text-left">)" << adresse << R"(</td>
                    <td class="py-3 px-6 text-left">)" << numberTel << R"(</td>
                    <td class="py-3 px-6 text-left">)" << classe << R"(</td>
                    <td class="py-3 px-6 text-left">)" << numberCard << R"(</td>
                </tr>
            </tbody>
        </table>
    </div>
</body>

</html>
)";
}

void StudentManager::formModify(const string& firstname , const string& lastname, int age, const string& email, const string& adresse, const string& numberTel, const string& classe, const string& numberCard, int id) const{
    cout << R"(<!DOCTYPE html>
<html lang="fr">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Modifier un étudiant</title>
</head>
<body>
    <h1>Modifier un étudiant</h1>
    <form action="student_manager.cgi" method="get" accept-charset="UTF-8">
        <input type="hidden" name="action" value="modify">

        <label for="name">lastname:</label>
        <input type="text" id="lastname" name="lastname" value=")" << lastname << R"(" required><br><br>
        
        <label for="prenom">firstname:</label>
        <input type="text" id="firstname" name="firstname" value=")" << firstname << R"(" required><br><br>
        
        <label for="age">age:</label>
        <input type="number" id="age" name="age" value=")" << age << R"(" required><br><br>

        <label for="email">Email:</label>
        <input type="email" id="email" name="email" value=")" << email << R"(" required><br><br>

        
        <label for="Adresse">Adresse:</label>
        <input type="text" id="adresse" name="adresse" value=")" << adresse << R"(" required><br><br>

        <label for="number">tel:</label>
        <input type="text" id="numberTel" name="numberTel" value=")" << numberTel << R"(" required><br><br>

        <label for="classe">Class:</label>
        <input type="text" id="classe" name="classe" value=")" << classe << R"(" required><br><br>

        <label for="numberCard">Numéros de carte:</label>
        <input type="text" id="numberCard" name="numberCard" value=")" << numberCard << R"(" required><br><br>

        <input type="hidden" id="id" name="id" value=")" << id <<  R"("required><br>
        <input type="submit" value="Modifier l'étudiant">
    </form>)";
    std::cout << "<a href='//www.site1.mg/student/student_manager.cgi?action=view'>Retour</a>" << std::endl;
cout << "</body>";
cout << "</html>";
}
void StudentManager::modifyStudent(int id) const {
    ifstream inputFile("./students.txt");
    ofstream tempFile("./temp.txt");
    chmod("temp.txt", 0777);
    string line;
    int currentId = 1;
    bool found = false;
    string firstname, lastname, email, adresse, numberTel, classe, numberCard;
    int age;

    while (getline(inputFile, line)) {
        stringstream ss(line);
        string first, last, ageStr, email1, adresse1, numberTel1, classe1, numberCard1;
        getline(ss, first, ',');
        getline(ss, last, ',');
        getline(ss, ageStr, ',');
        getline(ss, email1, ',');
        getline(ss, adresse1, ',');
        getline(ss, numberTel1, ',');
        getline(ss, classe1, ',');
        getline(ss, numberCard1, ',');

        if (currentId == id) {
            // Pré-remplir le formulaire avec les données actuelles
            firstname = first;
            lastname = last;
            age = std::stoi(ageStr);  // Convertir ageStr en int
            email = email1;
            adresse = adresse1;
            numberTel = numberTel1;
            classe = classe1;
            numberCard = numberCard1;

            found = true;
            break;
        }
        currentId++;
    }

    inputFile.close();

    if (found) {
        // Afficher le formulaire pour modifier les informations
        formModify(firstname, lastname, age, email, adresse, numberTel, classe, numberCard, id);
    } else {
        cout << "<p>Étudiant non trouvé.</p>";
    }
}



void StudentManager::modifierLigne(const std::string& fileName, int id, const std::string& nouvelleLigne) {
    std::ifstream dataFile(fileName);
    std::ofstream tempFile("temp.txt");
    std::string line;
    string firstname, lastname, ageStr, email, adresse, numberTel, classe, numberCard;
    int currentId = 1;

    while (std::getline(dataFile, line)) {
        if (currentId == id) {
            // Remplacer la ligne de l'étudiant par la nouvelle ligne
            tempFile << nouvelleLigne << std::endl;
        } else {
            // Réécrire la ligne telle quelle
            tempFile << line << std::endl;
        }
        currentId++;
    }

    dataFile.close();
    tempFile.close();
    chmod("temp.txt", 0777);
    chmod(fileName.c_str(), 0777);

    // Remplacer le fichier original par le fichier temporaire
    remove(fileName.c_str());
    rename("temp.txt", fileName.c_str());

    // Récupérer les nouvelles valeurs du formulaire
    stringstream ss(nouvelleLigne);
    getline(ss, firstname, ',');
    getline(ss, lastname, ',');
    getline(ss, ageStr, ',');  // ageStr est maintenant std::string
    getline(ss, email, ',');
    getline(ss, adresse, ',');
    getline(ss, numberTel, ',');
    getline(ss, classe, ',');
    getline(ss, numberCard, ',');

    // Convertir ageStr en int pour le formulaire
    int age = std::stoi(ageStr);

    // Afficher le formulaire pour modifier les informations
    formModify(firstname, lastname, age, email, adresse, numberTel, classe, numberCard, id);
}

string StudentManager::urlDecode(const string& str){
    string decoded;
    char ch;
    int i,ii;
    for(i=0;i<str.length();i++)
    {
        if(str[i]=='%')
        {
            sscanf(str.substr(i+1, 2).c_str(),"%x", &ii);
            ch = static_cast<char>(ii);
            decoded += ch;
            i += 2;
        } 
        else if (str[i] == '+')
        {
            decoded +=' ';
        }
        else
        {
            decoded +=str[i];
        }
    }
    return decoded;
}
void StudentManager::studentForm(const string& sessionFile) {
    cout << R"(<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Insertion</title>
</head>
<body>
    <header>
        <h4>Bienvenue</h4>
        <div>
            <a href="../user/user_manager.cgi?action=logout&sessionFile=)" << sessionFile << R"(">Deconnection?</a>
        </div>
    </header>
    <h2>Inscription</h2>
    <form action="./student_manager.cgi" method="get" accept-charset="UTF-8">
        <input type="hidden" name="action" value="create">

        <label for="name">lastname:</label>
        <input type="text" id="lastname" name="lastname" required><br><br>
        
        <label for="prenom">firstname:</label>
        <input type="text" id="firstname" name="firstname" required><br><br>
        
        <label for="age">age:</label>
        <input type="number" id="age" name="age" required><br><br>

        <label for="email">Email:</label>
        <input type="email" id="email" name="email" required><br><br>

        
        <label for="Adresse">Adresse:</label>
        <input type="text" id="adresse" name="adresse" required><br><br>

        <label for="number">tel:</label>
        <input type="text" id="numberTel" name="numberTel" required><br><br>

        <label for="classe">Class:</label>
        <input type="text" id="classe" name="classe" required><br><br>

        <label for="numberCard">Numéros de carte:</label>
        <input type="text" id="numberCard" name="numberCard" required><br><br>
        
        <input type="submit" value="Envoyer">
    </form>
    <a href="http://www.site1.mg/student/student_manager.cgi?action=view">Afficher la liste</a>
</body>
</html>)";
}
