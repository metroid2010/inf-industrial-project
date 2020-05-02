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
    _currentUser = -1;
}

// auxiliary function, search for user in _users given some data
// returns its uid (index in _users)
int Manager::searchUser(string data, string type) {

    if ( type == "username" ) {
        for (uint i = 0; i < _users.size(); i++ ) {
            if ( _users[i]->getUsername() == data ) {
                return i; // no need to keep iterating
            }
        }

    } else if ( type == "email" ) {
        for (uint i = 0; i < _users.size(); i++ ) {
            if ( _users[i]->getEmail() == data ) {
                return i; // no need to keep iterating
            }
        }
    }

    // user not found or other error
    return -1;
}

bool Manager::createUser(string email, string password, string username, string bio) {

    // check username does not exist to avoid duplicate users
    if ( searchUser(username, "username") != -1 ) {
        return false;
    }

    User* u = new User (email, password, username, bio);
    _users.push_back(u);

    return true;
}

vector<PublicUserData*> Manager::showUsers() {

    vector<PublicUserData*> pus; // pus == PublicUserData vector
    // cast every element of _users to PublicUserData*, append to vector
    for (uint i = 0; i < _users.size(); i++ ) {
        pus.push_back( (PublicUserData*) _users[i] );
    }

    return pus;
}

PublicUserData* Manager::showUser(string username) {

    // find username in _users
    int uid = searchUser(username, "username");
    if ( uid != -1 ) {
        return (PublicUserData*) _users[uid];
    }

    // username not found
    return nullptr;
}

bool Manager::login(string email, string password) {

    // check if there is a user already logged in
    if ( _currentUser != -1 ) {
        return false; // can't login
    }

    // search user given its email
    int uid = searchUser(email, "email");

    // if user exists and there is no one loggedin, can login
    if ( uid != -1 ) {

        // now check password
        if ( password == _users[uid]->getPassword() ) {

            //everything ok, login
            _currentUser = uid; // change _currentUser to the new loggedin user
            return true;
        }
    }

    // either password incorrect, user does not exist, or other error
    return false; // can't login
}

bool Manager::isLogged() {
    return ( _currentUser != -1 );
}

bool Manager::logout() {
    // check there is a loggedin user
    if ( _currentUser != -1 ) {
        _currentUser = -1;
        return true;
    } else {
        // there was no user loggedin
        return false;
    }
}

User* Manager::getCurrentUser() {
    // check there is a loggedin user
    if ( _currentUser != -1 ) {
        return _users[_currentUser];
    } else {
        // there was no user loggedin
        return nullptr;
    }
}

bool Manager::eraseCurrentUser() {

    // check there is a loggedin user
    if ( _currentUser != -1 ) {

        // delete publications from user
        for ( int i = 0; i < (int) _users[_currentUser]->getPublications().size(); i++ ) {
            // erase pointers in _pubs to user publications
            _pubs.erase( _pubs.begin() + _users[_currentUser]->getPublications()[i]->getId() );
            delete _users[_currentUser]->getPublications()[i];
        }

        // first delete the user
        delete _users[_currentUser];

        // remove pointer at position _currentUser (index)
        _users.erase(_users.begin() + _currentUser);

        // logout user (dereference user in _currentUser)
        logout();

        // everything OK
        return true;
    } else {
        // there was no user loggedin
        return false;
    }
}

bool Manager::editPassword(string password) {
    // check there is a loggedin user
    if ( _currentUser != -1 ) {
        _users[_currentUser]->setPassword(password);
        return true;
    } else {
        return false;
    }
}

bool Manager::editEmail(string email) {

    // check there is a loggedin user and no other user has the same email
    if ( ( _currentUser != -1 ) && ( searchUser(email, "email") == -1 ) ) {

        // set new email
        _users[_currentUser]->setEmail(email);
        return true;
    }

    return false; // can't change email
}

bool Manager::editUsername(string username) {

    // check there is a loggedin user and no other user has the same username
    if ( ( _currentUser != -1 ) && ( searchUser(username, "username") == -1 ) ) {

        // set new email
        _users[_currentUser]->setUsername(username);
        return true;
    }

    return false; // can't change username
}

bool Manager::editBio(string bio) {
    // check there is a loggedin user
    if ( _currentUser != -1 ) {
        _users[_currentUser]->setBio(bio);
        return true;
    } else {
        return false;
    }
}

