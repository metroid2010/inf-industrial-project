/**
* Proyecto Informatica Industrial
* Grupo 9
* Esther Alonso Pinillos, Roberto Uceda Gomez
*
* main.cpp
* por ahora, placeholder
*
**/

#include <iostream>
#include "Manager.hpp"
#include "User.hpp"
#include "Publication.hpp"
#include "Bark.hpp"
#include "Rebark.hpp"
#include "Reply.hpp"
#include "Interface.hpp"

using namespace std;

int main() {


    Manager* m = new Manager();
    Interface* i = new Interface(m);

    cout << "Starting Barker..." << endl;

    i->startInterface();

    cout << "Deleting objects and exiting" << endl;

    delete i;
    delete m;

    return 0;

}
