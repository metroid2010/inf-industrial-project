/**
* Proyecto Informatica Industrial
* Grupo 9
* Esther Alonso Pinillos, Roberto Uceda Gomez
*
* Implementacion de metodos de clase: Publication
*
**/
#include "Publication.hpp"
Publication::Publication(int id, ulong time, PublicUserData* user){
    _id=id;
    _time=time;
    _user=user;
}

int Publication::getId(){
    return _id;
}

ulong Publication::getTime(){
    return _time;
}

PublicUserData* Publication::getUser(){
    return _user;
}

void Publication::setId(int id){
    _id=id;
}
void Publication::setTime(ulong time){
    _time=time;
}

void Publication::setUser(PublicUserData* user){
    _user=user;
}




