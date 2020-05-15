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

    // screen decorations
    cout << "------------------------" << endl;

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

    cin.clear();
    return input;
}

int Interface::optionMenu(vector<string> options) {

    // screen decorations
    cout << "------------------------" << endl;

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
        if ( !cin.good() || input < 0 || ( input > options.size() - 1 ) ) {
            cout << "Option not valid, try again" << endl;
            cin.clear();
            cin.ignore(INT_MAX, '\n'); // sanitize our inputs! flush and ignore characters in cin
        } else {
            break; // we got a valid option
        }
    } while ( true );

    cin.clear();
    return input;
}

Interface::Interface(Manager* m) {
    _m = m;
}

void Interface::startInterface() {
    // this is the main function for the interface, which starts an interface and sets the flow that links the next functions
    int option;
    bool logged = false;

    // this loop allows the program to get back to login screen on logout from main menu
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
                                break;
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
            case 2: // load from file
                menuLoadFromDisk();
                break;
            case 3:
                menuSaveToDisk();
                break;
            case 4:
                return; // exit without login
        }
    } while ( !logged );

    return;

}

int Interface::menuLoginScreen() {

    // screen decorations
    cout << endl << "========================" << endl;

    // show login menu

    // options
    vector<string> options = { "Login", "Sign in", "Load from File", "Save state to file", "Exit" };
    cout << "Welcome to Barker!" << endl;
    int input;
    input = optionMenu(options);

    return input;
}

bool Interface::menuLogin() {

    // screen decorations
    cout << endl << "=========Login==========" << endl;

    string email;
    string password;

    // show login prompt
    cout << "Email: ";
    cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n') ;
    getline(cin, email);
    cout << "Password: ";
    //cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n') ;
    getline(cin, password);

    if ( _m->login(email, password) ) {
        cout << "Login successful!" << endl;
        return true;
    } else {
        cout << "Wrong email or password" << endl;
        return false;
    }
}

void Interface::menuCreateUser() {

    // screen decorations
    cout << endl << "======Create=User=======" << endl;

    string email;
    string username;
    string bio;
    string password;

    do {
        cout << "Email: ";
        cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n') ;
        getline(cin, email);
        //cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n') ;
    } while ( email == "");

    do {
        cout << "Password: ";
        getline(cin, password);
        //cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n') ;
    } while ( password == "");

    do {
        cout << "Username: ";
        //cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n') ;
        getline(cin, username);
    } while ( username == "");

    do {
        cout << "Bio: ";
        //cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n') ;
        getline(cin, bio);
    } while ( bio == "");

    if ( _m->createUser(email, password, username, bio) ) {
        cout << "User account created" << endl;
    } else {
        cout << "Error, account not created" << endl;
    }
}

void Interface::menuDeleteUser() {

    // screen decorations
    cout << endl << "=======Delete=User======" << endl;

    string password;
    int input;

    cout << "Enter current password" << endl;
    cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n') ;
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

    // screen decorations
    cout << endl << "========Log=Out=========" << endl;

    int input;

    // options
    string prompt = "Are you sure you want to logout?";
    vector<string> options = { "Yes", "No" };
    input = optionMenu(options, prompt);
    if ( input == 0 ) {
        if ( _m-> logout() ){
            cout << "Logged out" << endl;
            return 0;
        } else {
            cout << "Error trying to log out" << endl;
            return 1;
        }
    } else {
        cout << "Logout cancelled" << endl;
        return 1;
    }

    return input;
}

int Interface::menuMain() {

    // screen decorations
    cout << endl << "=======Main=Menu========" << endl;

    cout << "Welcome to Bark " << _m->getCurrentUser()->getUsername() << endl;

    // options
    vector<string> options = { "Publish Bark", "Show followed users' timeline", "Show Feed", "Search user", "View current Followers and Following Users", "Settings", "Logout" };
    int input;
    input = optionMenu(options);

    return input;

}


