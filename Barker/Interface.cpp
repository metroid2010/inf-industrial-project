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
        cout << i << "- " << options[i] << endl;
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

void Interface::startInterface() {
    // this is the main function for the interface, which starts an interface and sets the flow that links the next functions
    int option;
    bool logged = false;
    do {
        option = menuLoginScreen();
        switch (option) {
            case 0:
                if ( menuLogin() ) {
                    logged = true;
                }
                break;
            case 1:
                menuCreateUser();
                break;
            case 2:
                return;
        }
    } while ( !logged );

    // main loop
    int mainSelect;
    int loggedout = 0;
    do {

        mainSelect = menuMain();
        switch ( mainSelect ) {
            case 0:

            case 1:

            case 2:
            case 3:
            case 4:

            case 5:
                loggedout = menuLogout();
        }

    } while ( loggedout == 0 ); // exit on user chose to logout



}

int Interface::menuLoginScreen() {
    // show login menu

    // options
    vector<string> options = { "Login", "Sign in", "Exit" };
    cout << "Welcome to Barker!" << endl;
    int input;
    input = optionMenu(options);

    return input;
}

bool Interface::menuLogin() {

    string email;
    string password;

    // show login prompt
    cout << "Email: ";
    cin >> email;
    cout << "Password: ";
    getline(cin, password);

    return ( _m->login(email, password) );
}

void Interface::menuCreateUser() {

    string email;
    string username;
    string bio;
    string password;

    cout << "Email: ";
    cin >> email;
    cout << "Password: ";
    getline(cin, password);
    cout << "Username: ";
    cin >> username;
    cout << "Bio: ";
    getline(cin, bio);

    if ( _m->createUser(email, password, username, bio) ) {
        cout << "User account created" << endl;
    } else {
        cout << "Error, account not created" << endl;
    }
}

void Interface::menuDeleteUser() {

}

int Interface::menuLogout() {

    int input;
    string prompt = "Are you sure you want to logout?";
    vector<string> options = { "Yes", "No" };
    input = optionMenu(options, prompt);

    return input;
}

int Interface::menuMain() {

    cout << "Welcome to Bark!" << endl;

    // options
    vector<string> options = { "Publish Bark", "Show followed users' timeline", "Show Feed", "Search user", "Settings", "Logout" };
    int input;
    input = optionMenu(options);

    return input;

}

bool Interface::menuPublishBark() {
    string text;
    cout << "Text to bark: ";
    getline(cin, text);
    string prompt = "Confirm publish? ";
    vector<string> options = { "Yes", "Cancel" };
    int input = optionMenu(options, prompt);
    if ( input == 0 ) {
        _m->createBark(text);
        return true;
    } else {
        return false;
    }
}

bool Interface::menuPublishRebark() {

}

bool Interface::menuPublishReply() {

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


