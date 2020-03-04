// hierarchial inheritance.cpp
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <sstream>
#include <bits/stdc++.h>

using namespace std;
void menu();
int maping(string MAP);
int zmiana_wezla();
void dirA();
void dirB();
void dirC();
void dirD();

/*
std::string split implementation by using delimeter as an another string
*/
std::vector<std::string> split(std::string stringToBeSplitted, std::string delimeter)
{
	std::vector<std::string> splittedString;
	int startIndex = 0;
	int  endIndex = 0;
	while( (endIndex = stringToBeSplitted.find(delimeter, startIndex)) < stringToBeSplitted.size() )
	{

		std::string val = stringToBeSplitted.substr(startIndex, endIndex - startIndex);
		splittedString.push_back(val);
		startIndex = endIndex + delimeter.size();

	}
	if(startIndex < stringToBeSplitted.size())
	{
		std::string val = stringToBeSplitted.substr(startIndex);
		splittedString.push_back(val);
	}
	return splittedString;

}


//konwersja nazw klasow na litery ze struktury
string a="statek", b="nadwodny", c="podwodny", d="powietrzny", e="zaglowiec", f ="okret", g ="batyskaf", h ="balon", i ="samolot";

int matrix[9][9]={0};
/*matrix for movement on struct
0-no incedense
1-up -> down
2-down -> up
3-lisc could have objects
*/

//LEVEL 0


class statek //single base class
{
public:
    int masa, dlugosc, gps;
    char nazwa[10];
    int x,y;

    int zmiana_wezla(string goTo)
    {
        if((goTo == "cd..")||(goTo == "CD.."))
        {
            return 0;
        }
        else
        {
            int pole=1;




                std::string str = goTo;

                // Spliting the string by an another std::string
                std::vector<std::string> goTO = split(str, ".");
                int tab[goTO.size()]={0};//tabel to check if string exist
                int tab1[goTO.size()]={0};

    /*TEST of string input split
                for(int j = 1; j < goTO.size() ; j++)
                {
                    cout<<"goTO["<<j<<"] = "<<goTO[j]<<endl;//test
                }
*/

                for(int j = 1; j < goTO.size() ; j++)
                {
                    if(goTO[j] == a)        {tab[j]=1; tab1[j]=0;}
                    else if(goTO[j] == b)   {tab[j]=1; tab1[j]=1;}
                    else if(goTO[j] == c)   {tab[j]=1; tab1[j]=2;}
                    else if(goTO[j] == d)   {tab[j]=1; tab1[j]=3;}
                    else if(goTO[j] == e)   {tab[j]=1; tab1[j]=4;}
                    else if(goTO[j] == f)   {tab[j]=1; tab1[j]=5;}
                    else if(goTO[j] == g)   {tab[j]=1; tab1[j]=6;}
                    else if(goTO[j] == h)   {tab[j]=1; tab1[j]=7;}
                    else if(goTO[j] == i)   {tab[j]=1; tab1[j]=8;}
                    else{  cout<<"nie mozna przejsc do pola "; return x; }

                }
                int x1=x;

                for(int j = 1 ; j < goTO.size() ; j++)
                {
                    //cout<<"(matrix["<<x<<"][tab1["<<j<<"]] nr)" << " "<< (matrix[x1][tab1[j]])<<endl;//test
                    if(matrix[x1][tab1[j]] != (2||1))  {cout<<"nie mozna przejsc do pola "<< endl; return x;}
                    else {x1 = tab1[j];};
                }


                if(tab[goTO.size()-1] != 1) pole = x ;
                else
                {
                    if(goTO[goTO.size()-1]== a) pole=0;
                    else if(goTO[goTO.size()-1]== b) pole=1;
                    else if(goTO[goTO.size()-1]== c) pole=2;
                    else if(goTO[goTO.size()-1]== d) pole=3;
                    else if(goTO[goTO.size()-1]== e) pole=4;
                    else if(goTO[goTO.size()-1]== f) pole=5;
                    else if(goTO[goTO.size()-1]== g) pole=6;
                    else if(goTO[goTO.size()-1]== h) pole=7;
                    else if(goTO[goTO.size()-1]== i) pole=8;
                }

                return pole;
        }
    }

 	statek()    {x=y=5;}//ZMIENIC NA 0!!!


};

//LEVEL 1

class nadwodny : virtual public statek //B is derived from class base
{
private:
    char kolor[50];
public:
    int predkosc, zaloga;// predkosc w wezlach
};
class podwodny : virtual public statek //C is also derived from class base
{
private:
    char kolor[50];
public:
    int zanurzenie, zasieg;
    char naped[20];
};
class powietrzny : virtual public statek//D is also derived from class base
{
private:
    char kolor[50];
public:
    int wysokosc_lotu, ilosc_silnikow;

    //smth
};

//LEVEL 2

class zaglowiec : virtual public nadwodny//E
{
public:
    int wielkosc_zagla, liczba_maszt;
    class zaglowiec *next;//pole wskaznikowe - pamietamy wskazanie do nastepnego wezla
    class zaglowiec *headE = NULL;//poczatek

    void odczytE(char name[100])
    {
        //cout<<"Test: ja w funkcji. \n";
        //cout<<"Podaj nazwe pliku do odczytu (E): ";
        //char name[100];     cin>>name;
        string XXX;
        string fake;
        fstream plik;
        plik.open(name, ios::in);

        if(plik.is_open())
        while(!plik.fail())
        {
            plik>>XXX;
            if(plik.fail()) break;
            if(XXX == "4")
            {
                zaglowiec *element;
                zaglowiec *wsk = new zaglowiec;
                wsk->next = NULL;
                element = headE;
                if(element != NULL)//lista nie pusta
                {
                    while (element->next) element = element->next;
                    element->next = wsk;
                    //cout<<"II"<<endl;
                }
                else
                {
                    headE = wsk; //lista pusta - tmp as 1 node
                    //cout<<"I"<<endl;
                }
                wsk->gps = 4;
                plik>>wsk->masa>>wsk->dlugosc>>wsk->nazwa>>wsk->predkosc>>wsk->zaloga>>wsk->wielkosc_zagla>>wsk->liczba_maszt;
            }
            else
                getline(plik, fake);
        }

    }

