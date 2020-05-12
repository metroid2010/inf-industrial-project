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

<<<<<<< Updated upstream
friend class Manager;
=======
>>>>>>> Stashed changes

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
<<<<<<< Updated upstream
    bool menuPublishBark();
    bool menuPublishRebark();
    bool menuPublishReply();
    void menuTimeline();
    void menuSelectPub();
    void menuFeed();
    void menuDeletePublication();
=======
    void menuPublishBark();
    void menuPublishRebark(int id);
    void menuPublishReply(int id);
    void menuTimeline();
    void menuSelectPub(bool allowdelete);
    void menuFeed();
    void menuDeletePublication(int id);
>>>>>>> Stashed changes
    void menuSettings();
    void menuSettingsEditEmail();
    void menuSettingsEditBio();
    void menuSettingsEditUsername();
    void menuSettingsEditPassword();
    void menuSearch();
    void menuSearchResults();
    void menuShowUser();
<<<<<<< Updated upstream
    void menuFollowUser();
    void menuViewFollowersUser();
    void menuViewFollowingUser();
    void menuShowPubsUser();
=======
    void menuFollowUser(int pos);
    void menuViewFollowersUser();
    void menuUnfollowUser(int pos);
    void menuViewFollowingUser(int pos);
    void menuShowPubsUser(int pos);
>>>>>>> Stashed changes

};

#endif // INTERFACE_H
