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

#ifndef DATABASE_H_INCLUDED
#define DATABASE_H_INCLUDED
#include <sqlite3.h>
#include <iostream>
#include <stdlib.h>

#include <ctype.h>
#include <stdio.h>

#include <limits.h>
#include <vector>

using namespace std;

class Ddatabase
{
private:
    int argc;
    char* argv[];
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    const char *sql;
    const char* data = "Callback function called";

    static int ival;

    static vector <string>uebergabe; // ID
    static vector <string>iuebergabe; // Titel
    static vector <string>puebergabe; // Punkte

public:

    Ddatabase() {  };

    static int Tcallback(void *data, int argc, char **argv, char **azColName)
    {
        int i;

        for(i=0; i<argc; i++)
        {
            cout << argv[i] << " ";
            // IDListe.push_back(argc);
        }
        cout << "\n";
        return 0;
    }

    static int callback(void *data, int argc, char **argv, char **azColName)
    {


        uebergabe.push_back(argv[0]); // HIER MÜSSTE DER FEHLER SEIN
        iuebergabe.push_back(argv[1]);
        puebergabe.push_back(argv[2]);
        return 0;
    }

    void get_liste()
    {
        for(unsigned int i=0; i < uebergabe.size(); i++) // HIER MÜSSTE DER FEHLER  SEIN
        {
            cout <<"SerienID = " << uebergabe[i] << "\nTitel = " << iuebergabe[i] << "\nPunkte = " << puebergabe[i] << "\n\n";
        }
    }

    static int Ccallback(void *data, int argc, char **argv, char **azColName)
    {
        ival = atoi(argv[0]);
        return 0;
    }

    static int get_count()
    {
        return ival;
    }


    void open_database()
    {


        FILE *datei;
        datei=fopen("test.db","r");
        if(datei == NULL)
            {

            rc = sqlite3_open("test.db", &db);
            if( rc )
            {
                cout << "Neu erstellte Datenbank kann nicht geöffnet werden: " << sqlite3_errmsg(db);
                rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
                if( rc != SQLITE_OK )
                {
                    cout << "SQL error: " << zErrMsg << "\n";
                    sqlite3_free(zErrMsg);
                }
            }
                    sql = "CREATE  TABLE 'main'.'Serien' ('SerienID' INTEGER PRIMARY KEY  NOT NULL , 'Titel' TEXT UNIQUE , 'Punkte' INTEGER)";
                    rc = sqlite3_exec(db, sql, Ccallback, (void*)data, &zErrMsg);
                    if( rc != SQLITE_OK )
                    {
                        cout << "SQL error: " << zErrMsg << "\n";
                        sqlite3_free(zErrMsg);
                    }
            } // if
        else
        {
            rc = sqlite3_open("test.db", &db);
            if( rc )
            {
                cout << "Datenbank kann nicht geöffnet werden: " << sqlite3_errmsg(db);
                rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
                if( rc != SQLITE_OK )
                {
                    cout << "SQL error: " << zErrMsg << "\n";
                    sqlite3_free(zErrMsg);
                }
            }
            fclose(datei);
        }
    } // open_database ende

    string titeleingabe(){
        string a;
        bool w = false;
        while(w == false){
            getline(cin,a);
            w = true;
            for(int i=0; i<a.size();i++){
                if(a[i] == '\''){
                    w = false;
                }
            }
            if(w == false){
                cout << "Bitte verwende keine --> ' <--\n";
            }

        }
        return a;
    }

    void select()
    {
        sql = "SELECT * from Serien WHERE Titel IS NOT NULL";

        uebergabe.clear();
        iuebergabe.clear();
        puebergabe.clear();


        /* Execute SQL statement */
        rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
        if( rc != SQLITE_OK )
        {
            cout << "SQL error: " << zErrMsg << "\n";
            sqlite3_free(zErrMsg);
        }

        get_liste();
    }

    void selectTitel()
    {
        sql = "SELECT SerienID, Titel FROM Serien WHERE Titel IS NOT NULL";

        /* Execute SQL statement */
        rc = sqlite3_exec(db, sql, Tcallback, (void*)data, &zErrMsg);
        if( rc != SQLITE_OK )
        {
            cout << "SQL error: " << zErrMsg << "\n";
            sqlite3_free(zErrMsg);
        }
    }

    void count()
    {
        sql = "SELECT count(*) FROM Serien";
        /* Execute SQL statement */
        rc = sqlite3_exec(db, sql, Ccallback, (void*)data, &zErrMsg);
        if( rc != SQLITE_OK )
        {
            cout << "SQL error: " << zErrMsg << "\n";
            sqlite3_free(zErrMsg);
        }
    }

    char* punkteingabe()
    {

        int key=0;

        while(key==0)
        {

            string e;
            int p;

           // cin >> e;
            getline(cin,e);
            char c[e.size()];

            for(unsigned int i=0; i<sizeof(c); i++)
            {
                if(isdigit(e[i]))
                {
                    c[i] = e[i];
                }
                else
                {
                    key = 1;
                }
            }


            if(key == 1)
            {
                key = 0;
                cout << "\n\nNur Ganzzahlen bitte eingeben:\n\n";
                // cout << "\n" << key << "\n";
            }
            else
            {
                p = atoi (c);

                if(p<0 || p>10)
                {
                    cout << "\n\nBitte gib eine Zahl von 0 bis 10 ein:\n";
                }
                else
                {
                    key=1;
                    return c;
                }
            }
        }
    } // Punkteingabe Funktion

