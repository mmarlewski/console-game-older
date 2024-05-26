#ifndef OBIEKT
#define OBIEKT

#include "skill.h"
#include "item.h"

class Obiekt
{
	public:

	Obiekt ();
	~Obiekt ();

	virtual void ustaw_skill () = 0;  //tworzy tablice umiejetnosci
	void zadaj_obr (int);             //zadaje obrazenia uwzgledniajac ochrone stroju
	void dodaj_umiej (Skill*);        //dodaje umiejetnosc do tablicy umiejetnosci
	void dodaj_przedm (Item*);        //dodaje przedmiot do ekwipunku
	void zaloz_przedm (Item*);        //wszystko zwiazane z zalozeniem przedmiotu
	void zdejmij_przedm (Item*);      //wszystko zwiazane ze zdjeciem przedmiotu
	void usun_przedm (Item*);         //usuwa przedmiot z ekwipunku
	void poloz_przedm ();             //ustala nr_przedm kazdego przedmiotu
	void sprawdz_ammo ();             //usuwa amunicje z ekwipunku jesli ta sie wyczerpala
	bool ustal_przel ();              //ustala czy mozna przeladowac bron
	bool ustal_rozl ();               //ustala czy mozna rozladowac bron
	bool ustal_zaloz (Item*);         //ustala czy mozna zalozyc przedmiot

	std::string nazwa;    //nazwa klasy obiektu
	std::string imie;     //imie obiektu
	char symbol;          //znak wyswietlany na miejscu pola z obiektem
	int gracz;            //przynaleznosc do gracza ( 0-zaden gracz , 1-gracz nr1 , 2-gracz nr2 )
	int wysokosc;         //wysokosc obiektu ( 1-mozna przez niego strzelac , 2-nie mozna )
	int wsp_y, wsp_x;     //wspolrzedne obiektu
	int poj_aktual;       //ile zaladowano pociskow amunicji

	Skill** umiejetnosci; //tablica z umiejetnosciami
	Item** ekwipunek;     //tablica z przedmiotami ekwipunku
	Bron* wsk_bron;       //wskaznik na zalozona bron
	Ammo* wsk_ammo;       //wskaznik na zalozona amunicje
	Stroj* wsk_stroj;     //wskaznik na zalozony stroj

	bool czy_umiej;       //czy obiekt posiada umiejetnosci
	bool czy_ekwip;       //czy obiekt posiada ekwipunek
	bool czy_hp;          //czy mozna operowac na zdrowiu
	bool czy_ap;          //czy mozna operowac na punktach ruchu
	int ile_skill;        //liczba aktualnie dostepnych umiejetnosci
	int ekw_aktual;       //liczba przedmiotow wchodzacych w sklad ekwipunku
	int ekw_max;          //maksymalna liczba ptrzedmiotow mogaca tworzyc ekwipunek
	int hp_aktual;        //aktualna ilosc zdrowia
	int hp_max;           //maksymalna ilosc zdrowia
	int ap_aktual;        //aktualna liczba punktow ruchu
	int ap_max;           //maksymalna liczba punktow ruchu
};

#endif