void Interface::menuPublishBark() {

    // screen decorations
    cout << endl << "==========Bark==========" << endl;


    string text;
    cout << "Text to bark: " << endl;
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
    }else{
        cout << "Publication cancel" << endl;
    }
}

void Interface::menuPublishRebark(int id) {

    // screen decorations
    cout << endl << "=========Rebark=========" << endl;

    string text;
    int position = _m->searchPub(id);

    cout << "Original Bark:" << endl;
    cout << _m->_pubs[position]->getBarkPretty() << endl;

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
    }else{
        cout << "Publication cancel" << endl;
    }
    return;

}

void Interface::menuPublishReply(int id) {

    // screen decorations
    cout << endl << "=========Reply==========" << endl;

    string text;
    int position = _m->searchPub(id);

    cout << "Original Bark:" << endl;
    cout << _m->_pubs[position]->getBarkPretty() << endl;

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
    }else{
        cout << "Publication cancel" << endl;
    }
    return;

}

void Interface::menuTimeline() {

    // screen decorations
    cout << endl << "=========Timeline=======" << endl;

    vector<Publication*> timeline;
    timeline = _m->getTimeline();

    for(int i=0; i< (int) timeline.size(); i++){
        cout << "Publication ID:" << timeline[i]->getId() << endl;
        cout << timeline[i]->getBarkPretty() << endl;
    }

    if((int) timeline.size()>0){
        // options
        vector<string> options = {"Select Publication" , "Back to Main"};
        int input = optionMenu(options);
        if (input==0){
            menuSelectPub(false);
        }
    }
    return;
}

void Interface::menuSelectPub(bool allowdelete) {

    // screen decorations
    cout << endl << "===Select=Publication===" << endl;

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

    // screen decorations
    cout << endl << "=========Feed===========" << endl;

    vector<Publication*> feed;
    feed = _m->getUserFeed(_m->getCurrentUser()->getUsername());

    //Show publications current user
    for(int i=0; i< (int) feed.size(); i++){
        cout << "Publication ID:" << feed[i]->getId() << endl;
        cout << feed[i]->getBarkPretty() << endl;
    }

    if((int) feed.size()>0){
        // options
        vector<string> options = {"Select Publication", "Back to Main"};
        int input = optionMenu(options);
        if (input==0){
            menuSelectPub(true);
        }
    }
    return;

}

void Interface::menuDeletePublication(int id) {

    // screen decorations
    cout << endl << "===Delete=Publication===" << endl;

    int position;
    int input;

    //search position in vector _pubs
    position = _m->searchPub(id);

    // options
    string prompt = "Confirm delete publication with id: " + to_string(id);
    vector<string> options = { "Yes", "No"};
    input = optionMenu(options, prompt);
    if(input==0){
        if(_m->deletePublication(position)){
            cout << "Publication succesfully deleted" << endl;
        }else{
            cout << "Publication not deleted" << endl;
        }
    }else{
        cout << "Delete operation cancel" << endl;
    }
    return;

}