    void showE(string option)
    {
        std::string str = option;

        // Spliting the string by an another std::string
        std::vector<std::string> name = split(str, ".");
        zaglowiec *tmp;
        zaglowiec *element = headE;
        while(element)
        {
            if(element->next && (element->next->nazwa == name[1]))
             {
                tmp = element->next;
                cout<<"Masa: "<<tmp->masa<<endl;
                cout<<"Dlugosc: "<<tmp->dlugosc<<endl;
                cout<<"Nazwa: "<<tmp->nazwa<<endl;
                cout<<"Predkosc: "<<tmp->predkosc<<endl;
                cout<<"Liczba zalogi: "<<tmp->zaloga<<endl;
                cout<<"Wielkosc zagla: "<<tmp->wielkosc_zagla<<endl;
                cout<<"Liczba maszt: "<<tmp->liczba_maszt<<endl;
                cout<<"GPS: "<<tmp->gps<<endl;
             }
            else if(element->nazwa == name[1])
            {
                tmp = element;
                cout<<"Masa: "<<tmp->masa<<endl;
                cout<<"Dlugosc: "<<tmp->dlugosc<<endl;
                cout<<"Nazwa: "<<tmp->nazwa<<endl;
                cout<<"Predkosc: "<<tmp->predkosc<<endl;
                cout<<"Liczba zalogi: "<<tmp->zaloga<<endl;
                cout<<"Wielkosc zagla: "<<tmp->wielkosc_zagla<<endl;
                cout<<"Liczba maszt: "<<tmp->liczba_maszt<<endl;
                cout<<"GPS: "<<tmp->gps<<endl;
            }
            element=element->next;
        }

    }
    void treeE()
    {
        zaglowiec *tmp;
        tmp = headE;
        while(tmp != NULL )
        {
            if(tmp->gps == 4)
            {
                cout<<"                 >>>       "<<tmp->nazwa<<"  ";
                tmp = tmp->next;
            }
            else tmp = tmp->next;
        }
    }
    void modE(string option)
    {

        std::string str = option;

        // Spliting the string by an another std::string
        std::vector<std::string> name = split(str, ".");
        zaglowiec *tmp;
        zaglowiec *element = headE;
        while(element)
        {
            if(element->next && (element->next->nazwa == name[1])==0)
             {
                tmp = element->next;
                cout<<"Podaj mase: ";
                cin>>tmp->masa;
                cout<<"Podaj dlugosc: ";
                cin>>tmp->dlugosc;

                cout<<"Podaj nazwe: ";
                cin>>tmp->nazwa;

                cout<<"Podaj predkosc: ";
                cin>>tmp->predkosc;
                cout<<"Podaj liczbe zalogi: ";
                cin>>tmp->zaloga;
                cout<<"Podaj wielkosc zagla: ";
                cin>>tmp->wielkosc_zagla;
                cout<<"Podaj liczbe maszt: ";
                cin>>tmp->liczba_maszt;

                tmp->gps = 4;
             }
            else if(element->nazwa == name[1])
            {
                tmp = element;
                cout<<"Podaj mase: ";
                cin>>tmp->masa;
                cout<<"Podaj dlugosc: ";
                cin>>tmp->dlugosc;

                cout<<"Podaj nazwe: ";
                cin>>tmp->nazwa;

                cout<<"Podaj predkosc: ";
                cin>>tmp->predkosc;
                cout<<"Podaj liczbe zalogi: ";
                cin>>tmp->zaloga;
                cout<<"Podaj wielkosc zagla: ";
                cin>>tmp->wielkosc_zagla;
                cout<<"Podaj liczbe maszt: ";
                cin>>tmp->liczba_maszt;

                tmp->gps = 4;
            }
            element=element->next;
        }
        //cout<<" Zaglowce - zmiana skonczona"<<endl;

    }

    void usunE(string option)
    {
        std::string str = option;

        // Spliting the string by an another std::string
        std::vector<std::string> del = split(str, ".");


        zaglowiec *usun;
        zaglowiec *element =  headE;
        while(element)
        {
            if(element->next && (element->next->nazwa == del[1]))
            {
                usun = element ->next;
                element->next = usun->next;
                delete usun;
            }
            else if(element->nazwa == del[1])
            {
                usun = element;
                headE = element->next;
                delete usun;
            }
            element=element->next;
        }
        //cout<<" Zaglowce - objekt usuniento"<<endl;
    }
    void dirE()
    {
        cout<<"###Zaglowce### "<<endl;
        zaglowiec *tmp;
        tmp = headE;
        while(tmp != NULL )
        {
            if(tmp->gps == 4)
            {
                cout<<"Nazwa: "<<tmp->nazwa<<endl;
                tmp = tmp->next;
            }
            else tmp = tmp->next;
        }
    }
    void printE()
    {
        cout<<"###Zaglowce### "<<endl;
        zaglowiec *tmp;
        tmp = headE;
        while(tmp != NULL )
        {
            if(tmp->gps == 4)
            {
                cout<<"Masa: "<<tmp->masa<<endl;
                cout<<"Dlugosc: "<<tmp->dlugosc<<endl;
                cout<<"Nazwa: "<<tmp->nazwa<<endl;
                cout<<"Predkosc: "<<tmp->predkosc<<endl;
                cout<<"Liczba zalogi: "<<tmp->zaloga<<endl;
                cout<<"Wielkosc zagla: "<<tmp->wielkosc_zagla<<endl;
                cout<<"Liczba maszt: "<<tmp->liczba_maszt<<endl;
                cout<<"GPS: "<<tmp->gps<<endl;
                tmp = tmp->next;
            }
            else tmp = tmp->next;
        }
    }
    void dodajE(int x)
    {
        //cout<<"dodajE"<<endl;
        zaglowiec *element;
        zaglowiec *tmp = new zaglowiec;
        tmp->next = NULL;

        element = headE;
        if(element != NULL)//lista nie pusta
        {
            while (element->next) element = element->next;
            element->next = tmp;
            //cout<<"II"<<endl;
        }
        else
        {
            headE = tmp; //lista pusta - tmp as 1 node
            //cout<<"I"<<endl;
        }

            fflush(stdin);

                cout<<"Podaj mase: ";
                cin>>tmp->masa;
                cout<<"Podaj dlugosc: ";
                cin>>tmp->dlugosc;
                cout<<"Podaj nazwe: ";
                cin>>tmp->nazwa;
                cout<<"Podaj predkosc: ";
                cin>>tmp->predkosc;
                cout<<"Podaj liczbe zalogi: ";
                cin>>tmp->zaloga;
                cout<<"Podaj wielkosc zagla: ";
                cin>>tmp->wielkosc_zagla;
                cout<<"Podaj liczbe maszt: ";
                cin>>tmp->liczba_maszt;

                tmp->gps = 4;


    }

};
class okret : virtual public nadwodny//F
{
public:
    int silaOgniu;
    char typ[50];

    class okret *next;//pole wskaznikowe - pamietamy wskazanie do nastepnego wezla
    class okret *headF = NULL;

    void odczytF(char name[100])
    {
        string XXX, fake;
        fstream plik;
        plik.open(name, ios::in);

        if(plik.is_open())
        while(!plik.fail())
        {
            plik>>XXX;
            if(plik.fail()) break;
            if(XXX == "5")
            {
                    okret *element;
                    okret *wsk = new okret;
                    wsk->next = NULL;

                    element = headF;
                    if(element != NULL)//lista nie pusta
                    {
                        while (element->next) element = element->next;
                        element->next = wsk;
                        //cout<<"II"<<endl;
                    }
                    else
                    {
                        headF = wsk; //lista pusta - tmp as 1 node
                        //cout<<"I"<<endl;
                    }
                    wsk->gps = 5;
                    plik>>wsk->masa>>wsk->dlugosc>>wsk->nazwa>>wsk->predkosc>>wsk->zaloga>>wsk->silaOgniu>>wsk->typ;
            }
            else
                getline(plik, fake);

        }

    }

