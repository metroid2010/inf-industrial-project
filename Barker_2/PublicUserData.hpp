/**
* Proyecto Informatica Industrial
* Grupo 9
* Esther Alonso Pinillos, Roberto Uceda Gomez
*
* Archivo de cabecera: PublicUserData.hpp
*
**/



#ifndef PUBLICUSERDATA_HPP
#define PUBLICUSERDATA_HPP

#include <iostream>
#include <vector>
#include "Publication.hpp"

using namespace std;

//class Publication; // forward declaration to prevent mutual inclusion

class PublicUserData {

protected:
    string _username;
    string _bio;
    uint _followers;
    vector<PublicUserData*> _following;
    vector<Publication*> _publications;
    PublicUserData(string username, string bio);

private:
    PublicUserData();

public:
    string getUsername();
    string getBio();
    void setUsername(string newUsername);
    void setBio(string newBio);
    uint getFollowers();
    void increaseFollowers();
    void decreaseFollowers();
    vector<PublicUserData*> getFollowing();
    vector<Publication*> getPublications();
    bool addPublication(Publication* pub);
    bool removePublication(int id);
    bool follow(PublicUserData* user);
    bool unfollow(PublicUserData* user);
    ~PublicUserData();

};

#endif
