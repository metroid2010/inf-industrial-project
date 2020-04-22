/**
* Proyecto Informatica Industrial
* Grupo 9
* Esther Alonso Pinillos, Roberto Uceda Gomez
*
* Implementacion de metodos de clase: Replay
*
**/

#include "Reply.hpp"
Reply::Reply(int id, ulong time, Publication* publication, PublicUserData* user, string text):Publication(id, time,  user){
    _text=text;
    _publication = publication;

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
}

string Reply::getBark(){
    return _user->getUsername()+" replied - "+to_string(_time)+":\n===\n"+ _publication->getBark()+"\n===\n"+_text;
}