void Interface::menuSettings() {

    // screen decorations
    cout << endl << "========Settings========" << endl;

    string prompt = "Choose:";

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
    cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n') ;
    getline(cin, email);

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
    cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n') ;
    getline(cin, username);

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
        cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n') ;
        getline(cin, newpassword);

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

    // screen decorations
    cout << endl << "=========Search=========" << endl;

    cout << "All users in BARKER:" << endl;
    for(int i=0; i< (int) _m->_users.size(); i++){
        cout << _m->_users[i]->getUsername() << endl;
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

    // screen decorations
    cout << endl << "=====Show=User==========" << endl;

    string username;

    cout << "Enter username to visualize" << endl;
    cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n') ;
    getline(cin, username);
    int position = _m->searchUser(username, "username");
    if (position!=-1){
        cout << "Username:" << _m->_users[position]->getUsername() << endl;
        cout << "Email:" << _m->_users[position]->getEmail() << endl;
        cout << "Bio:" << _m->_users[position]->getBio() << endl;

        // options
        vector<string> options = { "Follow User", "View User's Followers and Following Users", "View User's Publications", "Back to Main"};
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
            cout << "Username: " << username << " not found";
    }
    return;

}

void Interface::menuFollowUser(int pos) {

    // screen decorations
    cout << endl << "======Follow=User=======" << endl;

    if(_m->followUser(_m->_users[pos]->getUsername())){
        cout << "Now you are following " << _m->_users[pos]->getUsername() << endl;
    }else{
        cout << "Error trying to follow user" << endl;
    }
    return;
}

void Interface::menuUnfollowUser(int pos) {

    // screen decorations
    cout << endl << "======Unfollow=User=====" << endl;

    if(_m->unfollowUser(_m->getCurrentUser()->getFollowing()[pos]->getUsername())){
        cout << "Unfollowed user succesfully"<< endl;
    }else{
        cout << "Error trying to unfollow user"<< endl;
    }
    return;
}

void Interface::menuViewFollowersUser() {

    // screen decorations
    cout << endl << "=====View=Followers=&=Following=======" << endl;

    cout << _m->getCurrentUser()->getUsername() << " has " << _m->getCurrentUser()->getFollowers() << " number of followers" << endl;
    cout << "The users you are following are:" << endl;

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
        cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n') ;
        getline(cin, username);
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

    // screen decorations
    cout << endl << "=====View=Followers=&=Following=======" << endl;

    cout << _m->_users[pos]->getUsername() << " has " << _m->_users[pos]->getFollowers() << " number of followers" << endl;
    cout << "The usernames " << _m->_users[pos]->getUsername() << " is following are:" << endl;

        for(int i=0; i< (int)_m->_users[pos]->getFollowing().size(); i++){
            cout << _m->_users[pos]->getFollowing()[i]->getUsername() << endl;
        }
    return;

}

void Interface::menuShowPubsUser(int pos) {

    // screen decorations
    cout << endl << "====View=Publications===" << endl;

    cout << "The publications of " << _m->_users[pos]->getUsername() << " are: " << endl;
    vector<Publication*> feed;
    feed = _m->getUserFeed(_m->_users[pos]->getUsername());

    //Show publications current user
    for(int i=0; i< (int) feed.size(); i++){
        cout << "Publication ID: " << feed[i]->getId() << " - ";
        cout << feed[i]->getBarkPretty() << endl;
    }

    // options
    vector<string> options = {"Select Publication", "Back to Main"};
    int input = optionMenu(options);
    if (input==0){
        menuSelectPub(false);
    }
    return;

}

void Interface::menuSaveToDisk() {

    // screen decorations
    cout << endl << "=======Save=To=Disk=====" << endl;

    // using Manager::saveToFile
    string prompt = "Save Barker state to disk?";
    vector<string> options = { "Yes", "No" };
    int input = optionMenu(options, prompt);

    // path to file, hardcoded name in same directory as executable
    string path = "barker.data";

    if ( input == 0 ){
        if ( _m->saveToFile(path) ) {
            cout << "Data saved as " << path << endl;
        } else {
            cout << "Error saving " << path << endl;
        }
    } else {
        cout << "Save operation cancelled" << endl;
    }

}

void Interface::menuLoadFromDisk() {

    // screen decorations
    cout << endl << "=====Load=From=Disk=====" << endl;

    // path to file, hardcoded name in same directory as executable
    string path = "barker.data";

    // using Manager::loadFromFile
    string prompt = "Load Barker state from disk? (file named " + path + ")";
    vector<string> options = { "Yes", "No" };
    int input = optionMenu(options, prompt);

    if ( input == 0 ){
        if ( _m->loadFromFile(path) ) {
            cout << "Data loaded succesfully from " << path << endl;
        } else {
            cout << "Error loading from " << path << endl;
            cout << "Check file exists and is readable" << endl;
        }
    } else {
        cout << "Load operation cancelled" << endl;
    }

}
