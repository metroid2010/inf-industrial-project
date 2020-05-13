/**
* Proyecto Informatica Industrial
* Grupo 9
* Esther Alonso Pinillos, Roberto Uceda Gomez
*
* main.cpp
* por ahora, placeholder
*
**/

#include <iostream>
#include "Manager.hpp"
#include "User.hpp"
#include "Publication.hpp"
#include "Bark.hpp"
#include "Rebark.hpp"
#include "Reply.hpp"
#include "Interface.hpp"

using namespace std;


void populateManager(Manager* m);

int main() {


    Manager* m = new Manager();
    Interface* i = new Interface(m);

    // populate m with fake data, shamelessly copied from tests
    populateManager(m);


    cout << "Starting Barker..." << endl;

    i->startInterface();

    cout << "Deleting objects and exiting" << endl;

    delete i;
    delete m;

    return 0;

}

void populateManager(Manager* m) {

    // populate Manager with data
    std::string text1, text2, text3, text4, text5;
    std::string bark_text, rebark_text, reply_text;
    std::string email1, password1, name1, bio1;
    std::string email2, password2, name2, bio2;
    std::string email3, password3, name3, bio3;

    text1 = "This is my first bark. Hello, world!";
    text2 = "This guy is hilarious";
    text3 = "You don't have a clue of what you're saying";
    text4 = "It's difficult to come up with a cool bark";
    text5 = "Hey yo!";

    //-- Define test users
    email1 = "email@domain.com";
    password1 = "1234";
    name1 = "coolGuy98";
    bio1 = "I'm just a random guy living my life";

    email2 = "otheremail@domain.com";
    password2 = "user2pass";
    name2 = "user2";
    bio2 = "Second user of Barker";

    email3 = "fakeemail@domain.com";
    password3 = "user3pass";
    name3 = "user3";
    bio3 = "Third user of Barker";

    m->createUser(email1, password1, name1, bio1);
    m->createUser(email2, password2, name2, bio2);
    m->createUser(email3, password3, name3, bio3);

    m->login(email1, password1);
    m->createBark(text1);
    std::vector<Publication *> pubs = m->getCurrentUser()->getPublications();
    int id = pubs[0]->getId();
    m->logout();
    m->login(email2, password2);
    m->createRebark(id, text2);
    m->createBark(text4);
    m->followUser(name1);
    m->logout();
    m->login(email3, password3);
    m->createBark(text5);
    m->createReply(id, text3);
    m->followUser(name1);
    m->followUser(name2);
    m->logout();

    return;
}
