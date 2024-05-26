#include "mapa.h"

extern int kurs_y, kurs_x;

Mapa::Mapa ()
{
	// tworzenie mapy

	mapa = new Pole*[23];

	for (int i = 0; i < 23; i++)
	{
		mapa[i] = new Pole[23];
	}
}

Mapa::~Mapa ()
{
	// usuwanie mapy

	for (int i = 0; i < 23; i++)
	{
		delete[] mapa[i];
	}

	delete[] mapa;
}

Pole* Mapa::operator[](int indeks)
{
	return mapa[indeks];
}

void Mapa::ustal_wyglad ()
{
	for (int i = 0; i < 23; i++)
	{
		for (int j = 0; j < 23; j++)
		{
			// jesli na polu znajduje sie obiekt
			if (mapa[i][j].wsk_obiekt)
			{
				// jesli obiekt nalezy do gracza nr1
				if (mapa[i][j].wsk_obiekt->gracz == 1)
				{
					if (kurs_y == i && kurs_x == j) mapa[i][j].kolor_pola = 242;

					else if (mapa[i][j].czy_info) mapa[i][j].kolor_pola = 130;

					else if (mapa[i][j].czy_wyb) mapa[i][j].kolor_pola = 114;

					else  mapa[i][j].kolor_pola = 10;

				}
				// jesli obiekt nalezy do gracza nr2
				else  if (mapa[i][j].wsk_obiekt->gracz == 2)
				{
					if (kurs_y == i && kurs_x == j) mapa[i][j].kolor_pola = 243;

					else if (mapa[i][j].czy_info) mapa[i][j].kolor_pola = 131;

					else if (mapa[i][j].czy_wyb) mapa[i][j].kolor_pola = 115;

					else  mapa[i][j].kolor_pola = 11;
				}
				// jesli obiekt jest neutralny
				else
				{
					if (kurs_y == i && kurs_x == j) mapa[i][j].kolor_pola = 240;

					else if (mapa[i][j].czy_info) mapa[i][j].kolor_pola = 128;

					else if (mapa[i][j].czy_wyb) mapa[i][j].kolor_pola = 112;

					else  mapa[i][j].kolor_pola = 15;
				}

				// znak pola to symbol obiektu
				mapa[i][j].znak_pola = mapa[i][j].wsk_obiekt->symbol;
			}
			// jesli pole jest puste
			else
			{
				if (kurs_y == i && kurs_x == j) mapa[i][j].kolor_pola = 240;

				else if (mapa[i][j].czy_info) mapa[i][j].kolor_pola = 128;

				else if (mapa[i][j].czy_wyb) mapa[i][j].kolor_pola = 112;

				else mapa[i][j].kolor_pola = 0;

				// prostokat
				mapa[i][j].znak_pola = char (32);
			}
		}
	}
}

void Mapa::ustal_anim ()
{
	for (int i = 0; i < 23; i++)
	{
		for (int j = 0; j < 23; j++)
		{
			// jesli pole stanowi czesc animacji
			if (mapa[i][j].znak_anim)
			{
				mapa[i][j].znak_pola = mapa[i][j].znak_anim;
				mapa[i][j].kolor_pola = mapa[i][j].kolor_anim;
			}
			// ( w czasie animacji nie ma na mapie oznaczen i kursora )
			else
			{
				if (mapa[i][j].wsk_obiekt)
				{
					if (mapa[i][j].wsk_obiekt->gracz == 1) mapa[i][j].kolor_pola = 10;

					else  if (mapa[i][j].wsk_obiekt->gracz == 2) mapa[i][j].kolor_pola = 11;

					else mapa[i][j].kolor_pola = 15;

					mapa[i][j].znak_pola = mapa[i][j].wsk_obiekt->symbol;
				}
				else
				{
					mapa[i][j].kolor_pola = 0;

					mapa[i][j].znak_pola = char (32);
				}
			}
		}
	}
}

void Mapa::czysc_wyb ()
{
	for (int i = 0; i < 23; i++)
	{
		for (int j = 0; j < 23; j++)
		{
			mapa[i][j].czy_wyb = 0;
		}
	}
}

void Mapa::czysc_info ()
{
	for (int i = 0; i < 23; i++)
	{
		for (int j = 0; j < 23; j++)
		{
			mapa[i][j].czy_info = 0;
		}
	}
}

void Mapa::czysc_anim ()
{
	for (int i = 0; i < 23; i++)
	{
		for (int j = 0; j < 23; j++)
		{
			mapa[i][j].znak_anim = 0;
			mapa[i][j].kolor_anim = 0;
		}
	}
}

void Mapa::ustal_poloz ()
{
	for (int i = 0; i < 23; i++)
	{
		for (int j = 0; j < 23; j++)
		{
			if (mapa[i][j].wsk_obiekt)
			{
				mapa[i][j].wsk_obiekt->wsp_y = i;
				mapa[i][j].wsk_obiekt->wsp_x = j;
			}
		}
	}
}