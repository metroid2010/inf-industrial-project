/**
* Proyecto Informatica Industrial
* Grupo 9
* Esther Alonso Pinillos, Roberto Uceda Gomez
*
* Archivo de cabecera: PrivateUserData.hpp
*
**/

#include <iostream>

using namespace std;

class PrivateUserData {

protected:
    string _email;
    string _password;
    PrivateUserData(string email, string password);

private:
    PrivateUserData();

public:
    string getEmail();
    string getPassword();
    void setEmail(string newEmail);
    void setPassword(string newPassword);

};
