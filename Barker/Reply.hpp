/**
* Proyecto Informatica Industrial
* Grupo 9
* Esther Alonso Pinillos, Roberto Uceda Gomez
*
* Archivo de cabecera:Replay
*
**/

#ifndef REPLY_HPP
#define REPLY_HPP

#include "PublicUserData.hpp"
#include "Publication.hpp"

class Reply: public Publication{

private:
    string _text;
    Publication *_publication;
    int _type = 2;

public:
    Reply(int id, ulong time, Publication* publication, PublicUserData* user, string text);
    void setText(string text);
    string getText();
    void setPublication(Publication* publication);
    Publication* getPublication();
    string getBark();
    string getBarkPretty();
    int getType();
    void setRep(Publication* rep);
    vector<Publication*> getRep();
    ~Reply();

};
#endif
