/**
* Proyecto Informatica Industrial
* Grupo 9
* Esther Alonso Pinillos, Roberto Uceda Gomez
*
* Implementacion de metodos de clase:Bark
*
**/
#include"Bark.hpp"

Bark::Bark(int id, ulong time, PublicUserData* user, string text):Publication(id, time,  user){
    _text=text;
}

string Bark::getText(){
    return _text;
}

void Bark::setText(string text){
    _text=text;
}

string Bark::getBark(){
    return _user->getUsername()+" - "+to_string(_time)+":\n"+_text;
}
