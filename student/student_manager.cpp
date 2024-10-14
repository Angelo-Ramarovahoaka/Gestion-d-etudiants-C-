#include <iostream>
#include <cstdlib>
#include "StudentManager.hpp"
#include "../user/UserManager.hpp"
#include <string>
using namespace std;
int main() {
    StudentManager studentManager;
    UserManager userManager;

    std::cout << "Content-type: text/html; charset=UTF-8\n\n";

    std::string query = std::getenv("QUERY_STRING");
if(userManager.isSessionValid()){
    if (query.empty()) {
        std::cerr << "<p>Aucun paramètre fourni.</p>\n";
        std::cout << "<a href='./student_form.html'>Retour</a>" << std::endl;
        return 1;
    }
    std::string action;
    string firstname, email, adresse, numberTel, classe,numberCard;
    string lastname;
    string TempAge;
    string tempId,sessionFile;
    
    int id, age;
    

    size_t pos = query.find("action=");
    if (pos != std::string::npos) {
        action = studentManager.urlDecode(query.substr(pos + 7, query.find('&', pos) - (pos + 7)));
    }

    pos = query.find("firstname=");
    if (pos != std::string::npos) {
        firstname = studentManager.urlDecode(query.substr(pos + 10, query.find('&', pos) - (pos + 10)));
    }

    pos = query.find("lastname=");
    if (pos != std::string::npos) {
        lastname = studentManager.urlDecode(query.substr(pos + 9, query.find('&', pos) - (pos + 9)));
    }

    pos = query.find("age=");
    if (pos != std::string::npos) {
        TempAge = studentManager.urlDecode(query.substr(pos + 4, query.find('&', pos) - (pos + 4)));
        age = stoi(TempAge);
    }

    pos = query.find("email=");
    if (pos != std::string::npos) {
        email = studentManager.urlDecode(query.substr(pos + 6, query.find('&', pos) - (pos + 6)));
    }

    pos = query.find("adresse=");
    if (pos != std::string::npos) {
        adresse = studentManager.urlDecode(query.substr(pos + 8, query.find('&', pos) - (pos + 8)));
    }

    pos = query.find("numberTel=");
    if (pos != std::string::npos) {
        numberTel = studentManager.urlDecode(query.substr(pos + 10, query.find('&', pos) - (pos + 10)));
    }

    pos = query.find("classe=");
    if (pos != std::string::npos) {
        classe = studentManager.urlDecode(query.substr(pos + 7, query.find('&', pos) - (pos + 7)));
    }

    pos = query.find("numberCard=");
    if (pos != std::string::npos) {
        numberCard = studentManager.urlDecode(query.substr(pos + 11, query.find('&', pos) - (pos + 11)));
    }

    pos = query.find("id=");
    if(pos != string::npos) {
        tempId = studentManager.urlDecode(query.substr(pos +3, query.find('&', pos) - (pos + 3)));
        id = stoi(tempId);
    }
    
    pos = query.find("sessionFile=");
    if(pos != string::npos) {
        sessionFile = studentManager.urlDecode(query.substr(pos +12, query.find('&', pos) - (pos + 12)));
    }
    if (action == "create" && !firstname.empty() && !lastname.empty() && !TempAge.empty()) {
        studentManager.addStudent(firstname,lastname,age,email,adresse,numberTel,classe,numberCard);
    }
    else if (action == "delete" ) {
        studentManager.deleteStudent(id);
    } 
    else if (action == "modify" && !firstname.empty() && !lastname.empty() && !TempAge.empty()) {
    std::string nouvelleLigne = firstname + "," + lastname + "," + std::to_string(age) + "," + email+ "," + adresse+ "," + numberTel+ "," + classe + "," + numberCard;
    studentManager.modifierLigne("students.txt", id, nouvelleLigne);
    }

    else if (action == "modify") {
        studentManager.modifyStudent(id);
    }

    else if (action == "view") {
        studentManager.displayStudents();
    }
    
    else if (action == "student") {
        studentManager.studentForm(sessionFile);
    }

    else if (action == "detail"){
        studentManager.detailStudents(id);
    } else {
        std::cerr << "<p>Action ou paramètres non valides.</p>\n";
    }
    }
    else {
        cout << "mety";
        // std::cout << "<meta http-equiv='refresh' content='0;url=http://www.site1.mg/../index.html'>" << std::endl;
    }
    
    return 0;
}
 