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



#ifndef HELP_H_INCLUDED
#define HELP_H_INCLUDED

#include <iostream>
using namespace std;


class help
{
private:
    bool schalter = true;
    string h = "help";
    string hh = "Help";
public:

    help(int &i, char *a[])
    {
        if(i == 2)
        {
            if(a[1] == h || a[1] == hh)
            {
                cout << "\nHelp überprüfung ist erfolgreich abgelaufen\n";
                schalter = false;
            }
            else
            {
                cout << "\nVersuchs mal mit help oder Help ;-)";
            }
        }
    };

    int rueckzug()
    {
        if(schalter == false)
        {
            return 1;
        }
    }
};


#endif // HELP_H_INCLUDED
