/**
* Proyecto Informatica Industrial
* Grupo 9
* Esther Alonso Pinillos, Roberto Uceda Gomez
*
* Implementacion de metodos de clase: PublicUserData
*
**/

#include "PublicUserData.hpp"

PublicUserData::PublicUserData(string username, string bio) {
    _username = username;
    _bio = bio;
    _followers = 0;
}

string PublicUserData::getUsername() {
    return _username;
}

string PublicUserData::getBio() {
    return _bio;
}

void PublicUserData::setUsername(string newUsername) {
    _username = newUsername;
}

void PublicUserData::setBio(string newBio) {
    _bio = newBio;
}

uint PublicUserData::getFollowers() {
    return _followers;
}

void PublicUserData::increaseFollowers() {
    _followers++;
}

void PublicUserData::decreaseFollowers() {
    if( (_followers) <= 1 ){
        _followers = 0;
    } else {
        _followers--;
    }
}

vector<PublicUserData*> PublicUserData::getFollowing() {
    return _following;
}

//vector<Publication*> PublicUserData::getPublications() {
//    return _publications;
//}

bool PublicUserData::follow(PublicUserData* user) {

    for (uint i = 0; i < _following.size(); i++ ) {
        if ( _following[i] == user ) {
            return false;
        }
    }
    _following.push_back(user);

    return true;
}

bool PublicUserData::unfollow(PublicUserData* user) {

    for (uint i = 0; i < _following.size(); i++ ) {
        if ( _following[i] == user ) {
            _following.erase(_following.begin()+i);
            return true;
        }
    }

    return false;
}
//bool PublicUserData::addPublication(Publication* user) {

//    for (uint i = 0; i < _publication.size(); i++ ) {
//        if ( _publication[i] == user ) {
//            return false;
//        }
//    }
//    _following.push_back(user);

//    return true;
//}
//bool removePublication(int id);

//PublicUserData::~PublicUserData() {}
