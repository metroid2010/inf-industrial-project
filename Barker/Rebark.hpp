/**
* Proyecto Informatica Industrial
* Grupo 9
* Esther Alonso Pinillos, Roberto Uceda Gomez
*
* Archivo de cabecera:Rebark
*
**/

#ifndef REBARK_HPP
#define REBARK_HPP
#include "PublicUserData.hpp"
#include "Publication.hpp"
class Rebark: public Publication{
private:
    string _text;
    Publication *_publication;
    int _type = 1;

public:
    Rebark(int id, ulong time, Publication* publication, PublicUserData* user, string text);
    void setText(string text);
    string getText();
    void setPublication(Publication* publication);
    Publication* getPublication();
    string getBark();
    string getBarkPretty();
    int getType();
    ~Rebark();

};
#endif
