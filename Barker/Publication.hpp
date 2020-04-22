/**
* Proyecto Informatica Industrial
* Grupo 9
* Esther Alonso Pinillos, Roberto Uceda Gomez
*
* Archivo de cabecera: Publication
*
**/
#include <iostream>
#include <vector>



#ifndef PUBLICATION_HPP
#define PUBLICATION_HPP
#include "PublicUserData.hpp"

class Publication{
protected:
    int _id;
    ulong _time;
    PublicUserData* _user;

public:
    Publication(int id, ulong time, PublicUserData* user);
    int getId();
    ulong getTime();
    PublicUserData* getUser();
    void setId(int id);
    void setTime(ulong time);
    void setUser(PublicUserData* user);
    virtual string getBark()=0;

};

#endif
