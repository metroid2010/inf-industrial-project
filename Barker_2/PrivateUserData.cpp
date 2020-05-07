/**
* Proyecto Informatica Industrial
* Grupo 9
* Esther Alonso Pinillos, Roberto Uceda Gomez
*
* Implementacion de metodos de clase: PrivateUserData
*
**/

#include "PrivateUserData.hpp"

PrivateUserData::PrivateUserData(string email, string password) {
    _email = email;
    _password = password;
}

string PrivateUserData::getEmail() {
    return _email;
}

string PrivateUserData::getPassword() {
    return _password;
}

void PrivateUserData::setEmail(string newEmail) {
    _email = newEmail;
}

void PrivateUserData::setPassword(string newPassword) {
    _password = newPassword;
}
