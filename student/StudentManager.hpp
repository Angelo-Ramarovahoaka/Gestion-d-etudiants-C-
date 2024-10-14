#ifndef STUDENTMANAGER_HPP
#define STUDENTMANAGER_HPP
#include <iostream>
#include <string>
using namespace std;

class StudentManager {
public:
    StudentManager(){}
    void addStudent(const string& firstname , const string& lastname, int age, const string& email, const string& adresse, const string& numberTel, const string& classe, const string& numberCard);
    void displayStudents() const;
    void detailStudents(int id );
    string urlDecode(const string& str);
    void deleteStudent(int id) const;
    void modifyStudent(int id) const;
    void modifierLigne(const std::string& fileName, int index, const std::string& nouvelleLigne);
    void formDetail(const string& firstname , const string& lastname, int age, const string& email, const string& adresse, const string& numberTel, const string& classe, const string& numberCard) const;
    void formModify(const string& firstname , const string& lastname, int age, const string& email, const string& adresse, const string& numberTel, const string& classe, const string& numberCard, int id) const;
    void formInscription(const string& firstname , const string& lastname, int age, const string& email, const string& adresse, const string& numberTel, const string& classe, const string& numberCard) const;
    bool validateEmail(const std::string& email);
    bool validatePhoneNumber(const std::string& phoneNumber);
    void registerStudent(const std::string& email, const std::string& phoneNumber);
    void studentForm(const std::string& sessionFile);
};
#endif // STUDENTMANAGER_HPP