    void showF(string option)
    {
        std::string str = option;

        // Spliting the string by an another std::string
        std::vector<std::string> name = split(str, ".");
        okret *tmp;
        okret *element = headF;
        while(element)
        {
            if(element->next && (element->next->nazwa == name[1]))
             {
                tmp = element->next;
                cout<<"Masa: "<<tmp->masa<<endl;
                cout<<"Dlugosc: "<<tmp->dlugosc<<endl;
                cout<<"Nazwa: "<<tmp->nazwa<<endl;
                cout<<"Predkosc: "<<tmp->predkosc<<endl;
                cout<<"Liczba zalogi: "<<tmp->zaloga<<endl;
                cout<<"Sila ogniu: "<<tmp->silaOgniu<<endl;
                cout<<"Typ: "<<tmp->typ<<endl;
                cout<<"GPS: "<<tmp->gps<<endl;
             }
            else if(element->nazwa == name[1])
            {
                tmp = element;
                cout<<"Masa: "<<tmp->masa<<endl;
                cout<<"Dlugosc: "<<tmp->dlugosc<<endl;
                cout<<"Nazwa: "<<tmp->nazwa<<endl;
                cout<<"Predkosc: "<<tmp->predkosc<<endl;
                cout<<"Liczba zalogi: "<<tmp->zaloga<<endl;
                cout<<"Sila ogniu: "<<tmp->silaOgniu<<endl;
                cout<<"Typ: "<<tmp->typ<<endl;
                cout<<"GPS: "<<tmp->gps<<endl;
            }
            element=element->next;
        }

    }
    void treeF()
    {
        okret *tmp;
        tmp = headF;
        while(tmp != NULL )
        {
            if(tmp->gps == 5)
            {
                cout<<"                 >>>       "<<tmp->nazwa<<"  ";
                tmp = tmp->next;
            }
            else tmp = tmp->next;
        }
    }
    void modF(string option)
    {

        std::string str = option;

        // Spliting the string by an another std::string
        std::vector<std::string> name = split(str, ".");
        okret *tmp;
        okret *element = headF;
        while(element)
        {
            if(element->next && (element->next->nazwa == name[1]))
            {
               tmp = element->next;
                cout<<"Podaj mase: ";
                cin>>tmp->masa;
                cout<<"Podaj dlugosc: ";
                cin>>tmp->dlugosc;
                cout<<"Podaj nazwe: ";
                cin>>tmp->nazwa;
                cout<<"Podaj predkosc: ";
                cin>>tmp->predkosc;
                cout<<"Podaj liczbe zalogi: ";
                cin>>tmp->zaloga;
                cout<<"Podaj sile ogniu: ";
                cin>>tmp->silaOgniu;
                cout<<"Podaj typ: ";
                cin>>tmp->typ;
                tmp->gps = 5;
            }

            else if(element->nazwa == name[1])
            {
                tmp = element;
                cout<<"Podaj mase: ";
                cin>>tmp->masa;
                cout<<"Podaj dlugosc: ";
                cin>>tmp->dlugosc;
                cout<<"Podaj nazwe: ";
                cin>>tmp->nazwa;
                cout<<"Podaj predkosc: ";
                cin>>tmp->predkosc;
                cout<<"Podaj liczbe zalogi: ";
                cin>>tmp->zaloga;
                cout<<"Podaj sile ogniu: ";
                cin>>tmp->silaOgniu;
                cout<<"Podaj typ: ";
                cin>>tmp->typ;
                tmp->gps = 5;
            }
            element=element->next;
        }
        //cout<<" Batyskafy - zmiana skonczona"<<endl;
    }
    void usunF(string option)
    {
        std::string str = option;

        // Spliting the string by an another std::string
        std::vector<std::string> del = split(str, ".");

        okret *usun;
        okret *element =  headF;
        while(element)
        {
            if(element->next && (element->next->nazwa == del[1]))
            {
                usun = element ->next;
                element->next = usun->next;
                delete usun;
            }
            else if(element->nazwa == del[1])
            {
                usun = element;
                headF = element->next;
                delete usun;
            }
            element=element->next;
        }
        //cout<<" Okrety - objekt usuniento"<<endl;
    }
    void dirF()
    {
        cout<<"###Okrety### "<<endl;
        okret *tmp;
        tmp = headF;
        while(tmp != NULL )
        {
            if(tmp->gps == 5)
            {
                cout<<"Nazwa: "<<tmp->nazwa<<endl;
                tmp = tmp->next;
            }
            else tmp = tmp->next;
        }
    }

    void printF()
    {
        cout<<"###Okret### "<<endl;
        okret *tmp;
        tmp = headF;

        while(tmp != NULL)
        {
            if(tmp->gps == 5)
            {
                cout<<"Masa: "<<tmp->masa<<endl;
                cout<<"Dlugosc: "<<tmp->dlugosc<<endl;
                cout<<"Nazwa: "<<tmp->nazwa<<endl;
                cout<<"Predkosc: "<<tmp->predkosc<<endl;
                cout<<"Liczba zalogi: "<<tmp->zaloga<<endl;
                cout<<"Sila ogniu: "<<tmp->silaOgniu<<endl;
                cout<<"Typ: "<<tmp->typ<<endl;
                tmp = tmp->next;
            }
            else tmp = tmp->next;
        }
    }
    void dodajF(int x)
    {
        //cout<<"dodajF"<<endl;
        okret *element;
        okret *tmp = new okret;
        tmp->next = NULL;

        element = headF;
        if(element != NULL)//lista nie pusta
        {
            while (element->next) element = element->next;
            element->next = tmp;
            //cout<<"II"<<endl;
        }
        else
        {
            headF = tmp; //lista pusta - tmp as 1 node
            //cout<<"I"<<endl;
        }
        fflush(stdin);
        cout<<"Podaj mase: ";
        cin>>tmp->masa;
        cout<<"Podaj dlugosc: ";
        cin>>tmp->dlugosc;
        cout<<"Podaj nazwe: ";
        cin>>tmp->nazwa;
        cout<<"Podaj predkosc: ";
        cin>>tmp->predkosc;
        cout<<"Podaj liczbe zalogi: ";
        cin>>tmp->zaloga;
        cout<<"Podaj sile ogniu: ";
        cin>>tmp->silaOgniu;
        cout<<"Podaj typ: ";
        cin>>tmp->typ;
        tmp->gps = 5;
    }


};
class batyskaf : virtual public podwodny//G
{
public:
    int zaloga, moc_silnikow;

    class batyskaf *next;//pole wskaznikowe - pamietamy wskazanie do nastepnego wezla
    class batyskaf *headG = NULL;

    void odczytG(char name[100])
    {
        //cout<<"Podaj nazwe pliku do odczytu (G): ";
        //char name[100];     cin>>name;
        string XXX, fake;
        fstream plik;
        plik.open(name, ios::in);
        if(plik.is_open())
        while(!plik.fail())
        {
            if(plik.fail()) break;
            plik>>XXX;
            if(XXX == "6")
            {
                    batyskaf *element;
                    batyskaf *wsk = new batyskaf;
                    wsk->next = NULL;

                    element = headG;
                    if(element != NULL)//lista nie pusta
                    {
                        while (element->next) element = element->next;
                        element->next = wsk;
                        //cout<<"II"<<endl;
                    }
                    else
                    {
                        headG = wsk; //lista pusta - tmp as 1 node
                        //cout<<"I"<<endl;
                    }
                    wsk->gps = 6;
                    plik>>wsk->masa>>wsk->dlugosc>>wsk->nazwa>>wsk->zanurzenie>>wsk->zasieg>>wsk->naped>>wsk->zaloga>>wsk->moc_silnikow;

            }
            else
                getline(plik, fake);
        }

    }