bool Manager::followUser(string username) {

    // check there is a loggedin user
    if ( _currentUser == -1 ) {
        return false; // no user logged in
    }

    // check user is not trying to follow itself
    if ( _users[_currentUser]->getUsername() == username ) {
        return false;
    }

    // search username in _users, get its uid
    int uid = searchUser(username, "username");

    // check username exists, and is not followed
    if ( uid != -1 ) {

        // call currentUser.follow, need cast
        if ( _users[_currentUser]->follow( (PublicUserData*) _users[uid] ) == false ) {
            return false;
        }

        // increase number of followers on followed user
        _users[uid]->increaseFollowers();

        return true;
    }

    return false; // can't follow
}

bool Manager::unfollowUser(string username) {

    // check there is a loggedin user
    if ( _currentUser == -1 ) {
        return false; // no user logged in
    }

    // search username in _users, get its uid
    int uid = searchUser(username, "username");

    // check username exists
    if ( uid != -1 ) {

        // call User.unfollow, need cast
        if ( _users[_currentUser]->unfollow( (PublicUserData*) _users[uid] ) == false ) {
            return false;
        }

        // decrease number of followers on followed user
        _users[uid]->decreaseFollowers();

        return true;
    }

    return false; // can't unfollow
}

vector<Publication *> Manager::getUserFeed(string username) {

    // check user exists, get its id
    int id = searchUser(username, "username");

    // return empty vector if user does not exist
    if ( id == -1 ) {
        return vector<Publication*>();
    }

    // user exists, send user._publications
    return _users[id]->getPublications();

}

vector<Publication*> Manager::getTimeline() {

    // declare vector to return
    vector<Publication*> timeline; // it's empty for now

    // check some user is logged in
    if ( _currentUser == -1 ) {
        // no user logged in, return empty vector
        return timeline;
    }

    // get following from logged user
    vector<PublicUserData*> following = _users[_currentUser]->getFollowing();

    // iterate timeline list, get list of publications from each user on it
    for ( uint i = 0 ; i < following.size() ; i++ ){

        // iterate list of publications for user i in timeline list, append
        for ( uint j = 0; j < following[i]->getPublications().size(); j++ ) {
            timeline.push_back( following[i]->getPublications()[j] );
        }
    }

    // return vector
    return timeline;

}

bool Manager::createBark(string text) {

    // check some user is logged in
    if ( _currentUser == -1 ) {
        // no user logged in, return empty vector
        return false;
    }

    // get last id of publication list, add one to get this bark's id
    int id;
    if ( _pubs.size() == 0 ) {
        id = 0;
    } else {
        id = _pubs.back()->getId() + 1;
    }

    // get time
    time_t t = time(0);

    // create bark
    Bark* bark = new Bark(id, t, _users[_currentUser], text);

    _pubs.push_back(bark);
    _users[_currentUser]->addPublication(bark);

    return true;
}

bool Manager::createRebark(int id, string text) {

    // check some user is logged in
    if ( _currentUser == -1 ) {
        // no user logged in, return empty vector
        return false;
    }

    // check publication exists, id is not out of bonds
    if ( (int) _pubs.size() < id ) {
        return false;
    }

    // get last id of publication list, add one to get this bark's id
    int id_new;
    if ( _pubs.back() == nullptr ) {
        id_new = 0;
    } else {
        id_new = _pubs.back()->getId() + 1;
    }

    // get time
    time_t t = time(0);

    // create rebark
    Rebark* rebark = new Rebark(id_new, t, _pubs[id], _users[_currentUser], text);

    _pubs.push_back(rebark);
    _users[_currentUser]->addPublication(rebark);

    return true;
}

bool Manager::createReply(int id, string text) {

    // check some user is logged in
    if ( _currentUser == -1 ) {
        // no user logged in, return empty vector
        return false;
    }

    // check publication exists, id is not out of bonds
    if ( (int) _pubs.size() < id ) {
        return false;
    }

    // get last id of publication list, add one to get this bark's id
    int id_new;
    if ( _pubs.back() == nullptr ) {
        id_new = 0;
    } else {
        id_new = _pubs.back()->getId() + 1;
    }

    // get time
    time_t t = time(0);

    // create rebark
    Reply* reply = new Reply(id_new, t, _pubs[id], _users[_currentUser], text);

    _pubs.push_back(reply);
    _users[_currentUser]->addPublication(reply);

    return true;
}

Manager::~Manager() {

    // delete each user in _users
    for (uint i = 0; i < _users.size(); i++ ) {
        delete _users[i];
    }

    // clear remaining references
    _users.clear();

    // delete each user in _users
    for (uint i = 0; i < _pubs.size(); i++ ) {
        delete _pubs[i];
    }

    // clear remaining references
    _pubs.clear();
}
