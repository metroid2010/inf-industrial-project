/**
* Proyecto Informatica Industrial
* Grupo 9
* Esther Alonso Pinillos, Roberto Uceda Gomez
*
* Implementacion de metodos de clase: User
*
**/

#include "User.hpp"


User::User(string email, string password, string username, string bio) : PublicUserData(email, password), PrivateUserData(username, bio) {

}
