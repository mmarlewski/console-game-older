#ifndef MAPA
#define MAPA

#include "pole.h"

class Mapa
{
	public:

	Mapa ();
	~Mapa ();

	Pole* operator[](int);

	void ustal_wyglad ();     //ustala znak i kolor kazdego pola mapy na podstawie obiektow
	void ustal_anim ();       //ustala znak i kolor na podstawie animacji
	void czysc_wyb ();        //zeruje czy_wyb kazdego pola
	void czysc_info ();       //zeruje czy_info kazdego pola
	void czysc_anim ();       //zeruje znak_anim i kolor_anim kazdego pola
	void ustal_poloz ();      //ustala wspolrzedne kazdego obiektu na mapie

	Pole** mapa;
};

#endif