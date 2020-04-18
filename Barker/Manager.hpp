/**
* Proyecto Informatica Industrial
* Grupo 9
* Esther Alonso Pinillos, Roberto Uceda Gomez
*
* Archivo de cabecera: Manager
*
**/

#include <iostream>
#include <vector>
#include "User.hpp"

using namespace std;

class Manager {

private:
    vector<User*> _users;
    int _currentUser;

public:
    Manager();

    bool createUser(string email, string password, string username, string bio);
    vector<PublicUserData*> showUsers();
    PublicUserData* showUser(string username);
    bool login(string username, string password);
    ~Manager();


};
