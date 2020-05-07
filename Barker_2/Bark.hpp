/**
* Proyecto Informatica Industrial
* Grupo 9
* Esther Alonso Pinillos, Roberto Uceda Gomez
*
* Archivo de cabecera: Bark
*
**/

#include <iostream>

#ifndef BARK_HPP
#define BARK_HPP

#include "PublicUserData.hpp"
#include "Publication.hpp"

class Bark: public Publication{
private:
    string _text;

public:
    Bark(int id, ulong time, PublicUserData* user, string text);
    void setText(string text);
    string getText();
    string getBark();
    int getType();
    ~Bark();

};

#endif
