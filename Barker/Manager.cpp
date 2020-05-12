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

//auxiliary function to sort Timeline, gets time from Timeline Publications
bool Manager::compByTime(Publication* a,Publication* b) {
    return a->getTime() < b->getTime();
}

int Manager::searchPub(int id) {
    int pos = -1; // position in _pubs for pub with id, -1 if not found
    for ( int i = 0; i < (int) _pubs.size(); i++ ) {
        if ( _pubs[i]->getId() == id ){
            pos = i;
            break; // no need to keep searching
        }
    }

    return pos;
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

    vector<PublicUserData*> pud; // pud == PublicUserData vector
    // cast every element of _users to PublicUserData*, append to vector
    for (uint i = 0; i < _users.size(); i++ ) {
        pud.push_back( (PublicUserData*) _users[i] );
    }

    return pud;
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
            deletePublication( _users[_currentUser]->getPublications()[i]->getId() );
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
    //sort vector timeline in chronological order
    sort (timeline.begin(),timeline.end(), compByTime);

    // return vector
    return timeline;

}

bool Manager::createBark(string text) {

    // check some user is logged in
    if ( _currentUser == -1 ) {
        // no user logged in, return false
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
    ulong t = time(0);

    // create bark
    Bark* bark = new Bark(id, t, _users[_currentUser], text);

    _pubs.push_back(bark);
    _users[_currentUser]->addPublication(bark);

    return true;
}

bool Manager::createRebark(int id, string text) {

    // check some user is logged in
    if ( _currentUser == -1 ) {
        // no user logged in, return false
        return false;
    }

    // check publication exists, id is not out of bonds
    int pos;
    pos = searchPub(id);
    if ( pos == -1 ) {
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
    ulong t = time(0);

    // create rebark
    Rebark* rebark = new Rebark(id_new, t, _pubs[id], _users[_currentUser], text);

    _pubs.push_back(rebark);
    _users[_currentUser]->addPublication(rebark);

    return true;
}

bool Manager::createReply(int id, string text) {

    // check some user is logged in
    if ( _currentUser == -1 ) {
        // no user logged in, return false
        return false;
    }

    // check publication exists, id is not out of bonds
    int pos;
    pos = searchPub(id);
    if ( pos == -1 ) {
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
    ulong t = time(0);

    // create rebark
    Reply* reply = new Reply(id_new, t, _pubs[id], _users[_currentUser], text);

    _pubs.push_back(reply);
    _users[_currentUser]->addPublication(reply);

    return true;
}

bool Manager::deletePublication(int id) {

    // find position in _pubs for publication with id,
    int pos;
    pos = searchPub(id);

    if ( pos == -1 ){
        return false;
    }

    // if publication is a bark, check if it has references and delete them
    if ( _pubs[id]->getType() == 0 ) {
        Bark* b = dynamic_cast<Bark*>( _pubs[id] );
        for ( int i = 0; i < (int) b->getRep().size(); i++ ) {
            deletePublication( b->getRep()[i]->getId() ); // recursive fun here
        }
    }

    // remove pointer in _pubs
    _pubs.erase( _pubs.begin() + id );

    // remove pointer in owner user
    _pubs[id]->getUser()->removePublication(id);

    return true;
}

bool Manager::saveToFile(string path) {

    ofstream f(path);

    for ( int i = 0; i < (int) _users.size(); i++ ) {
        f << "#" << endl;
        f << _users[i]->getEmail() << endl;
        f << _users[i]->getPassword() << endl;
        f << _users[i]->getUsername() << endl;
        f << _users[i]->getBio() << endl;
        f << _users[i]->getFollowers() << endl;
        f << "following:" << endl;
        for ( int j = 0; j < (int) _users[i]->getFollowing().size(); j++ ) {
            f << _users[i]->getFollowing()[j]->getUsername() << endl;
        }
        f << "publications:" << endl;
        for ( int j = 0; j < (int) _users[i]->getPublications().size(); j++ ) {
            f << _users[i]->getPublications()[j]->getId() << endl;
        }
        f << "#" << endl;
    }

    for ( int i = 0; i < (int) _pubs.size(); i++ ) {

        if ( _pubs[i]->getType() == 0 ) { // it's a bark
            f << "$Bark" << endl;
        } else if ( _pubs[i]->getType() == 1 ) { // it's a rebark
            f << "$Rebark" << endl;
        } else {
            f << "$Reply" << endl;
        }

        f << _pubs[i]->getId() << endl;
        f << _pubs[i]->getTime() << endl;

        if ( _pubs[i]->getType() == 1 ) {
            Rebark* r = dynamic_cast<Rebark*>(_pubs[i]); // downcast the Publication* to Rebark
            f << r->getPublication()->getId() << endl;

        } else if ( _pubs[i]->getType() == 2 ) {
            Reply* r = dynamic_cast<Reply*>(_pubs[i]); // downcast the Publication* to Reply
            f << r->getPublication()->getId() << endl;
        }

        f << _pubs[i]->getUser()->getUsername() << endl;
        f << _pubs[i]->getText() << endl;
    }

    f.close();

    return true;

}

bool Manager::loadFromFile(string path) {

    ifstream f; // input stream file
    f.open(path); // open as plain text

    // auxiliary line
    string line;

    // user properties
    string email;
    string password;
    string username;
    string bio;
    int followers;
    vector<string> following; // store following by username
    vector<int> publications; // store publications by id

    // publication properties
    int id;
    time_t time;
    PublicUserData* pub_username;
    string text;
    Publication* orig_pub;

    if ( f.fail() ) {
        return false; // if there were errors opening the file, quit
    }

    // create users, publications
    while ( getline(f, line) ) {

        if( line == "#" ) { // user starts or ends

             getline(f, email);
             getline(f, password);
             getline(f, username);
             getline(f, bio);
             getline(f, line); // can't get a int from a str
             followers = stoi(line); // cast to store as int
             getline(f, line);
             if ( line != "following:" ) { // there should be a 'following:' in here always
                 return false;
             }
             while ( getline(f, line) && line != "publications:" ) {
                 following.push_back(line); // store following
             } // this ends when line == publications
             while ( getline(f, line) && line != "#" ) {
                 publications.push_back(stoi(line));
             } // this ends when line == #, so on to the next object

             // create user

             createUser(email, password, username, bio); // now the user is stored in manager

             // clean remains
             email = "";
             password = "";
             username = "";
             bio = "";
             followers = 0;
             following.clear();
             publications.clear();

             // on to the next thing, no need to evaluate following code
             continue;

        } else if ( line == "$Bark" ) {

            getline(f, line);
            id = stoi(line); // need to cast line to int
            getline(f, line);
            time = stol(line);
            getline(f, line);
            pub_username = _users[ searchUser(line, "username") ];
            getline(f, text);

            // create bark
            Bark* bark = new Bark(id, time, pub_username, text);
            _pubs.push_back(bark); // trust that barks where saved in order on file!

            // clean remains
            id = 0;
            time = 0;
            pub_username = nullptr;
            text = "";

            // on to the next thing, no need to evaluate following code
            continue;

        } else if ( line == "$Rebark" ) {

            getline(f, line);
            id = stoi(line); // need to cast line to int
            getline(f, line);
            time = stol(line);
            getline(f, line);
            orig_pub = _pubs[stoi(line)];
            getline(f, line);
            pub_username = _users[ searchUser(line, "username") ];
            getline(f, text);

            // create bark
            Rebark* rebark = new Rebark(id, time, orig_pub, pub_username, text);
            _pubs.push_back(rebark); // trust that barks where saved in order on file!

            // clean remains
            id = 0;
            time = 0;
            pub_username = nullptr;
            text = "";
            orig_pub = nullptr;

            // on to the next thing, no need to evaluate following code
            continue;

        } else if ( line == "$Reply" ) {

            getline(f, line);
            id = stoi(line); // need to cast line to int
            getline(f, line);
            time = stol(line);
            getline(f, line);
            orig_pub = _pubs[stoi(line)];
            getline(f, line);
            pub_username = _users[ searchUser(line, "username") ];
            getline(f, text);

            // create bark
            Reply* reply = new Reply(id, time, orig_pub, pub_username, text);
            _pubs.push_back(reply); // trust that barks where saved in order on file!

            // clean remains
            id = 0;
            time = 0;
            pub_username = nullptr;
            text = "";
            orig_pub = nullptr;

            // on to the next thing, no need to evaluate following code
            continue;

        }

    }

    // all objects created, now need to make follows between users

    f.clear(); // reset flags (EOF)
    f.seekg(0); // reset position in file to beginning
    int uid;

    // iterate again whole file to find followers and publications per user, and make the links
    while ( getline(f, line) ) {

        if( line == "#" ) { // user starts or ends

             getline(f, email);
             getline(f, password);
             getline(f, username);
             getline(f, bio);
             getline(f, line); // can't get a int from a str
             followers = stoi(line); // cast to store as int
             getline(f, line);

             if ( line != "following:" ) { // there should be a 'following:' in here always
                 return false;
             }

             while ( getline(f, line) && line != "publications:" ) {
                 following.push_back(line); // store following
             } // this ends when line == publications

             while ( getline(f, line) && line != "#" ) {
                 publications.push_back(stoi(line));
             } // this ends when line == #, so on to the next object

             // setup followers
             uid = searchUser(username, "username");
             for ( int i = 0; i < (int) following.size(); i++ ) {
                _users[uid]->follow( _users[ searchUser(following[i], "username") ]);
                _users[ searchUser(following[i], "username") ]->increaseFollowers();
             }

             // setup publications
             for ( int i = 0; i < (int) publications.size(); i++ ) {
                 _users[uid]->addPublication( _pubs[ publications[i] ] );
             }

             // clean remains
             email = "";
             password = "";
             username = "";
             bio = "";
             followers = 0;
             following.clear();
             publications.clear();

             // on to the next user, no need to evaluate following code
             continue;

        } else if ( line == "$Bark" || line == "$Rebark" || line == "$Reply" ) {
            break; // we finished all users, so no need to keep reading file
        }

    }

    // all done!
    return true;
}

Manager::~Manager() {

    // delete each user in _users
    for (uint i = 0; i < _users.size(); i++ ) {
        delete _users[i];
    }

    // clear remaining references
    _users.clear();

    // delete each publication in _pubs
    for (uint i = 0; i < _pubs.size(); i++ ) {
        delete _pubs[i];
    }

    // clear remaining references
    _pubs.clear();
}
