#ifndef ITEM
#define ITEM

#include <string>

class Item
{
	public:

	Item ();
	virtual ~Item ();

	std::string nazwa;    //nazwa przedmiotu
	int item_id;          //numer przedmiotu
	int rodzaj;           //typ przedmiotu ( 0-inne , 1-bron , 2-ammo , 3-stroj )
	int nr_ekw;           //numer ktory zajmuje przedmiot w ekwipunku
	bool zaloz;           //czy przedmiot jest zalozony ( rodzaje 1 2 3 )
	std::string opis[8];  //opis przedmiotu
};

class Inne :public Item
{
	public:

	Inne ();
	~Inne ();

	virtual void uzyj () = 0;

	int koszt_item;       //koszt uzycia przedmiotu
};

class Bron :public Item
{
	public:

	Bron ();
	~Bron ();

	int obrazenia;        //obrazenia broni
	bool czy_dyst;        //czy bron jest dystansowa i moze korzystac z amunicji

	int poj_max;          //ile mozna maksymalnie zaladowac pociskow amunicji
	int ile_ammo;         //liczba odpowiadajacych broni typow amunicji
	int* tab_ammo;        //tablica zawierajaca typy odpowiadajacej broni amunicji
};

class Ammo :public Item
{
	public:

	Ammo ();
	~Ammo ();

	int obrazenia;        //obrazenia amunicji
	int pojemnosc;        //ile poczatkowo pociskow zamiera amunicja
	int przel;            //ile pociskow jest przekazywanych broni podczas przeladowania
};

class Stroj :public Item
{
	public:

	Stroj ();
	~Stroj ();

	int ochrona;          //jaka ochrone zapewnia stroj
};

#endif