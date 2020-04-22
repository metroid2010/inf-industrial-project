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

#ifndef MANAGER_HPP
#define MANAGER_HPP

using namespace std;

class Manager {

private:
    vector<User*> _users;
    int _currentUser;

public:
    Manager();
    int searchUser(string data, string type); // auxiliary function
    bool createUser(string email, string password, string username, string bio);
    vector<PublicUserData*> showUsers();
    PublicUserData* showUser(string username);
    bool login(string email, string password);
    bool isLogged();
    bool logout();
    User* getCurrentUser();
    bool eraseCurrentUser();
    bool editPassword(string password);
    bool editEmail(string email);
    bool editUsername(string username);
    bool editBio(string bio);
    bool followUser(string username);
    bool unfollowUser(string username);
    ~Manager();

};

#endif
