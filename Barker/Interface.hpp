/**
* Proyecto Informatica Industrial
* Grupo 9
* Esther Alonso Pinillos, Roberto Uceda Gomez
*
* Clase interfaz, definicion
*
**/

#ifndef INTERFACE_H
#define INTERFACE_H

#include <iostream>
#include "Manager.hpp"

class Interface {

friend class Manager;

private:
    Interface();
    Manager* _m;
    int optionMenu(vector<string> options, string prompt);
    int optionMenu(vector<string> options);

public:
    Interface(Manager* m);
    void startInterface();
    int menuLoginScreen();
    bool menuLogin();
    void menuCreateUser();
    void menuDeleteUser();
    int menuLogout();
    int menuMain();
    bool menuPublishBark();
    bool menuPublishRebark();
    bool menuPublishReply();
    void menuTimeline();
    void menuSelectPub();
    void menuFeed();
    void menuDeletePublication();
    void menuSettings();
    void menuSettingsEditEmail();
    void menuSettingsEditBio();
    void menuSettingsEditUsername();
    void menuSettingsEditPassword();
    void menuSearch();
    void menuSearchResults();
    void menuShowUser();
    void menuFollowUser();
    void menuViewFollowersUser();
    void menuViewFollowingUser();
    void menuShowPubsUser();

};

#endif // INTERFACE_H
