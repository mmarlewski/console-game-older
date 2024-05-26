#ifndef POLE
#define POLE

#include "obiekt.h"

class Pole
{
	public:

	Pole ();
	~Pole ();

	Obiekt* wsk_obiekt;   //wskaznik na obiekt znajdujacy sie na polu
	bool czy_wyb;         //czy pole mozna obrac za cel ( tryb 2 )
	bool czy_info;        //czy pole ma byc specjalnie oznaczone ( tryb 2 )
	char znak_pola;       //znak wyswietlany w miejscu pola
	int kolor_pola;       //kolor znaku wyswietlanego w miejscu pola
	char znak_anim;       //znak bedacy czascia animacji
	int kolor_anim;       //kolor znaku bedacego czescia animacji
};

#endif