    void showG(string option)
    {
        std::string str = option;

        // Spliting the string by an another std::string
        std::vector<std::string> name = split(str, ".");
        batyskaf *tmp;
        batyskaf *element = headG;
        while(element)
        {
            if(element->next && (element->next->nazwa == name[1]))
             {
                tmp = element->next;
                cout<<"Masa: "<<tmp->masa<<endl;
                cout<<"Dlugosc: "<<tmp->dlugosc<<endl;
                cout<<"Nazwa: "<<tmp->nazwa<<endl;
                cout<<"Zanurzenie maksymalne: "<<tmp->zanurzenie<<endl;
                cout<<"Zasieg: "<<tmp->zasieg<<endl;
                cout<<"Naped: "<<tmp->naped<<endl;
                cout<<"Zaloga: "<<tmp->zaloga<<endl;
                cout<<"Moc silnikow: "<<tmp->moc_silnikow<<endl;
                cout<<"GPS: "<<tmp->gps<<endl;
             }
            else if(element->nazwa == name[1])
            {
                tmp = element;
                cout<<"Masa: "<<tmp->masa<<endl;
                cout<<"Dlugosc: "<<tmp->dlugosc<<endl;
                cout<<"Nazwa: "<<tmp->nazwa<<endl;
                cout<<"Zanurzenie maksymalne: "<<tmp->zanurzenie<<endl;
                cout<<"Zasieg: "<<tmp->zasieg<<endl;
                cout<<"Naped: "<<tmp->naped<<endl;
                cout<<"Zaloga: "<<tmp->zaloga<<endl;
                cout<<"Moc silnikow: "<<tmp->moc_silnikow<<endl;
                cout<<"GPS: "<<tmp->gps<<endl;
            }
            element=element->next;
        }

    }
    void treeG()
    {
        batyskaf *tmp;
        tmp = headG;
        while(tmp != NULL )
        {
            if(tmp->gps == 6)
            {
                cout<<"                 >>>       "<<tmp->nazwa<<"  ";
                tmp = tmp->next;
            }
            else tmp = tmp->next;
        }
    }
    void modG(string option)
    {
        std::string str = option;

        // Spliting the string by an another std::string
        std::vector<std::string> name = split(str, ".");

        batyskaf *tmp;
        batyskaf *element = headG;
        while(element)
        {
            if(element->next && (element->next->nazwa == name[1]))
            {
                tmp = element->next;
                fflush(stdin);
                cout<<"Podaj mase: ";
                cin>>tmp->masa;
                cout<<"Podaj dlugosc: ";
                cin>>tmp->dlugosc;
                cout<<"Podaj nazwe: ";
                cin>>tmp->nazwa;
                cout<<"Podaj zanurzenie maksymalne: ";
                cin>>tmp->zanurzenie;
                cout<<"Podaj zasieg: ";
                cin>>tmp->zasieg;
                cout<<"Podaj naped: ";
                cin>>tmp->naped;
                cout<<"Podaj liczbe zalogi: ";
                cin>>tmp->zaloga;
                cout<<"Podaj moc silnika: ";
                cin>>tmp->moc_silnikow;
                tmp->gps = 6;
            }

            else if(element->nazwa == name[1])
            {
                tmp = element;
                fflush(stdin);
                cout<<"Podaj mase: ";
                cin>>tmp->masa;
                cout<<"Podaj dlugosc: ";
                cin>>tmp->dlugosc;
                cout<<"Podaj nazwe: ";
                cin>>tmp->nazwa;
                cout<<"Podaj zanurzenie maksymalne: ";
                cin>>tmp->zanurzenie;
                cout<<"Podaj zasieg: ";
                cin>>tmp->zasieg;
                cout<<"Podaj naped: ";
                cin>>tmp->naped;
                cout<<"Podaj liczbe zalogi: ";
                cin>>tmp->zaloga;
                cout<<"Podaj moc silnika: ";
                cin>>tmp->moc_silnikow;
                tmp->gps = 6;
            }
            element=element->next;
        }
        //cout<<" Okrety - zmiana skonczona"<<endl;
    }
    void usunG(string option)
    {
        std::string str = option;

        // Spliting the string by an another std::string
        std::vector<std::string> del = split(str, ".");
        batyskaf *usun;
        batyskaf *element =  headG;
        while(element)
        {
            if(element->next && (element->next->nazwa == del[1]))
            {
                usun = element ->next;
                element->next = usun->next;
                delete usun;
            }
            else if(element->nazwa == del[1])
            {
                usun = element;
                headG = element->next;
                delete usun;
            }
            element=element->next;
        }
        //cout<<" Batyskafy - objekt usuniento"<<endl;
    }
    void dirG()
    {
        cout<<"###Batyskafy### "<<endl;
        batyskaf *tmp;
        tmp = headG;
        while(tmp != NULL )
        {
            if(tmp->gps == 6)
            {
                cout<<"Nazwa: "<<tmp->nazwa<<endl;
                tmp = tmp->next;
            }
            else tmp = tmp->next;
        }
    }

    void printG()
    {
        cout<<"###Batyskaf### "<<endl;
        batyskaf *tmp;
        tmp = headG;
        while(tmp != NULL)
        {
            if(tmp->gps == 6)
            {
                cout<<"Masa: "<<tmp->masa<<endl;
                cout<<"Dlugosc: "<<tmp->dlugosc<<endl;
                cout<<"Nazwa: "<<tmp->nazwa<<endl;
                cout<<"Zanurzenie maksymalne: "<<tmp->zanurzenie<<endl;
                cout<<"Zasieg: "<<tmp->zasieg<<endl;
                cout<<"Naped: "<<tmp->naped<<endl;
                cout<<"Zaloga: "<<tmp->zaloga<<endl;
                cout<<"Moc silnikow: "<<tmp->moc_silnikow<<endl;
                tmp = tmp->next;
            }
            else tmp = tmp->next;
        }
    }
    void dodajG(int x)
    {
        //cout<<"dodajG"<<endl;
        batyskaf *element;
        batyskaf *tmp = new batyskaf;
        tmp->next = NULL;

        element = headG;
        if(element != NULL)//lista nie pusta
        {
            while (element->next) element = element->next;
            element->next = tmp;
            //cout<<"II"<<endl;
        }
        else
        {
            headG = tmp; //lista pusta - tmp as 1 node
            //cout<<"I"<<endl;
        }
        fflush(stdin);
        cout<<"Podaj mase: ";
        cin>>tmp->masa;
        cout<<"Podaj dlugosc: ";
        cin>>tmp->dlugosc;
        cout<<"Podaj nazwe: ";
        cin>>tmp->nazwa;
        cout<<"Podaj zanurzenie maksymalne: ";
        cin>>tmp->zanurzenie;
        cout<<"Podaj zasieg: ";
        cin>>tmp->zasieg;
        cout<<"Podaj naped: ";
        cin>>tmp->naped;
        cout<<"Podaj liczbe zalogi: ";
        cin>>tmp->zaloga;
        cout<<"Podaj moc silnika: ";
        cin>>tmp->moc_silnikow;
        tmp->gps = 6;
    }

};
class balon : virtual public powietrzny//H
{
public:
    int rozmiar_czaszy, pojemosc_paliwa;

    class balon *next;//pole wskaznikowe - pamietamy wskazanie do nastepnego wezla
    class balon *headH = NULL;

    void odczytH(char name[100])
    {
        //cout<<"Podaj nazwe pliku do odczytu (H): ";
        //char name[100];     cin>>name;
        string XXX, fake;
        fstream plik;
        plik.open(name, ios::in);
        if(plik.is_open())
        while(!plik.fail())
        {
            plik>>XXX;
            if(plik.fail()) break;
            if(XXX == "7")
            {
                    balon *element;
                    balon *wsk = new balon;
                    wsk->next = NULL;

                    element = headH;
                    if(element != NULL)//lista nie pusta
                    {
                        while (element->next) element = element->next;
                        element->next = wsk;
                        //cout<<"II"<<endl;
                    }
                    else
                    {
                        headH = wsk; //lista pusta - tmp as 1 node
                        //cout<<"I"<<endl;
                    }
                    wsk->gps = 7;
                    plik>>wsk->masa>>wsk->dlugosc>>wsk->nazwa>>wsk->wysokosc_lotu>>wsk->ilosc_silnikow>>wsk->rozmiar_czaszy>>wsk->pojemosc_paliwa;

            }
        }

    }

