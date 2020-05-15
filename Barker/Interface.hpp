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
#include <string>
#include <climits>

class Interface {

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
    void menuPublishBark();
    void menuPublishRebark(int id);
    void menuPublishReply(int id);
    void menuTimeline();
    void menuSelectPub(bool allowdelete);
    void menuFeed();
    void menuDeletePublication(int id);
    void menuSettings();
    void menuSettingsEditEmail();
    void menuSettingsEditBio();
    void menuSettingsEditUsername();
    void menuSettingsEditPassword();
    void menuSearch();
    void menuSearchResults();
    void menuShowUser();
    void menuFollowUser(int pos);
    void menuViewFollowersUser();
    void menuUnfollowUser(int pos);
    void menuViewFollowingUser(int pos);
    void menuShowPubsUser(int pos);
    void menuSaveToDisk();
    void menuLoadFromDisk();

};

#endif // INTERFACE_H
