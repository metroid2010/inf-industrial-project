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

                    // main loop
                    int mainSelect;
                    int loggedout = 1;

                    do {
                        mainSelect = menuMain();
                        switch ( mainSelect ) {
                            case 0:
                                menuPublishBark();
                                break;
                            case 1:
                                menuTimeline();
                                break;
                            case 2:
                                menuFeed();
                                break;
                            case 3:
                                menuSearch();
                                break;
                            case 4:
                                menuViewFollowersUser();
                            case 5:
                                menuSettings();
                                break;
                            case 6:
                                loggedout = menuLogout();
                        }

                    } while ( loggedout == 1 && _m->isLogged() ); // exit on user chose to logout

                    logged = false;
                }
                break;

            case 1:
                menuCreateUser();
                break;
            case 2:
                return; // exit without login
        }
    } while ( !logged );

    return;

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
    cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n') ;
    getline(cin, password);

    if ( _m->login(email, password) ) {
        cout << "Login successful!" << endl;
        return true;
    } else {
        cout << "Wrong username or password" << endl;
        return false;
    }
}

void Interface::menuCreateUser() {

    string email;
    string username;
    string bio;
    string password;

    cout << "Email: ";
    cin >> email;
    cout << "Password: ";
    cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n') ;
    getline(cin, password);
    cout << "Username: ";
    cin >> username;
    cout << "Bio: ";
    cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n') ;
    getline(cin, bio);

    if ( _m->createUser(email, password, username, bio) ) {
        cout << "User account created" << endl;
    } else {
        cout << "Error, account not created" << endl;
    }
}

void Interface::menuDeleteUser() {
    string password;
    int input;

    cout << "Enter current password" << endl;
    getline(cin, password);

    if(password==_m->getCurrentUser()->getPassword()){

        // options
        string prompt = "Confirm delete account" + _m->getCurrentUser()->getUsername();
        vector<string> options = { "Yes", "No"};
        input = optionMenu(options, prompt);
        if(input==0){
            if(_m->eraseCurrentUser()){
                cout << "User account succesfully delete!" << endl;
            }else{
                cout << "Error";
            }
        }else{
            cout << "Delete operation cancel!" << endl;
        }
    }else{
        cout << "Wrong password" << endl;
    }
    return;


}

int Interface::menuLogout() {

    int input;

    // options
    string prompt = "Are you sure you want to logout?";
    vector<string> options = { "Yes", "No" };
    input = optionMenu(options, prompt);

    return input;
}

int Interface::menuMain() {

    cout << "Welcome to Bark " << _m->getCurrentUser()->getUsername() << endl;

    // options
    vector<string> options = { "Publish Bark", "Show followed users' timeline", "Show Feed", "Search user", "View current followers", "Settings", "Logout" };
    int input;
    input = optionMenu(options);

    return input;

}


void Interface::menuPublishBark() {
    string text;
    cout << "Text to bark: ";
    cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n') ;
    getline(cin, text);

    // options
    string prompt = "Confirm publish? ";
    vector<string> options = { "Yes", "Cancel" };
    int input = optionMenu(options, prompt);
    if ( input == 0 ) {
        if(_m->createBark(text)){
            cout << "Bark succesfully published" << endl;
        }
    }
}

void Interface::menuPublishRebark(int id) {
    string text;
    int position = _m->searchPub(id);

    cout << "Original Bark:" << endl;
    cout << _m->_pubs[position]->getBark() << endl;

    cout << "Text to Rebark: " << endl;
    cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n') ;
    getline(cin, text);

    // options
    string prompt = "Confirm publish? ";
    vector<string> options = { "Yes", "Cancel" };
    int input = optionMenu(options, prompt);
    if ( input == 0 ) {
        if(_m->createRebark(id, text)){
            cout << "Rebark succesfully published" << endl;
        }
    }
    return;

}

void Interface::menuPublishReply(int id) {
    string text;
    int position = _m->searchPub(id);

    cout << "Original Bark:" << endl;
    cout << _m->_pubs[position]->getBark() << endl;

    cout << "Text to Reply: " << endl;
    cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n') ;
    getline(cin, text);

    // options
    string prompt = "Confirm publish?";
    vector<string> options = { "Yes", "Cancel" };
    int input = optionMenu(options, prompt);
    if ( input == 0 ) {
        if(_m->createReply(id, text)){
            cout << "Reply succesfully published" << endl;
        }
    }
    return;

}

