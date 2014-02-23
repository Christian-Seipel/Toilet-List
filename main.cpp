/*
Toilet List Version 0.01.004.1B
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


#include <iostream>
#include <string>
#include <vector>

#include "database.h"
#include "startmenue.h"
#include "help.h"

using namespace std;

int Ddatabase::ival=0;
vector <string> Ddatabase::uebergabe;
vector <string> Ddatabase::iuebergabe;
vector <string>Ddatabase::puebergabe;


int main(int argc, char* argv[])
{
 /*
    help hilfe(argc,argv);
    if(hilfe.rueckzug() == 1)
    {
        return 1;
    }; */

    Ddatabase anime;
    anime.open_database();

    startmenue start(&anime);
    bool theend = false;
    while(theend == false)
    {
        start.menue_anzeigen();
        theend = start.menue_eingabe();
    }
    return 0;

}
