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
    // check to avoid _followers being lower than zero
    if( (_followers) <= 1 ){
        _followers = 0;
    } else {
        _followers--;
    }
}

vector<PublicUserData*> PublicUserData::getFollowing() {
    return _following;
}


vector<Publication*> PublicUserData::getPublications() {
    return _publications;
}

bool PublicUserData::follow(PublicUserData* user) {

    for ( uint i = 0; i < _following.size(); i++ ) {
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


bool PublicUserData::addPublication(Publication* pub) {

    // check the publication is not included already
    for (uint i = 0; i < _publications.size(); i++ ) {
        if ( _publications[i] == pub ) {
            return false;
        }
    }

    // check publication is not owned by another user
    if ( pub->getUser() != this ) {
        return false;
    }

    // add publication if it is not already in list
    _publications.push_back(pub);

    return true;
}

bool PublicUserData::removePublication(int id) {

    // find the position in _publication that
    // corresponds to given ID
    for ( int i = 0; i < (int) _publications.size(); i++ ) {
        if ( _publications[i]->getId() == id ) {

            // delete object publication
            //delete _publications[id] // won't pass test

            // delete pointer to publication
            _publications.erase( _publications.begin() + i );

            return true;
        }
    }

    // publication with ID not found for this user
    return false;
}

PublicUserData::~PublicUserData() {}
