/**
* Proyecto Informatica Industrial
* Grupo 9
* Esther Alonso Pinillos, Roberto Uceda Gomez
*
* Archivo de cabecera: User.hpp
*
**/

#ifndef USER_HPP
#define USER_HPP

#include <iostream>
#include "PublicUserData.hpp"
#include "PrivateUserData.hpp"

using namespace std;

class User : public PrivateUserData, public PublicUserData {

private:
    User();

public:
    User(string email, string password, string username, string bio);

};

#endif
