/**
* Proyecto Informatica Industrial
* Grupo 9
* Esther Alonso Pinillos, Roberto Uceda Gomez
*
* Archivo de cabecera: Publication
*
**/

#ifndef PUBLICATION_HPP
#define PUBLICATION_HPP

#include <iostream>
#include <vector>
//#include "PublicUserData.hpp"

using namespace std;

class PublicUserData;

class Publication{

protected:
    int _id;
    ulong _time;
    PublicUserData* _user;
    int _type;
    vector<Publication*> _rep; // replies or rebarks that point to this bark

public:
    Publication(int id, ulong time, PublicUserData* user);
    int getId();
    ulong getTime();
    PublicUserData* getUser();
    void setId(int id);
    void setTime(ulong time);
    void setUser(PublicUserData* user);
    virtual string getText()=0;
    virtual int getType()=0;
    virtual string getBark()=0;
    virtual string getBarkPretty()=0;
    virtual vector<Publication*> getRep()=0;
    virtual void setRep(Publication* rep)=0;
    virtual ~Publication();

};

#endif