    void showH(string option)
    {
        std::string str = option;

        // Spliting the string by an another std::string
        std::vector<std::string> name = split(str, ".");
        balon *tmp;
        balon *element = headH;
        while(element)
        {
            if(element->next && (element->next->nazwa == name[1]))
             {
                tmp = element->next;
                cout<<"Masa: "<<tmp->masa<<endl;
                cout<<"Dlugosc: "<<tmp->dlugosc<<endl;
                cout<<"Nazwa: "<<tmp->nazwa<<endl;
                cout<<"Wysokosc lotu: "<<tmp->wysokosc_lotu<<endl;
                cout<<"Ilosc silnikow: "<<tmp->ilosc_silnikow<<endl;
                cout<<"Rozmiar czaszy: "<<tmp->rozmiar_czaszy<<endl;
                cout<<"Pojemosc paliwa: "<<tmp->pojemosc_paliwa<<endl;
                cout<<"GPS: "<<tmp->gps<<endl;
             }
            else if(element->nazwa == name[1])
            {
                tmp = element;
                cout<<"Masa: "<<tmp->masa<<endl;
                cout<<"Dlugosc: "<<tmp->dlugosc<<endl;
                cout<<"Nazwa: "<<tmp->nazwa<<endl;
                cout<<"Wysokosc lotu: "<<tmp->wysokosc_lotu<<endl;
                cout<<"Ilosc silnikow: "<<tmp->ilosc_silnikow<<endl;
                cout<<"Rozmiar czaszy: "<<tmp->rozmiar_czaszy<<endl;
                cout<<"Pojemosc paliwa: "<<tmp->pojemosc_paliwa<<endl;
                cout<<"GPS: "<<tmp->gps<<endl;
            }
            element=element->next;
        }

    }
    void treeH()
    {
        balon *tmp;
        tmp = headH;
        while(tmp != NULL )
        {
            if(tmp->gps == 7)
            {
                cout<<"                 >>>       "<<tmp->nazwa<<"  ";
                tmp = tmp->next;
            }
            else tmp = tmp->next;
        }
    }
    void modH(string option)
    {

        std::string str = option;

        // Spliting the string by an another std::string
        std::vector<std::string> name = split(str, ".");

        balon *tmp;
        balon *element = headH;
        while(element)
        {
           if(element->next && (element->next->nazwa == name[1]))
            {
                tmp = element->next;
                fflush(stdin);
                cout<<"Podaj mase: ";
                cin>>tmp->masa;
                cout<<"Podaj dlugosc: ";
                cin>>tmp->dlugosc;
                cout<<"Podaj nazwe: ";
                cin>>tmp->nazwa;
                cout<<"Podaj wysokosc lotu: ";
                cin>>tmp->wysokosc_lotu;
                cout<<"Podaj ilosc silnikow: ";
                cin>>tmp->ilosc_silnikow;
                cout<<"Podaj rozmiar czaszy: ";
                cin>>tmp->rozmiar_czaszy;
                cout<<"Podaj pojemnosc palaiwa: ";
                cin>>tmp->pojemosc_paliwa;
                tmp->gps = 7;
            }
            else if(element->nazwa == name[1])
            {
                tmp = element;
                fflush(stdin);
                cout<<"Podaj mase: ";
                cin>>tmp->masa;
                cout<<"Podaj dlugosc: ";
                cin>>tmp->dlugosc;
                cout<<"Podaj nazwe: ";
                cin>>tmp->nazwa;
                cout<<"Podaj wysokosc lotu: ";
                cin>>tmp->wysokosc_lotu;
                cout<<"Podaj ilosc silnikow: ";
                cin>>tmp->ilosc_silnikow;
                cout<<"Podaj rozmiar czaszy: ";
                cin>>tmp->rozmiar_czaszy;
                cout<<"Podaj pojemnosc palaiwa: ";
                cin>>tmp->pojemosc_paliwa;
                tmp->gps = 7;
            }
            element=element->next;
        }
        //cout<<" Balony - zmiana skonczona"<<endl;
    }
    void usunH(string option)
    {
        std::string str = option;

        // Spliting the string by an another std::string
        std::vector<std::string> del = split(str, ".");
        balon *usun;
        balon *element =  headH;
        while(element)
        {
            if(element->next && (element->next->nazwa == del[1]))
            {
                usun = element ->next;
                element->next = usun->next;
                delete usun;
            }
            else if(element->nazwa == del[1])
            {
                usun = element;
                headH = element->next;
                delete usun;
            }
            element=element->next;
        }
        //cout<<" Balone - objekt usuniento"<<endl;
    }
    void dirH()
    {
        cout<<"###Balony### "<<endl;
        balon *tmp;
        tmp = headH;
        while(tmp != NULL )
        {
            if(tmp->gps == 7)
            {
                cout<<"Nazwa: "<<tmp->nazwa<<endl;
                tmp = tmp->next;
            }
            else tmp = tmp->next;
        }
    }

    void printH()
    {
        cout<<"###Balon### "<<endl;
        balon *tmp;
        tmp = headH;
        while(tmp != NULL)
        {
            if(tmp->gps == 7)
            {
                cout<<"Masa: "<<tmp->masa<<endl;
                cout<<"Dlugosc: "<<tmp->dlugosc<<endl;
                cout<<"Nazwa: "<<tmp->nazwa<<endl;
                cout<<"Wysokosc lotu: "<<tmp->wysokosc_lotu<<endl;
                cout<<"Ilosc silnikow: "<<tmp->ilosc_silnikow<<endl;
                cout<<"Rozmiar czaszy: "<<tmp->rozmiar_czaszy<<endl;
                cout<<"Pojemosc paliwa: "<<tmp->pojemosc_paliwa<<endl;
                tmp = tmp->next;
            }
            else tmp = tmp->next;
        }
    }
    void dodajH(int x)
    {
        //cout<<"dodajH"<<endl;
        balon *element;
        balon *tmp = new balon;
        tmp->next = NULL;

        element = headH;
        if(element != NULL)//lista nie pusta
        {
            while (element->next) element = element->next;
            element->next = tmp;
            //cout<<"II"<<endl;
        }
        else
        {
            headH = tmp; //lista pusta - tmp as 1 node
            //cout<<"I"<<endl;
        }
        fflush(stdin);
        cout<<"Podaj mase: ";
        cin>>tmp->masa;
        cout<<"Podaj dlugosc: ";
        cin>>tmp->dlugosc;
        cout<<"Podaj nazwe: ";
        cin>>tmp->nazwa;
        cout<<"Podaj wysokosc lotu: ";
        cin>>tmp->wysokosc_lotu;
        cout<<"Podaj ilosc silnikow: ";
        cin>>tmp->ilosc_silnikow;
        cout<<"Podaj rozmiar czaszy: ";
        cin>>tmp->rozmiar_czaszy;
        cout<<"Podaj pojemnosc palaiwa: ";
        cin>>tmp->pojemosc_paliwa;
        tmp->gps = 7;

    }

};
class samolot : virtual public powietrzny//I
{
public:
    int zasieg, zaloga;

    class samolot *next;//pole wskaznikowe - pamietamy wskazanie do nastepnego wezla
    class samolot *headI = NULL;

