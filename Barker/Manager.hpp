/**
* Proyecto Informatica Industrial
* Grupo 9
* Esther Alonso Pinillos, Roberto Uceda Gomez
*
* Archivo de cabecera: Manager
*
**/

#ifndef MANAGER_HPP
#define MANAGER_HPP

#include <iostream>
#include <vector>
#include "User.hpp"
#include "Bark.hpp"
#include "Rebark.hpp"
#include "Reply.hpp"
#include <ctime>
#include <fstream>
#include <algorithm>

using namespace std;

class Manager {

private:
    vector<User*> _users;
    int _currentUser;
    int searchUser(string data, string type); // funcion auxiliar, fuera de especificaciones
    vector<Publication*> _pubs;

public:
    Manager();
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
    vector<Publication*> getUserFeed(string username);
    vector<Publication*> getTimeline();
    bool createBark(string text);
    bool createRebark(int id, string text);
    bool createReply(int id, string text);
    bool saveToFile(string path);
    bool loadFromFile(string path);
    ~Manager();
    static bool compByTime(Publication* a, Publication* b);

};

#endif
