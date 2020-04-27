/**
* Proyecto Informatica Industrial
* Grupo 9
* Esther Alonso Pinillos, Roberto Uceda Gomez
*
* Archivo de cabecera: PublicUserData.hpp
*
**/

#include <iostream>
#include <vector>
#include "Publication.hpp"

#ifndef PUBLICUSERDATA_HPP
#define PUBLICUSERDATA_HPP

using namespace std;

class PublicUserData {

protected:
    string _username;
    string _bio;
    uint _followers;
    vector<PublicUserData*> _following;
    //vector<Publication*> _publications;
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
    //vector<Publication*> getPublications(); // para entregas posteriores
    bool follow(PublicUserData* user);
    bool unfollow(PublicUserData* user);
    //bool addPublication(Publication* user); // para entregas posteriores
    bool removePublication(int id);
//    ~PublicUserData(); // no necesario por ahora

};

#endif
