/**
* Proyecto Informatica Industrial
* Grupo 9
* Esther Alonso Pinillos, Roberto Uceda Gomez
*
* Implementacion de metodos de clase:Rebark
*
**/
#include "Rebark.hpp"
#include "Bark.hpp"

Rebark::Rebark(int id, ulong time, Publication* publication, PublicUserData* user, string text):Publication(id, time,  user){
    _text=text;
    setPublication(publication);
    _type=1;
}

string Rebark::getText(){
    return _text;
}

void Rebark::setText(string text){
    _text=text;
}

Publication* Rebark::getPublication(){
    return _publication;
}

void Rebark::setRep(Publication *rep) {
    _rep.push_back(rep);
}

vector<Publication*> Rebark::getRep(){
    return _rep;
}

void Rebark::setPublication(Publication* publication){
    _publication=publication;
    _publication->setRep(this); // link to original publication
}

string Rebark::getBark(){
    return _user->getUsername()+" rebarked - "+to_string(_time)+":\n"+_text+"\n***\n"+ _publication->getBark()+"\n***";
}

string Rebark::getBarkPretty(){
    struct tm* timePretty = localtime((long*) &_time);
    return _user->getUsername()+" rebarked - "+ asctime(timePretty) +":" + "\n"+_text+"\n***\n"+ _publication->getBarkPretty()+"\n***";
}

int Rebark::getType() {
    return _type;
}

Rebark::~Rebark() {}
