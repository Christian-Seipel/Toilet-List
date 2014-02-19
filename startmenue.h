/*
Toilet List Version 0.01B
Author: Christian Seipel c.seipel@gmx.de

Copyright 2014 Christian Seipel

This file is part of Toilet List.

Toilet List is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Toilet List is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Toilet List.  If not, see <http://www.gnu.org/licenses/>.

*/
// bla bla test tes

#ifndef STARTMENUE_H_INCLUDED
#define STARTMENUE_H_INCLUDED

#include <iostream>
#include <string>

#include "database.h"


/* Für die Eingabe von nur einen Zeichen [X1] */
#include <stdio.h>
#include <string.h>

using namespace std;

#include "menue.h"


class startmenue : public menue
{
private:
    Ddatabase *dl;
public:

    startmenue(Ddatabase *A)
    {
        dl = A;
    };
    ~startmenue() {};


    void menue_anzeigen()
    {
        cout << "\n1. Liste anzeigen\n2. Neue Serie eintragen\n3. Tabelle bearbeiten\n4. Serie Löschen\n5. Exit\n\n";
    };

    bool menue_eingabe()
    {



        string eingabe;
        cin >> eingabe;
        cout << endl;
        if(eingabe[0] == '1' || eingabe[0] == '2' || eingabe[0] == '3' ||eingabe[0] == '4' || eingabe[0] == '5')
        {
            switch(eingabe[0])
            {
            case '1':
                dl->select();
                break;

            case '2':
                dl->insert();
                break;
            case '3':
                dl->bearbeiten();
                break;
            case '4':
                cout << "\n------------------------------\nWähle bitte eine Serie über die Zahl links von der Serie zum löschen aus.\nFalls du keine Serie löschen willst gib einfach keine passende Zahl ein.\n------------------------------\n";
                dl->selectTitel();
                dl->loeschen();
                // Tabelle löschen muss noch bearbeitet werden
                break;
            case '5':
                return true;
                break;
            default:
                cout << "Gib bitte eine Ganzzahl von 1 bis 5 ein\n";
            }

        }
        else
        {
            cout << "Bitte gib eine Zahl von 1 bis 5 ein und nur das erste Zeichen wird gewertet!!!";
        }


    } // ENDE menue_eingabe()


};

#endif // STARTMENUE_H_INCLUDED
