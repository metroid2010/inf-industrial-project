/**
* Proyecto Informatica Industrial
* Grupo 9
* Esther Alonso Pinillos, Roberto Uceda Gomez
*
* Implementacion de metodos de clase: Manager
*
**/

#include "Manager.hpp"

Manager::Manager() {
    _currentUser = 0;
}

bool Manager::createUser(string email, string password, string username, string bio) {

    // check username does not exist to avoid duplicate users
    for (uint i = 0; i < _users.size(); i++ ) {
        if ( _users[i]->getUsername() == username ) {
            return false;
        }
    }

    User* u = new User (email, password, username, bio);
    _users.push_back(u);

    return true;
}

vector<PublicUserData*> Manager::showUsers() {
    // TODO
}

PublicUserData* Manager::showUser(string username) {

    // check username exists
    for (uint i = 0; i < _users.size(); i++ ) {
        if ( _users[i]->getUsername() == username ) {
            // TODO
        }
    }

    // username not found
    return nullptr;
}

bool Manager::login(string username, string password) {

    // username exists
    bool username_exists = false;
    for (uint i = 0; i < _users.size(); i++ ) {
        if ( _users[i]->getUsername() == username ) {
            username_exists = true;
        }
    }

    if ( username_exists == true && isLogged(username) )

}