void Interface::menuTimeline() {

    vector<Publication*> timeline;
    timeline = _m->getTimeline();

    for(int i=0; i< (int) timeline.size(); i++){
        cout << timeline[i]->getId() << endl;
        cout << timeline[i]->getBark();
    }

    // options
    vector<string> options = {"Select Publication" , "Back to Main"};
    int input = optionMenu(options);
    if (input==0){
        menuSelectPub(false);
    }
    return;
}

void Interface::menuSelectPub(bool allowdelete) {
    int id;
    int position=-1;
    cout << "Id Publication:";
    cin >> id;

    //search position in vector _pubs
    position = _m->searchPub(id);

    if(position!=-1){
        // options
        vector<string> options;
        if(allowdelete==false){
            options = {"Create Rebark", "Create Reply", "Back to Main"};
        }else{
            options = {"Create Rebark", "Create Reply", "Back to Main", "Delete Publication"};
        }
        int input = optionMenu(options);
        switch (input) {
            case 0:
                menuPublishRebark(id);
                break;
            case 1:
                menuPublishReply(id);
                break;
            case 2:
                return;
            case 3:
                menuDeletePublication(id);
        }
    }else{
        cout << "Bark not found!" << endl;
    }
    return;
}

void Interface::menuFeed() {
    vector<Publication*> feed;
    feed = _m->getUserFeed(_m->getCurrentUser()->getUsername());

    //Show publications current user
    for(int i=0; i< (int) feed.size(); i++){
        cout << feed[i]->getId() << endl;
        cout << feed[i]->getBark();
    }

    // options
    vector<string> options = {"Select Publication", "Back to Main"};
    int input = optionMenu(options);
    if (input==0){
        menuSelectPub(true);
    }
    return;

}

void Interface::menuDeletePublication(int id) {
    int position;
    int input;

    //search position in vector _pubs
    position = _m->searchPub(id);

    // options
    string prompt = "Confirm delete publication with id: " + to_string(id);
    vector<string> options = { "Yes", "No"};
    input = optionMenu(options, prompt);
    if(input==0){
        _m->deletePublication(position);
    }else{
        cout << "Delete operation cancel" << endl;
    }
    return;

}

void Interface::menuSettings() {
    string prompt = "Settings:";

    // options
    vector<string> options = { "Edit Email", "Edit Password", "Edit Username", "Edit Bio", "Delete Account", "Back to Main"};
    int input;
    input = optionMenu(options, prompt);
    switch (input) {
        case 0:
            menuSettingsEditEmail();
            break;
        case 1:
            menuSettingsEditPassword();
            break;
        case 2:
            menuSettingsEditUsername();
            break;
        case 3:
            menuSettingsEditBio();
            break;
        case 4:
            menuDeleteUser();
            break;
        case 5:
            break;
    }
    return;

}

void Interface::menuSettingsEditEmail() {
    string email;
    int input;
    cout << "Enter new Email" << endl;
    cin >> email;

    // options
    string prompt = "Confirm change Email to " + email + "?";
    vector<string> options = { "Yes", "No"};
    input = optionMenu(options, prompt);
    if(input==0){
        if(_m->editEmail(email)){
            cout << "Email succesfully changed!" << endl;
        }else{
            cout << "Error";
        }
    }else{
        cout << "Edit operation cancel!" << endl;
    }

    return;
}

void Interface::menuSettingsEditBio() {
    string bio;
    int input;
    cout << "Enter new Bio" << endl;
    cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n') ;
    getline(cin, bio);

    // options
    string prompt = "Confirm change Bio to " + bio + "?";
    vector<string> options = { "Yes", "No"};
    input = optionMenu(options, prompt);
    if(input==0){
        if(_m->editBio(bio)){
            cout << "Bio succesfully changed!" << endl;
        }else{
            cout << "Error";
        }
    }else{
        cout << "Edit operation cancel!" << endl;
    }

    return;
}

void Interface::menuSettingsEditUsername() {
    string username;
    int input;
    cout << "Enter new Username" << endl;
    cin >> username;

    // options
    string prompt = "Confirm change username to " + username + "?";
    vector<string> options = { "Yes", "No"};
    input = optionMenu(options, prompt);
    if(input==0){
        if(_m->editUsername(username)){
            cout << "Username succesfully changed!" << endl;
        }else{
            cout << "Error";
        }
    }else{
        cout << "Edit operation cancel!" << endl;
    }
    return;
}

