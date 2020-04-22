/**
* Proyecto Informatica Industrial
* Grupo 9
* Esther Alonso Pinillos, Roberto Uceda Gomez
*
* Archivo de cabecera: User.hpp
*
**/

#include <iostream>
#include "PublicUserData.hpp"
#include "PrivateUserData.hpp"

#ifndef USER_HPP
#define USER_HPP

using namespace std;

class User : public PrivateUserData, public PublicUserData {

private:
    User();

public:
    User(string email, string password, string username, string bio);

};

#endif
