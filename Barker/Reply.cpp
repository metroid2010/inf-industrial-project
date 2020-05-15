/**
* Proyecto Informatica Industrial
* Grupo 9
* Esther Alonso Pinillos, Roberto Uceda Gomez
*
* Implementacion de metodos de clase: Replay
*
**/

#include "Reply.hpp"
#include "Bark.hpp"

Reply::Reply(int id, ulong time, Publication* publication, PublicUserData* user, string text):Publication(id, time,  user){
    _text=text;
    setPublication(publication );
    _type=2;


}

string Reply::getText(){
    return _text;
}

void Reply::setText(string text){
    _text=text;
}

Publication* Reply::getPublication(){
    return _publication;
}

void Reply::setPublication(Publication* publication){
    _publication=publication;
    dynamic_cast<Bark*>(_publication)->setRep(this); // downcast Publication* to Bark*
}

string Reply::getBark(){
    return _user->getUsername()+" replied - "+to_string(_time)+":\n===\n"+ _publication->getBark()+"\n===\n"+_text;
}

string Reply::getBarkPretty(){
    struct tm* timePretty = localtime((long*) &_time);
    return _user->getUsername()+" replied - "+ asctime(timePretty) +":" + "\n===\n"+ _publication->getBarkPretty()+"\n===\n"+_text;
}

int Reply::getType() {
    return _type;
}

Reply::~Reply() {}