    void odczytI(char name[100])
    {
        //cout<<"Podaj nazwe pliku do odczytu (I): ";
        //char name[100];     cin>>name;
        string XXX, fake;
        fstream plik;
        plik.open(name, ios::in);
        if(plik.is_open())
        while(!plik.fail())
        {
            plik>>XXX;
            if(plik.fail()) break;
            if(XXX == "8")
            {
                    samolot *element;
                    samolot *wsk = new samolot;
                    wsk->next = NULL;

                    element = headI;
                    if(element != NULL)//lista nie pusta
                    {
                        while (element->next) element = element->next;
                        element->next = wsk;
                        //cout<<"II"<<endl;
                    }
                    else
                    {
                        headI = wsk; //lista pusta - tmp as 1 node
                        //cout<<"I"<<endl;
                    }
                    wsk->gps = 8;
                    plik>>wsk->masa>>wsk->dlugosc>>wsk->nazwa>>wsk->wysokosc_lotu>>wsk->ilosc_silnikow>>wsk->zasieg>>wsk->zaloga;
                    if(plik.fail()) break;
            }
            else
                getline(plik, fake);


        }

    }
    void showI(string option)
    {
        std::string str = option;

        // Spliting the string by an another std::string
        std::vector<std::string> name = split(str, ".");
        samolot *tmp;
        samolot *element = headI;
        while(element)
        {
            if(element->next && (element->next->nazwa == name[1]))
             {
                tmp = element->next;
                cout<<"Masa: "<<tmp->masa<<endl;
                cout<<"Dlugosc: "<<tmp->dlugosc<<endl;
                cout<<"Nazwa: "<<tmp->nazwa<<endl;
                cout<<"ZWysokosc lotu: "<<tmp->wysokosc_lotu<<endl;
                cout<<"Ilosc silnikow: "<<tmp->ilosc_silnikow<<endl;
                cout<<"Zasieg: "<<tmp->zasieg<<endl;
                cout<<"Zaloga: "<<tmp->zaloga<<endl;
                cout<<"GPS: "<<tmp->gps<<endl;
             }
            else if(element->nazwa == name[1])
            {
                tmp = element;
                cout<<"Masa: "<<tmp->masa<<endl;
                cout<<"Dlugosc: "<<tmp->dlugosc<<endl;
                cout<<"Nazwa: "<<tmp->nazwa<<endl;
                cout<<"ZWysokosc lotu: "<<tmp->wysokosc_lotu<<endl;
                cout<<"Ilosc silnikow: "<<tmp->ilosc_silnikow<<endl;
                cout<<"Zasieg: "<<tmp->zasieg<<endl;
                cout<<"Zaloga: "<<tmp->zaloga<<endl;
                cout<<"GPS: "<<tmp->gps<<endl;
            }
            element=element->next;
        }

    }
    void treeI()
    {
        samolot *tmp;
        tmp = headI;
        while(tmp != NULL )
        {
            if(tmp->gps == 8)
            {
                cout<<"                 >>>       "<<tmp->nazwa<<"  ";
                tmp = tmp->next;
            }
            else tmp = tmp->next;
        }
    }
    void modI(string option)
    {

        std::string str = option;

        // Spliting the string by an another std::string
        std::vector<std::string> name = split(str, ".");

        samolot *tmp;
        samolot *element = headI;
        while(element)
        {
            if(element->next && (element->next->nazwa == name[1]))
            {
                tmp = element->next;
                cout<<"Podaj mase: ";
                cin>>tmp->masa;
                cout<<"Podaj dlugosc: ";
                cin>>tmp->dlugosc;
                cout<<"Podaj nazwe: ";
                cin>>tmp->nazwa;
                cout<<"Podaj wysokosc lotu: ";
                cin>>tmp->wysokosc_lotu;
                cout<<"Podaj ilosc silnikow: ";
                cin>>tmp->ilosc_silnikow;
                cout<<"Podaj zasieg: ";
                cin>>tmp->zasieg;
                cout<<"Podaj ilosc zalogi: ";
                cin>>tmp->zaloga;
                tmp->gps = 8;
            }

            else if(element->nazwa == name[1])
            {
                tmp = element;
                cout<<"Podaj mase: ";
                cin>>tmp->masa;
                cout<<"Podaj dlugosc: ";
                cin>>tmp->dlugosc;
                cout<<"Podaj nazwe: ";
                cin>>tmp->nazwa;
                cout<<"Podaj wysokosc lotu: ";
                cin>>tmp->wysokosc_lotu;
                cout<<"Podaj ilosc silnikow: ";
                cin>>tmp->ilosc_silnikow;
                cout<<"Podaj zasieg: ";
                cin>>tmp->zasieg;
                cout<<"Podaj ilosc zalogi: ";
                cin>>tmp->zaloga;
                tmp->gps = 8;
            }
            element=element->next;
        }
        //cout<<" Samoloty - zmiana skonczona"<<endl;
    }
    void usunI(string option)
    {
        std::string str = option;

        // Spliting the string by an another std::string
        std::vector<std::string> del = split(str, ".");
        samolot *usun;
        samolot *element =  headI;
        while(element)
        {
            if(element->next && (element->next->nazwa == del[1]))
            {
                usun = element ->next;
                element->next = usun->next;
                delete usun;
            }
            else if(element->nazwa == del[1])
            {
                usun = element;
                headI = element->next;
                delete usun;
            }
            element=element->next;
        }
        //cout<<" Samoloty - objekt usuniento"<<endl;
    }
    void dirI()
    {
        cout<<"###Samoloty### "<<endl;
        samolot *tmp;
        tmp = headI;
        while(tmp != NULL )
        {
            if(tmp->gps == 8)
            {
                cout<<"Nazwa: "<<tmp->nazwa<<endl;
                tmp = tmp->next;
            }
            else tmp = tmp->next;
        }
    }

    void printI()
    {
        cout<<"###Samolot### "<<endl;
        samolot *tmp;
        tmp = headI;
        while(tmp != NULL)
        {
            if(tmp->gps == 5)
            {
                cout<<"Masa: "<<tmp->masa<<endl;
                cout<<"Dlugosc: "<<tmp->dlugosc<<endl;
                cout<<"Nazwa: "<<tmp->nazwa<<endl;
                cout<<"ZWysokosc lotu: "<<tmp->wysokosc_lotu<<endl;
                cout<<"Ilosc silnikow: "<<tmp->ilosc_silnikow<<endl;
                cout<<"Zasieg: "<<tmp->zasieg<<endl;
                cout<<"Zaloga: "<<tmp->zaloga<<endl;
                tmp = tmp->next;
            }
            else tmp = tmp->next;
        }
    }
    void dodajI(int x)
    {
        //cout<<"dodajI"<<endl;
        samolot *element;
        samolot *tmp = new samolot;
        tmp->next = NULL;

        element = headI;
        if(element != NULL)//lista nie pusta
        {
            while (element->next) element = element->next;
            element->next = tmp;
            //cout<<"II"<<endl;
        }
        else
        {
            headI = tmp; //lista pusta - tmp as 1 node
            //cout<<"I"<<endl;
        }
        fflush(stdin);
        cout<<"Podaj mase: ";
        cin>>tmp->masa;
        cout<<"Podaj dlugosc: ";
        cin>>tmp->dlugosc;
        cout<<"Podaj nazwe: ";
        cin>>tmp->nazwa;
        cout<<"Podaj wysokosc lotu: ";
        cin>>tmp->wysokosc_lotu;
        cout<<"Podaj ilosc silnikow: ";
        cin>>tmp->ilosc_silnikow;
        cout<<"Podaj zasieg: ";
        cin>>tmp->zasieg;
        cout<<"Podaj ilosc zalogi: ";
        cin>>tmp->zaloga;
        tmp->gps = 8;
    }

};



class work : public zaglowiec, public okret, public batyskaf, public balon, public samolot
{
public:

