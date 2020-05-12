/**
* Proyecto Informatica Industrial
* Grupo 9
* Esther Alonso Pinillos, Roberto Uceda Gomez
*
* Clase interfaz, implementacion
*
**/

#include "Interface.hpp"

Interface::Interface() {}

int Interface::optionMenu(vector<string> options, string prompt) {
    // show prompt
    cout << prompt << endl;

    // show options
    for ( int i = 0; i < (int) options.size(); i++ ) {
        cout << "1- " << options[i] << endl;
    }

    // get option
    uint input;
    do {
        cout << "$> ";
        cin >> input;
        if ( cin.fail() || input < 0 || input > options.size() ) {
            cout << "Option not valid, try again" << endl;
        } else {
            break; // we got a valid option
        }
    } while ( true );

    return input;
}

int Interface::optionMenu(vector<string> options) {
    // show prompt
    string prompt = "Choose an option"; // default prompt
    cout << prompt << endl;

    // show options
    for ( int i = 0; i < (int) options.size(); i++ ) {
        cout << "1- " << options[i] << endl;
    }

    // get option
    uint input;
    do {
        cout << "$> ";
        cin >> input;
        if ( cin.fail() || input < 0 || input > options.size() ) {
            cout << "Option not valid, try again" << endl;
        } else {
            break; // we got a valid option
        }
    } while ( true );

    return input;
}

Interface::Interface(Manager* m) {
    _m = m;
}

void startInterface() {
    // this is the main function for the interface, which starts an interface and sets the flow that links the next functions

}

void Interface::menuLogin() {

}

void Interface::menuCreateUser() {

}

void Interface::menuDeleteUser() {

}

void Interface::menuLogout() {

}

void Interface::menuMain() {

}

void Interface::menuPublishBark() {

}

void Interface::menuPublishRebark() {

}

void Interface::menuPublishReply() {

}

void Interface::menuTimeline() {

}

void Interface::menuSelectPub() {

}

void Interface::menuFeed() {

}

void Interface::menuDeletePublication() {

}

void Interface::menuSettings() {

}

void Interface::menuSettingsEditEmail() {

}

void Interface::menuSettingsEditBio() {

}

void Interface::menuSettingsEditUsername() {

}

void Interface::menuSettingsEditPassword() {

}

void Interface::menuSearch() {

}

void Interface::menuSearchResults() {

}

void Interface::menuShowUser() {

}

void Interface::menuFollowUser() {

}

void Interface::menuViewFollowersUser() {

}

void Interface::menuViewFollowingUser() {

}

void Interface::menuShowPubsUser() {

}


