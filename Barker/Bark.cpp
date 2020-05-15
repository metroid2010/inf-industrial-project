/**
* Proyecto Informatica Industrial
* Grupo 9
* Esther Alonso Pinillos, Roberto Uceda Gomez
*
* Implementacion de metodos de clase: Bark
*
**/

#include "Bark.hpp"

Bark::Bark(int id, ulong time, PublicUserData* user, string text):Publication(id, time,  user){
    _text=text;
    _type=0;
}

string Bark::getText(){
    return _text;
}

void Bark::setText(string text){
    _text=text;
}

void Bark::setRep(Publication *rep) {
    _rep.push_back(rep);
}

vector<Publication*> Bark::getRep(){
    return _rep;
}

string Bark::getBark(){
    return _user->getUsername()+" - "+to_string(_time)+":\n"+_text;
}

string Bark::getBarkPretty(){
    struct tm* timePretty = localtime((long*) &_time);
    return _user->getUsername()+" - "+ asctime(timePretty) +":" +"\n"+_text;
}

int Bark::getType() {
    return _type;
}

Bark::~Bark() {}