    void saveW(class zaglowiec* headE, class okret* headF, class batyskaf* headG, class balon* headH, class samolot* headI)
    {
        cout<<"Podaj nazwe pliku do zapisu |name.txt| : ";
        fflush(stdin);        char file[100]; cin>>file;
        //work *hE = zaglowiec::head;

        fstream plik;
        plik.open(file, ios::out);
        if(plik.is_open())
        {
            zaglowiec *wskE = headE;
            //if(wskE == NULL)            //cout<<"Lista E pusta. Nie mozna nic zapisac do pliku."<<endl;
            if(wskE != NULL)
            {
                    while(wskE!=NULL)
                    {
                        plik<<wskE->gps<<" "<<wskE->masa<<" "<<wskE->dlugosc<<" "<<wskE->nazwa<<" "<<wskE->predkosc<<" "<<wskE->zaloga<<" "<<wskE->wielkosc_zagla<<" "<<wskE->liczba_maszt<<endl;
                        wskE = wskE->next;
                    }
            }


            okret *wskF = headF;
            //if(wskF == NULL)            //cout<<"Lista F pusta. Nie mozna nic zapisac do pliku."<<endl;
            if(wskF != NULL)
            {
                while(wskF!=NULL)
                {
                    plik<<wskF->gps<<"  ";
                    plik<<wskF->masa<<"  ";
                    plik<<wskF->dlugosc<<"  ";
                    plik<<wskF->nazwa<<"  ";
                    plik<<wskF->predkosc<<"  ";
                    plik<<wskF->zaloga<<"  ";
                    plik<<wskF->silaOgniu<<"  ";
                    plik<<wskF->typ<<endl;

                    wskF = wskF->next;
                }
            }


            batyskaf *wskG = headG;
            //if(wskG == NULL)            //cout<<"Lista G pusta. Nie mozna nic zapisac do pliku."<<endl;
            if(wskG != NULL)
            {
                while(wskG!=NULL)
                {
                    plik<<wskG->gps<<" ";
                    plik<<wskG->masa<<" ";
                    plik<<wskG->dlugosc<<" ";
                    plik<<wskG->nazwa<<" ";
                    plik<<wskG->zanurzenie<<" ";
                    plik<<wskG->zasieg<<" ";
                    plik<<wskG->naped<<" ";
                    plik<<wskG->zaloga<<" ";
                    plik<<wskG->moc_silnikow<<endl;

                    wskG = wskG->next;
                }
            }


            balon *wskH = headH;
            //if(wskH == NULL)            //cout<<"Lista H pusta. Nie mozna nic zapisac do pliku."<<endl;
            if(wskH != NULL)
            {
                while(wskH!=NULL)
                {
                    plik<<wskH->gps<<" "<<wskH->masa<<" "<<wskH->dlugosc<<" "<<wskH->nazwa<<" "<<wskH->wysokosc_lotu<<" "<<wskH->ilosc_silnikow<<" "<<wskH->rozmiar_czaszy<<" "<<wskH->pojemosc_paliwa<<endl;
                    wskH = wskH->next;
                }
            }


            samolot *wskI = headI;
            //if(wskI == NULL)            //cout<<"Lista I pusta. Nie mozna nic zapisac do pliku."<<endl;
            if(wskI != NULL)
            {
                while(wskI!=NULL)
                {
                    plik<<wskI->gps<<" "<<wskI->masa<<" "<<wskI->dlugosc<<" "<<wskI->nazwa<<" "<<wskI->wysokosc_lotu<<" "<<wskI->ilosc_silnikow<<" "<<wskI->zasieg<<endl;
                    wskI = wskI->next;
                }
            }

        }
    }
    void readW(char name[100])
    {
        string XXX;


        fstream plik;
        plik.open(name, ios::in);
        if(plik.is_open())
        while(!plik.fail())
        {
            plik>>XXX;
            //cout<<"text XXX  == "<<XXX<<endl;
            if(XXX == "4")
            {
                cout<<"creat "<<XXX<<endl;//TEST
                    zaglowiec *element;
                    zaglowiec *wsk = new zaglowiec;
                    wsk->next = NULL;

                    element = headE;
                    if(element != NULL)//lista nie pusta
                    {
                        while (element->next) element = element->next;
                        element->next = wsk;
                        cout<<"II"<<endl;
                    }
                    else
                    {
                        headE = wsk; //lista pusta - tmp as 1 node
                        cout<<"I"<<endl;
                    }
                plik>>wsk->gps>>wsk->masa>>wsk->dlugosc>>wsk->nazwa>>wsk->predkosc>>wsk->zaloga>>wsk->wielkosc_zagla>>wsk->liczba_maszt;
            }
            else if(XXX == "5")
            {
                    cout<<"creat "<<XXX<<endl;//TEST
                    odczytF(name);

/*
                    okret *element;
                    okret *wskF = new okret;
                    wskF->next = NULL;

                    element = headF;
                    if(element != NULL)//lista nie pusta
                    {
                        while (element->next) element = element->next;
                        element->next = wskF;
                        cout<<"II"<<endl;
                    }
                    else
                    {
                        headF = wskF; //lista pusta - tmp as 1 node
                        cout<<"I"<<endl;
                    }
                   // plik>>wskF->gps;        cout<<wskF->gps<<endl;
                    plik>>wskF->masa;       cout<<wskF->masa<<endl;
                    plik>>wskF->dlugosc;    cout<<wskF->nazwa<<endl;
                    plik>>wskF->nazwa;      cout<<wskF->dlugosc<<endl;
                    plik>>wskF->predkosc;   cout<<wskF->predkosc<<endl;
                    plik>>wskF->zaloga;     cout<<wskF->zaloga<<endl;
                    plik>>wskF->silaOgniu;  cout<<wskF->silaOgniu<<endl;
                    plik>>wskF->typ;        cout<<wskF->typ<<endl;
                    cout<<" \n"<<wskF->gps<<" "<<wskF->masa<<" "<<wskF->dlugosc<<" "<<wskF->nazwa<<" "<<wskF->predkosc<<" "<<wskF->zaloga<<" "<<wskF->silaOgniu<<" "<<wskF->typ;
*/

            }
            else if(XXX == "6")
            {
                    cout<<"creat "<<XXX<<endl;//TEST
                    batyskaf *element;
                    batyskaf *wsk = new batyskaf;
                    wsk->next = NULL;

                    element = headG;
                    if(element != NULL)//lista nie pusta
                    {
                        while (element->next) element = element->next;
                        element->next = wsk;
                        cout<<"II"<<endl;
                    }
                    else
                    {
                        headG = wsk; //lista pusta - tmp as 1 node
                        cout<<"I"<<endl;
                    }

                    plik>>wsk->gps>>wsk->masa>>wsk->dlugosc>>wsk->nazwa>>wsk->zanurzenie>>wsk->zasieg>>wsk->naped>>wsk->zaloga>>wsk->moc_silnikow;


            }
            else if(XXX == "7")
            {
                    cout<<"creat "<<XXX<<endl;//TEST
                    balon *element;
                    balon *wsk = new balon;
                    wsk->next = NULL;

                    element = headH;
                    if(element != NULL)//lista nie pusta
                    {
                        while (element->next) element = element->next;
                        element->next = wsk;
                        cout<<"II"<<endl;
                    }
                    else
                    {
                        headH = wsk; //lista pusta - tmp as 1 node
                        cout<<"I"<<endl;
                    }

                    plik>>wsk->gps>>wsk->masa>>wsk->dlugosc>>wsk->nazwa>>wsk->wysokosc_lotu>>wsk->ilosc_silnikow>>wsk->rozmiar_czaszy>>wsk->pojemosc_paliwa;
                    if(plik.fail()) break;
            }
            else if(XXX == "8")
            {

                    cout<<"creat "<<XXX<<endl;//TEST
                    samolot *element;
                    samolot *wsk = new samolot;
                    wsk->next = NULL;

                    element = headI;
                    if(element != NULL)//lista nie pusta
                    {
                        while (element->next) element = element->next;
                        element->next = wsk;
                        cout<<"II"<<endl;
                    }
                    else
                    {
                        headI = wsk; //lista pusta - tmp as 1 node
                        cout<<"I"<<endl;
                    }

                    plik>>wsk->gps>>wsk->masa>>wsk->dlugosc>>wsk->nazwa>>wsk->wysokosc_lotu>>wsk->ilosc_silnikow>>wsk->zasieg>>wsk->zaloga;
            }

            if(plik.fail()) break;
        }
    }
};