void Interface::menuSettingsEditPassword() {
    string password, newpassword;
    int input;

    cout << "Enter current password" << endl;
    cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n') ;
    getline(cin, password);

    if(password==_m->getCurrentUser()->getPassword()){
        cout << "Enter new password" << endl;
        cin >> newpassword;

        // options
        string prompt = "Confirm change Password";
        vector<string> options = { "Yes", "No"};
        input = optionMenu(options, prompt);
        if(input==0){
            if(_m->editPassword(newpassword)){
                cout << "Password succesfully changed!" << endl;
            }else{
                cout << "Error";
            }
        }else{
            cout << "Edit operation cancel!" << endl;
        }
    }else{
        cout << "Wrong password" << endl;
    }
    return;

}

void Interface::menuSearch() {
    cout << "All users in BARKER:" << endl;
    for(int i=0; i< (int) _m->_users.size(); i++){
        cout << _m->getCurrentUser()->getUsername() << endl;
    }

    int input;
    // options
    vector<string> options = { "Select User", "Back to Main"};
    input = optionMenu(options);
    if(input==0){
        menuShowUser();
    }
    return;
}

void Interface::menuSearchResults() {

}

void Interface::menuShowUser() {
    string username;

    cout << "Enter username to visualize" << endl;
    cin >> username;
    int position = _m->searchUser(username, "username");
    if (position!=-1){
        cout << "Username:" << _m->_users[position]->getUsername() << endl;
        cout << "Username:" << _m->_users[position]->getEmail() << endl;
        cout << "Username:" << _m->_users[position]->getBio() << endl;

        // options
        vector<string> options = { "Follow User", "View User's Followers", "View User's Publications", "Back to Main"};
        int input;
        input = optionMenu(options);
        switch (input) {
            case 0:
                menuFollowUser(position);
                break;
            case 1:
                menuViewFollowingUser(position);
                break;
            case 2:
                menuShowPubsUser(position);
                break;
            case 3:
                return;
        }
    }else{
            cout << "Username: " << username << "not found";
    }
    return;

}

void Interface::menuFollowUser(int pos) {

    if(_m->followUser(_m->_users[pos]->getUsername())){
        cout << "Now you are following " << _m->_users[pos]->getUsername() << endl;
    }else{
        cout << "Error trying to follow user" << endl;
    }
    return;
}

void Interface::menuUnfollowUser(int pos) {

    if(_m->unfollowUser(_m->_users[pos]->getUsername())){
        cout << "Unfollowed user succesfully"<< endl;
    }else{
        cout << "Error trying to follow user"<< endl;
    }
    return;
}

void Interface::menuViewFollowersUser() {
    cout << _m->getCurrentUser()->getUsername() << " has " << _m->getCurrentUser()->getFollowers() << "number of followers" << endl;
    cout << "The followers' usernames are:" << endl;

    for(int i=0; i< (int)_m->getCurrentUser()->getFollowing().size(); i++){
        cout << _m->getCurrentUser()->getFollowing()[i]->getUsername() << endl;
    }

    int input, position=-1;
    string username;

    // options
    vector<string> options = { "Unfollow User", "Back to Main"};
    input = optionMenu(options);
    if(input==0){
        cout << "Enter username to unfollow:" << endl;
        cin >> username;
        for(int i=0; i< (int)_m->getCurrentUser()->getFollowing().size(); i++){
                if(username== _m->getCurrentUser()->getFollowing()[i]->getUsername()){
                    position=i;
                    break;
                }
        }
        if (position!=-1 ){
            menuUnfollowUser(position);
        }else{
            cout << "User not in followers" << endl;
        }
    }
    return;
}

void Interface::menuViewFollowingUser(int pos) {
    cout << _m->_users[pos]->getUsername() << " has " << _m->_users[pos]->getFollowers() << "number of followers" << endl;
    cout << "The followers' usernames are:" << endl;

    for(int i=0; i< (int)_m->_users[pos]->getFollowing().size(); i++){
        cout << _m->_users[pos]->getFollowing()[i]->getUsername() << endl;
    }
    return;

}

void Interface::menuShowPubsUser(int pos) {
    cout << "The publications of " << _m->_users[pos]->getUsername() << "are:";
    vector<Publication*> feed;
    feed = _m->getUserFeed(_m->_users[pos]->getUsername());

    //Show publications current user
    for(int i=0; i< (int) feed.size(); i++){
        cout << feed[i]->getId() << endl;
        cout << feed[i]->getBark();
    }

    // options
    vector<string> options = {"Select Publication", "Back to Main"};
    int input = optionMenu(options);
    if (input==0){
        menuSelectPub(false);
    }
    return;

}


