/**
* Proyecto Informatica Industrial
* Grupo 9
* Esther Alonso Pinillos, Roberto Uceda Gomez
*
* Implementacion de metodos de clase:Rebark
*
**/
#include "Rebark.hpp"
Rebark::Rebark(int id, ulong time, Publication* publication, PublicUserData* user, string text):Publication(id, time,  user){
    _text=text;
    _publication = publication;
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

void Rebark::setPublication(Publication* publication){
    _publication=publication;
}

string Rebark::getBark(){
    return _user->getUsername()+" rebarked - "+to_string(_time)+":\n"+_text+"\n***\n"+ _publication->getBark()+"\n***";
}

int Rebark::getType() {
    return _type;
}

Rebark::~Rebark() {}