    void bearbeiten()
    {
        string eingabe;
        bool schalter = true;

        select();
        cout << "\n\n\n";

        cout << "Bitte gib eine passende Nr. ein\n";
        getline(cin,eingabe);
      //  cin >> eingabe;
        for(int i=0; i<eingabe.size(); i++)
        {
            if(isdigit(eingabe[i]))
            {
            }
            else
            {
                schalter = false;
            }
        }



        if(schalter == false)
        {
            cout << "Du hast keine Ganzzahlen eingegeben:";
        }
        else
        {
            const char *CC = eingabe.c_str();
            schalter = false;
            for(int i=0; i<uebergabe.size(); i++)
            {
                if(eingabe != uebergabe[i])
                {
                }
                else
                {
                    schalter = true;
                }
            }

            if(schalter == false)
            {
                cout << "Die Zahl steht nicht auf der Liste";
            }
            else
            {
                cout << "Willst du 1. Titel, 2. Punkte oder 3. beides bearbeiten?\n";
                string eingabe2;
                string eingabe3;
                string eingabe4;

             //   cin >> eingabe2;
                getline(cin,eingabe2);

                switch(eingabe2[0])
                {
                case '1':
                    cout << "Bitte gib den neuen Namen des Titels ein:\n";
                   // cin >> eingabe2;
                    //getline(cin,eingabe2);

                    eingabe3.append("UPDATE Serien SET Titel = '");
                    eingabe3.append(titeleingabe());
                    eingabe3.append("'WHERE SerienID =");
                    eingabe3.append(eingabe);

                    sql = eingabe3.c_str();


                    rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
                    if( rc != SQLITE_OK )
                    {
                        cout << "SQL error: " << zErrMsg << "\n";
                        sqlite3_free(zErrMsg);
                    }

//___

                    break;

                case '2':
                    cout << "Bitte gib die neue Anzahl der Punkte ein:\n";
                    eingabe2 = punkteingabe();


                    eingabe3.append("UPDATE Serien SET Punkte = ");
                    eingabe3.append(eingabe2);
                    eingabe3.append(" WHERE SerienID =");
                    eingabe3.append(eingabe);

                    sql = eingabe3.c_str();


                    rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
                    if( rc != SQLITE_OK )
                    {
                        cout << "SQL error: " << zErrMsg << "\n";
                        sqlite3_free(zErrMsg);
                    }

                    break;
                case '3':
                    cout << "Bitte gib den neuen Titel ein\n";
                  //  cin >> eingabe2;
                //    getline(cin,eingabe2);
                    eingabe3.append("UPDATE Serien Set Titel= '");
                    eingabe3.append(titeleingabe());
                    cout << "Bitte gib die neue Anzahl der Punkte ein:\n";
                    eingabe3.append("', Punkte =");
                    eingabe3.append(punkteingabe());
                    eingabe3.append(" WHERE SerienID =");
                    eingabe3.append(eingabe);

                    sql = eingabe3.c_str();


                    rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
                    if( rc != SQLITE_OK )
                    {
                        cout << "SQL error: " << zErrMsg << "\n";
                        sqlite3_free(zErrMsg);
                    }



                    // UPDATE Serien Set Titel= 'EEEE', Punkte = 3 WHERE SerienID = 3;
                    break;
                default:
                    cout << "Du hättest eine Ganzzahl von 1 bis 3 eingeben sollen.";
                    break;
                }
            }


        }




    } // Bearbeiten ende

    void insert()
    {

        count(); // ACHTUNG FUNKTION MIT DUMMEN NAMEN

        string temp;
        string Lstringeingabe;
        char anzahl[5];

        Lstringeingabe = "INSERT INTO Serien (SerienID,Titel,Punkte) VALUES(";

        sprintf(anzahl,"%i",ival+1);

        Lstringeingabe.append(anzahl);
        Lstringeingabe.append(",'");

        cout << "\nBitte gib den Namen der Serie ein:\n";


       // getline(std::cin, temp);
       // cin >> temp;
       // Lstringeingabe.append(temp);
       Lstringeingabe.append(titeleingabe());
        Lstringeingabe.append("',");

        cout << "Und nun die Anzahl der Punkte bitte:\n";

        Lstringeingabe.append(punkteingabe());
        Lstringeingabe.append(")");

        //sql = jan(Lstringeingabe);
        sql = Lstringeingabe.c_str();

        rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
        if( rc != SQLITE_OK )
        {
            cout << "SQL Fehler: "  << zErrMsg;
            sqlite3_free(zErrMsg);
        }
        else
        {
            cout << "Records created successfully" << endl;
        }


    }

    void loeschen()
    {
        count();
        // int anzahl = get_count();
        bool schalter = true;
        int ergebnis = 0;

        string eingabe;
        // cin >> eingabe;
        getline(cin,eingabe);



        for(int i=0; i<eingabe.size(); i++)
        {
            if(isdigit(eingabe[i]))
            {

            }
            else
            {
                schalter = false;
                break;
            }
        }

        if(schalter == false)
        {
            cout << "Du hast keine Ganzzahl eingeben.";
        }
        else
        {
            const char *CCeingabe = eingabe.c_str();
            ergebnis = atoi(CCeingabe);
            if(ergebnis >= 1 && ergebnis <= get_count())
            {

                eingabe = "UPDATE Serien Set Titel = null, Punkte = null WHERE SerienID =";

                char anzahl[5];
                sprintf(anzahl,"%i",ergebnis);


                eingabe.append(anzahl);

                CCeingabe = eingabe.c_str();
                sql = CCeingabe;

                // cout << "\nSQL: " << sql;

                rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
                if( rc != SQLITE_OK )
                {
                    cout << "SQL error: " << zErrMsg << "\n";
                    sqlite3_free(zErrMsg);
                }


            }
            else
            {
                cout << "Bitte gib eine Zahl von der Liste ein.";
            }


        }

    }


};



#endif // DATABASE_H_INCLUDED