int main()
{

    menu();
//implementaca wartosci dla macierzy poruszania
matrix[0][1]=matrix[0][2]=matrix[0][3]=matrix[1][4]=matrix[1][5]=matrix[2][6]=matrix[3][7]=matrix[3][8]={1};
matrix[1][0]=matrix[2][0]=matrix[3][0]=matrix[4][1]=matrix[5][1]=matrix[6][2]=matrix[7][3]=matrix[8][3]={1};//should be 2
matrix[4][4]=matrix[5][5]=matrix[6][6]=matrix[7][7]=matrix[8][8]={3};
for(int i=0;i<9;i++)    {for(int j=0;j<9;j++){cout<<  matrix[i][j] <<"  ";}        cout<<"\n";} // drukuje macierz


    statek *wezel = new statek();//wezel do poruszania
    work oW;    zaglowiec oE;    okret oF;    batyskaf oG;    balon oH;    samolot oI;

    int X;


    while(true)
    {
        cout<<endl;
        //cout<<oF.headF<<" - value of head okret"<<endl;
        if(wezel->x == 0)       cout<<"STATEK";
        else if(wezel->x == 1)  cout<<"STATEK>>NADWODNY";
        else if(wezel->x == 2)  cout<<"STATEK>>PODWODNY";
        else if(wezel->x == 3)  cout<<"STATEK>>POWIETRZNY";
        else if(wezel->x == 4)  cout<<"STATEK>>NADWODNY>>ZAGLOWIEC";
        else if(wezel->x == 5)  cout<<"STATEK>>NADWODNY>>OKRET";
        else if(wezel->x == 6)  cout<<"STATEK>>PODWODNY>>BATYSKAF";
        else if(wezel->x == 7)  cout<<"STATEK>>POWIETRZNY>>BALON";
        else if(wezel->x == 8)  cout<<"STATEK>>POWIETRZNY>>SAMOLOT";

        cout<<" >>";
        fflush(stdin);


        string option, MAP;
        cin>>option;
        std::string str = option;

        // Spliting the string by an another std::string
        std::vector<std::string> O = split(str, ".");





        int X = maping(option);

        switch(X) //make map from numbers to comands
        {
        case 1:
            //cout<<"Zmiana wezla w strukturze"<<endl;

            wezel->y = wezel->zmiana_wezla(option);

            wezel->x=wezel->y;//stay on old place if i cant go to smth



            break;

        case 2:
            //cout<<"Dodawanie obiekta"<<endl;
            //cout<<"Wartosc macierzy = "<<matrix[wezel->x][wezel->y]<<endl;
            if(matrix[wezel->x][wezel->y]==3) //warunek if liść
            {
                //cout<<"Nr wezla = "<<wezel->x<<endl;
                if(wezel->x == 4) oE.dodajE(wezel->x);
                else if(wezel->x == 5) oF.dodajF(wezel->x);
                else if(wezel->x == 6) oG.dodajG(wezel->x);
                else if(wezel->x == 7) oH.dodajH(wezel->x);
                else if(wezel->x == 8) oI.dodajI(wezel->x);

            }
            else    cout<<"Na tym poziomie nie mozna stworzyc obiekt"<<endl;
            break;
        case 3:
            //cout<<"Usuwanie obiektu po nazwie"<<endl;
            //cout<<"Podaj nazwe objektu, ktory chcesz usunac: "<<endl;
           // char del[50];  cin>>del;
                oE.usunE(option);
                oF.usunF(option);
                oG.usunG(option);
                oH.usunH(option);
                oI.usunI(option);
            break;
        case 4:
            //cout<<"Modyfikacja obiektu po nazwie"<<endl;
            //cout<<"Podaj nazwe objektu, ktory chcesz zmienic: "<<endl;
            //char name[50];  cin>>name;
            oE.modE(option);
            oF.modF(option);
            oG.modG(option);
            oH.modH(option);
            oI.modI(option);
            break;
        case 5:
            //cout<<"Wyswietlanie wszystkich widocznych obiektow"<<endl;//DIR zmienic

                //cout<<"Nr wezla = "<<wezel->x<<endl;
                if(wezel->x == 0) dirA();
                else if(wezel->x == 1) dirB();
                else if(wezel->x == 2) dirC();
                else if(wezel->x == 3) dirD();
                else if(wezel->x == 4) oE.dirE();
                else if(wezel->x == 5) oF.dirF();
                else if(wezel->x == 6) oG.dirG();
                else if(wezel->x == 7) oH.dirH();
                else if(wezel->x == 8) oI.dirI();



            break;
        case 6:
            //cout<<"Wyswietlanie szczegolnych infromacji o obiekcie"<<endl;
            //cout<<"Podaj nazwe objektu, szczegoly ktorego chcesz sprawdzic: "<<endl;
            //char name1[50];  cin>>name1;
            oE.showE(option);
            oF.showF(option);
            oG.showG(option);
            oH.showH(option);
            oI.showI(option);

            break;
        case 7:
//            work::hE = oE.head;
            //cout<<"Zapis"<<endl;
            oW.saveW(oE.headE, oF.headF, oG.headG, oH.headH, oI.headI);
            break;
        case 8:
            cout<<"Podaj nazwe pliku do odczytu |nazwa.txt| : ";
            char name[100];     cin>>name;
            //cout<<"Odczyt"<<endl;
            oE.odczytE(name);
            oF.odczytF(name);
            oG.odczytG(name);
            oH.odczytH(name);
            oI.odczytI(name);
            //oW.readW(name);
            break;
        case 9:
            //cout<<"Wyswietlanie struktury"<<endl;
            cout<<"\n KLASA I - STATEK"<<endl;
            cout<<"\n     KLASA II - NADWODNY"<<endl;
            cout<<"\n         KLASA III - ZAGLOWIEC"<<endl;            oE.treeE();
            cout<<"\n         KLASA III - OKRET"<<endl;                oF.treeF();
            cout<<"\n     KLASA II - PODWODNY"<<endl;
            cout<<"\n         KLASA III - BATYSKAF"<<endl;             oG.treeG();
            cout<<"\n     KLASA II - POWIETRZNY"<<endl;
            cout<<"\n         KLASA III - BALON"<<endl;                oH.treeH();
            cout<<"\n         KLASA III - SAMOLOT"<<endl;              oI.treeI();
            break;
        case 10:
            break;
        case 11:
            menu();
            break;

        case 0 :               return 0;
        default:    ;
        }
    }
    return 0;
}

int maping(string O)
{
    //char MAP[10];


        std::string str = O;

        // Spliting the string by an another std::string
        std::vector<std::string> MAP = split(str, ".");

    if((MAP[0]=="MENU")||(MAP[0]=="menu"))return 11;
    else if((MAP[0]=="CD")||(MAP[0]=="cd")) return 1;
    else if((MAP[0]=="MO")||(MAP[0]=="mo")) return 2;
    else if((MAP[0]=="DO")||(MAP[0]=="do")) return 3;
    else if((MAP[0]=="MDO")||(MAP[0]=="mdo")) return 4;
    else if((MAP[0]=="DIR")||(MAP[0]=="dir")) return 5;
    else if((MAP[0]=="SHOW")||(MAP[0]=="show")) return 6;
    else if((MAP[0]=="SAVE")||(MAP[0]=="save")) return 7;
    else if((MAP[0]=="READ")||(MAP[0]=="read")) return 8;
    else if((MAP[0]=="TREE")||(MAP[0]=="tree")) return 9;
    else if((MAP[0]=="END")||(MAP[0]=="end")) return 0;
    else{cout<<"niema takiej komandy, sproboj ponownie: "; return 10;}

}
void menu()
{

    cout<<"\n     MENU"<<endl;
    cout<<"CD   - zmiana wezla w strukturze"<<endl;
    cout<<"MO   - stworzenie obiekta"<<endl;
    cout<<"DO   - usuniencie obiekta"<<endl;
    cout<<"MDO  - modyfikacja obiektu"<<endl;
    cout<<"DIR  - wyswietla obiekty widoczne z obecnego poziomu"<<endl;
    cout<<"SHOW - pokazuje szczegolowe informacje o obiekcie"<<endl;
    cout<<"SAVE - zapis do pliku"<<endl;
    cout<<"READ - odczyt z pliku"<<endl;
    cout<<"TREE - wyswietla cala strukture"<<endl;

}
void dirA()
{
    cout<<"\n###STATKI###"<<endl;
    cout<<"\n >>>Nadwodny\n >>>Podwodny\n >>>Powietrzny"<<endl;
}
void dirB()
{
    cout<<"\n###NADWODNE###"<<endl;
    cout<<"\n Zaglowiec\n Okret"<<endl;
}
void dirC()
{
    cout<<"\n###PODWONE###"<<endl;
    cout<<"\n >>>Batyskaf"<<endl;
}
void dirD()
{
    cout<<"\n###POWIETRZNE###"<<endl;
    cout<<"\n >>>Balon\n >>>Samolot"<<endl;
}


