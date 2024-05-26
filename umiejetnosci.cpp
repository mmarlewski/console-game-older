#include "mapa.h"
#include "kreska.h"
#include "klasy.h"
#include "umiejetnosci.h"

#include <windows.h>

extern void pokaz ();

extern Mapa mapa;
extern Kreska kreska;
extern Obiekt* jak_obiekt;
extern int kurs_y,kurs_x;

Ruch::Ruch ()
{
	nazwa = "Ruch";
	koszt_skill = 1;

	opis[0] = "Przemieszcz sie";
	opis[1] = "o jedno pole w";
	opis[2] = "kazdym kierunku";
	opis[3] = "";
	opis[4] = "";
	opis[5] = "";
	opis[6] = "";
	opis[7] = "";
}

void Ruch::wybierz ()
{
	if (jak_obiekt->wsp_y > 0 && jak_obiekt->wsp_x > 0)
	{
		if (!mapa[jak_obiekt->wsp_y - 1][jak_obiekt->wsp_x - 1].wsk_obiekt)
			mapa[jak_obiekt->wsp_y - 1][jak_obiekt->wsp_x - 1].czy_wyb = 1;
	}

	if (jak_obiekt->wsp_y > 0)
	{
		if (!mapa[jak_obiekt->wsp_y - 1][jak_obiekt->wsp_x].wsk_obiekt)
			mapa[jak_obiekt->wsp_y - 1][jak_obiekt->wsp_x].czy_wyb = 1;
	}

	if (jak_obiekt->wsp_y > 0 && jak_obiekt->wsp_x < 22)
	{
		if (!mapa[jak_obiekt->wsp_y - 1][jak_obiekt->wsp_x + 1].wsk_obiekt)
			mapa[jak_obiekt->wsp_y - 1][jak_obiekt->wsp_x + 1].czy_wyb = 1;
	}

	if (jak_obiekt->wsp_x > 0)
	{
		if (!mapa[jak_obiekt->wsp_y][jak_obiekt->wsp_x - 1].wsk_obiekt)
			mapa[jak_obiekt->wsp_y][jak_obiekt->wsp_x - 1].czy_wyb = 1;
	}

	if (jak_obiekt->wsp_x < 22)
	{
		if (!mapa[jak_obiekt->wsp_y][jak_obiekt->wsp_x + 1].wsk_obiekt)
			mapa[jak_obiekt->wsp_y][jak_obiekt->wsp_x + 1].czy_wyb = 1;
	}

	if (jak_obiekt->wsp_y < 22 && jak_obiekt->wsp_x > 0)
	{
		if (!mapa[jak_obiekt->wsp_y + 1][jak_obiekt->wsp_x - 1].wsk_obiekt)
			mapa[jak_obiekt->wsp_y + 1][jak_obiekt->wsp_x - 1].czy_wyb = 1;
	}

	if (jak_obiekt->wsp_y < 22)
	{
		if (!mapa[jak_obiekt->wsp_y + 1][jak_obiekt->wsp_x].wsk_obiekt)
			mapa[jak_obiekt->wsp_y + 1][jak_obiekt->wsp_x].czy_wyb = 1;
	}

	if (jak_obiekt->wsp_y < 22 && jak_obiekt->wsp_x < 22)
	{
		if (!mapa[jak_obiekt->wsp_y + 1][jak_obiekt->wsp_x + 1].wsk_obiekt)
			mapa[jak_obiekt->wsp_y + 1][jak_obiekt->wsp_x + 1].czy_wyb = 1;
	}
}

void Ruch::info ()
{
	//
}

void Ruch::cel ()
{
	mapa[kurs_y][kurs_x].wsk_obiekt = jak_obiekt;
	mapa[jak_obiekt->wsp_y][jak_obiekt->wsp_x].wsk_obiekt = 0;
}

//####################################################################################################

Skok::Skok ()
{
	nazwa = "Skok";
	koszt_skill = 3;

	opis[0] = "Przeskocz przez";
	opis[1] = "przeszkode o";
	opis[2] = "wysokosci 1";
	opis[3] = "";
	opis[4] = "";
	opis[5] = "";
	opis[6] = "";
	opis[7] = "";
}

void Skok::wybierz ()
{
	int skill_y, skill_x;
	bool czy_zderz;

	for (int i = 2; i <= 3; i++)
	{
		skill_y = jak_obiekt->wsp_y - i; skill_x = jak_obiekt->wsp_x - i;

		for (int j = 0; j < 8 * i; j++)
		{
			if (skill_y >= 0 && skill_y <= 22 && skill_x >= 0 && skill_x <= 22)
			{
				czy_zderz = 0;

				kreska (jak_obiekt->wsp_y, jak_obiekt->wsp_x, skill_y, skill_x);

				for (int k = 1; k < kreska.ile_pol - 1; k++)
				{
					if (mapa[kreska.y[k]][kreska.x[k]].wsk_obiekt)
					{
						if (mapa[kreska.y[k]][kreska.x[k]].wsk_obiekt->wysokosc == 2)
						{
							czy_zderz = 1; break;
						}
					}
				}

				if (mapa[skill_y][skill_x].wsk_obiekt)
				{
					czy_zderz = 1;
				}

				kreska.usun ();

				if (czy_zderz == 0) mapa[skill_y][skill_x].czy_wyb = 1;
			}

			if (j >= 0 * i && j < 2 * i) skill_x++;
			if (j >= 2 * i && j < 4 * i) skill_y++;
			if (j >= 4 * i && j < 6 * i) skill_x--;
			if (j >= 6 * i && j < 8 * i) skill_y--;
		}
	}
}

void Skok::info ()
{
	//
}

void Skok::cel ()
{
	mapa[kurs_y][kurs_x].wsk_obiekt = jak_obiekt;
	mapa[jak_obiekt->wsp_y][jak_obiekt->wsp_x].wsk_obiekt = 0;
}

//####################################################################################################

Przewrot::Przewrot ()
{
	nazwa = "Przewrot";
	koszt_skill = 2;

	opis[0] = "Zrob przewrot po";
	opis[1] = "plaskim terenie";
	opis[2] = "";
	opis[3] = "";
	opis[4] = "";
	opis[5] = "";
	opis[6] = "";
	opis[7] = "";
}

void Przewrot::wybierz ()
{
	int skill_y, skill_x;
	bool czy_zderz;

	for (int i = 2; i <= 3; i++)
	{
		skill_y = jak_obiekt->wsp_y - i; skill_x = jak_obiekt->wsp_x - i;

		for (int j = 0; j < 8 * i; j++)
		{
			if (skill_y >= 0 && skill_y <= 22 && skill_x >= 0 && skill_x <= 22)
			{
				czy_zderz = 0;

				kreska (jak_obiekt->wsp_y, jak_obiekt->wsp_x, skill_y, skill_x);

				for (int k = 1; k < kreska.ile_pol; k++)
				{
					if (mapa[kreska.y[k]][kreska.x[k]].wsk_obiekt)
					{
						czy_zderz = 1; break;
					}
				}

				kreska.usun ();

				if (czy_zderz == 0) mapa[skill_y][skill_x].czy_wyb = 1;
			}

			if (j >= 0 * i && j < 2 * i) skill_x++;
			if (j >= 2 * i && j < 4 * i) skill_y++;
			if (j >= 4 * i && j < 6 * i) skill_x--;
			if (j >= 6 * i && j < 8 * i) skill_y--;
		}
	}
}

void Przewrot::info ()
{
	//
}

void Przewrot::cel ()
{
	mapa[kurs_y][kurs_x].wsk_obiekt = jak_obiekt;
	mapa[jak_obiekt->wsp_y][jak_obiekt->wsp_x].wsk_obiekt = 0;
}

//####################################################################################################

Bliski_atak::Bliski_atak ()
{
	nazwa = "Bliski atak";
	koszt_skill = 2;

	opis[0] = "Rani przeciwnika";
	opis[1] = "w poblizu";
	opis[2] = "";
	opis[3] = "";
	opis[4] = "";
	opis[5] = "";
	opis[6] = "";
	opis[7] = "";
}

void Bliski_atak::wybierz ()
{
	if (jak_obiekt->wsp_y > 0 && jak_obiekt->wsp_x > 0)
		mapa[jak_obiekt->wsp_y - 1][jak_obiekt->wsp_x - 1].czy_wyb = 1;

	if (jak_obiekt->wsp_y > 0)
		mapa[jak_obiekt->wsp_y - 1][jak_obiekt->wsp_x].czy_wyb = 1;

	if (jak_obiekt->wsp_y > 0 && jak_obiekt->wsp_x < 22)
		mapa[jak_obiekt->wsp_y - 1][jak_obiekt->wsp_x + 1].czy_wyb = 1;

	if (jak_obiekt->wsp_x > 0)
		mapa[jak_obiekt->wsp_y][jak_obiekt->wsp_x - 1].czy_wyb = 1;

	if (jak_obiekt->wsp_x < 22)
		mapa[jak_obiekt->wsp_y][jak_obiekt->wsp_x + 1].czy_wyb = 1;

	if (jak_obiekt->wsp_y < 22 && jak_obiekt->wsp_x > 0)
		mapa[jak_obiekt->wsp_y + 1][jak_obiekt->wsp_x - 1].czy_wyb = 1;

	if (jak_obiekt->wsp_y < 22)
		mapa[jak_obiekt->wsp_y + 1][jak_obiekt->wsp_x].czy_wyb = 1;

	if (jak_obiekt->wsp_y < 22 && jak_obiekt->wsp_x < 22)
		mapa[jak_obiekt->wsp_y + 1][jak_obiekt->wsp_x + 1].czy_wyb = 1;
}

void Bliski_atak::info ()
{
	//
}

void Bliski_atak::cel ()
{
	int obr = jak_obiekt->wsk_bron->obrazenia * 2;

	mapa[kurs_y][kurs_x].znak_anim = 'X';
	mapa[kurs_y][kurs_x].kolor_anim = 12;
	mapa.ustal_anim (); pokaz (); Sleep (500);

	if (mapa[kurs_y][kurs_x].wsk_obiekt) mapa[kurs_y][kurs_x].wsk_obiekt->zadaj_obr (obr);
}

//####################################################################################################

Bliski_zamach::Bliski_zamach ()
{
	nazwa = "Bliski zamach";
	koszt_skill = 3;

	opis[0] = "Rani 3 przeciwnikow";
	opis[1] = "w poblizu naraz";
	opis[2] = "";
	opis[3] = "";
	opis[4] = "";
	opis[5] = "";
	opis[6] = "";
	opis[7] = "";
}

void Bliski_zamach::wybierz ()
{
	if (jak_obiekt->wsp_y > 0) mapa[jak_obiekt->wsp_y - 1][jak_obiekt->wsp_x].czy_wyb = 1;

	if (jak_obiekt->wsp_x > 0) mapa[jak_obiekt->wsp_y][jak_obiekt->wsp_x - 1].czy_wyb = 1;

	if (jak_obiekt->wsp_x < 22) mapa[jak_obiekt->wsp_y][jak_obiekt->wsp_x + 1].czy_wyb = 1;

	if (jak_obiekt->wsp_y < 22) mapa[jak_obiekt->wsp_y + 1][jak_obiekt->wsp_x].czy_wyb = 1;
}

void Bliski_zamach::info ()
{
	mapa[kurs_y][kurs_x].czy_info = 1;

	if (jak_obiekt->wsp_y == kurs_y)
	{
		if (kurs_y > 0) mapa[kurs_y - 1][kurs_x].czy_info = 1;
		if (kurs_y < 22) mapa[kurs_y + 1][kurs_x].czy_info = 1;
	}
	else
	{
		if (kurs_x > 0) mapa[kurs_y][kurs_x - 1].czy_info = 1;
		if (kurs_x < 22) mapa[kurs_y][kurs_x + 1].czy_info = 1;
	}
}

void Bliski_zamach::cel ()
{
	int obr = jak_obiekt->wsk_bron->obrazenia;

	for (int i = 0; i < 23; i++)
	{
		for (int j = 0; j < 23; j++)
		{
			if (mapa[i][j].czy_info)
			{
				mapa[i][j].znak_anim = 'X';
				mapa[i][j].kolor_anim = 12;

				if (mapa[i][j].wsk_obiekt) mapa[i][j].wsk_obiekt->zadaj_obr (obr);
			}
		}
	}

	mapa.ustal_anim (); pokaz (); Sleep (500);
}

//####################################################################################################

Daleki_atak::Daleki_atak ()
{
	nazwa = "Daleki atak";
	koszt_skill = 2;

	opis[0] = "Rani przeciwnika";
	opis[1] = "oddalonego o 1 pole";
	opis[2] = "";
	opis[3] = "";
	opis[4] = "";
	opis[5] = "";
	opis[6] = "";
	opis[7] = "";
}

void Daleki_atak::wybierz ()
{
	int skill_y, skill_x;
	bool czy_zderz;

	skill_y = jak_obiekt->wsp_y - 2; skill_x = jak_obiekt->wsp_x - 2;

	for (int i = 0; i < 8 * 2; i++)
	{
		if (skill_y >= 0 && skill_y <= 22 && skill_x >= 0 && skill_x <= 22)
		{
			czy_zderz = 0;

			kreska (jak_obiekt->wsp_y, jak_obiekt->wsp_x, skill_y, skill_x);

			for (int k = 1; k < kreska.ile_pol - 1; k++)
			{
				if (mapa[kreska.y[k]][kreska.x[k]].wsk_obiekt)
				{
					if (mapa[kreska.y[k]][kreska.x[k]].wsk_obiekt->wysokosc == 2)
					{
						czy_zderz = 1; break;
					}
				}

				kreska.usun ();

				if (czy_zderz == 0) mapa[skill_y][skill_x].czy_wyb = 1;
			}

			if (i >= 0 * 2 && i < 2 * 2) skill_x++;
			if (i >= 2 * 2 && i < 4 * 2) skill_y++;
			if (i >= 4 * 2 && i < 6 * 2) skill_x--;
			if (i >= 6 * 2 && i < 8 * 2) skill_y--;

		}
	}
}

void Daleki_atak::info ()
{
	//
}

void Daleki_atak::cel ()
{
	int obr = jak_obiekt->wsk_bron->obrazenia * 2;

	mapa[kurs_y][kurs_x].znak_anim = 'X';
	mapa[kurs_y][kurs_x].kolor_anim = 12;
	mapa.ustal_anim (); pokaz (); Sleep (500);

	if (mapa[kurs_y][kurs_x].wsk_obiekt) mapa[kurs_y][kurs_x].wsk_obiekt->zadaj_obr (obr);
}

//####################################################################################################

Przebicie::Przebicie ()
{
	nazwa = "Przebicie";
	koszt_skill = 3;

	opis[0] = "Rani przeciwnika w";
	opis[1] = "w poblizu oraz";
	opis[2] = "przeciwnika za nim";
	opis[3] = "";
	opis[4] = "";
	opis[5] = "";
	opis[6] = "";
	opis[7] = "";
}

void Przebicie::wybierz ()
{
	if (jak_obiekt->wsp_y > 0 && jak_obiekt->wsp_x > 0)
		mapa[jak_obiekt->wsp_y - 1][jak_obiekt->wsp_x - 1].czy_wyb = 1;

	if (jak_obiekt->wsp_y > 0)
		mapa[jak_obiekt->wsp_y - 1][jak_obiekt->wsp_x].czy_wyb = 1;

	if (jak_obiekt->wsp_y > 0 && jak_obiekt->wsp_x < 22)
		mapa[jak_obiekt->wsp_y - 1][jak_obiekt->wsp_x + 1].czy_wyb = 1;

	if (jak_obiekt->wsp_x > 0)
		mapa[jak_obiekt->wsp_y][jak_obiekt->wsp_x - 1].czy_wyb = 1;

	if (jak_obiekt->wsp_x < 22)
		mapa[jak_obiekt->wsp_y][jak_obiekt->wsp_x + 1].czy_wyb = 1;

	if (jak_obiekt->wsp_y < 22 && jak_obiekt->wsp_x > 0)
		mapa[jak_obiekt->wsp_y + 1][jak_obiekt->wsp_x - 1].czy_wyb = 1;

	if (jak_obiekt->wsp_y < 22)
		mapa[jak_obiekt->wsp_y + 1][jak_obiekt->wsp_x].czy_wyb = 1;

	if (jak_obiekt->wsp_y < 22 && jak_obiekt->wsp_x < 22)
		mapa[jak_obiekt->wsp_y + 1][jak_obiekt->wsp_x + 1].czy_wyb = 1;
}

void Przebicie::info ()
{
	mapa[kurs_y][kurs_x].czy_info = 1;

	if (jak_obiekt->wsp_y - kurs_y < 0 && kurs_y < 22)
	{
		if (jak_obiekt->wsp_x - kurs_x < 0 && kurs_x < 22) mapa[kurs_y + 1][kurs_x + 1].czy_info = 1;
		else if (jak_obiekt->wsp_x - kurs_x > 0 && kurs_x > 0) mapa[kurs_y + 1][kurs_x - 1].czy_info = 1;
		else if (jak_obiekt->wsp_x - kurs_x == 0) mapa[kurs_y + 1][kurs_x].czy_info = 1;
	}
	else if (jak_obiekt->wsp_y - kurs_y > 0 && kurs_y > 0)
	{
		if (jak_obiekt->wsp_x - kurs_x < 0 && kurs_x < 22) mapa[kurs_y - 1][kurs_x + 1].czy_info = 1;
		else if (jak_obiekt->wsp_x - kurs_x > 0 && kurs_x > 0) mapa[kurs_y - 1][kurs_x - 1].czy_info = 1;
		else if (jak_obiekt->wsp_x - kurs_x == 0) mapa[kurs_y - 1][kurs_x].czy_info = 1;
	}
	else if (jak_obiekt->wsp_y - kurs_y == 0)
	{
		if (jak_obiekt->wsp_x - kurs_x < 0 && kurs_x < 22) mapa[kurs_y][kurs_x + 1].czy_info = 1;
		else if (jak_obiekt->wsp_x - kurs_x > 0 && kurs_x > 0) mapa[kurs_y][kurs_x - 1].czy_info = 1;
	}
}

void Przebicie::cel ()
{
	int obr = jak_obiekt->wsk_bron->obrazenia;

	for (int i = 0; i < 23; i++)
	{
		for (int j = 0; j < 23; j++)
		{
			if (mapa[i][j].czy_info)
			{
				mapa[i][j].znak_anim = 'X';
				mapa[i][j].kolor_anim = 12;

				if (mapa[i][j].wsk_obiekt) mapa[i][j].wsk_obiekt->zadaj_obr (obr);
			}
		}
	}

	mapa.ustal_anim (); pokaz (); Sleep (500);
}

//####################################################################################################

Pojedynczy_strzal::Pojedynczy_strzal ()
{
	nazwa = "Pojedynczy strzal";
	koszt_skill = 3;

	opis[0] = "Strzela 1 pociskiem";
	opis[1] = "z magazynku";
	opis[2] = "";
	opis[3] = "";
	opis[4] = "";
	opis[5] = "";
	opis[6] = "";
	opis[7] = "";
}

void Pojedynczy_strzal::wybierz ()
{
	int skill_y, skill_x;
	bool czy_zderz;

	for (int i = 3; i <= 7; i++)
	{
		skill_y = jak_obiekt->wsp_y - i; skill_x = jak_obiekt->wsp_x - i;

		for (int j = 0; j < 8 * i; j++)
		{
			if (skill_y >= 0 && skill_y <= 22 && skill_x >= 0 && skill_x <= 22)
			{
				czy_zderz = 0;

				kreska (jak_obiekt->wsp_y, jak_obiekt->wsp_x, skill_y, skill_x);

				for (int k = 1; k < kreska.ile_pol - 1; k++)
				{
					if (mapa[kreska.y[k]][kreska.x[k]].wsk_obiekt)
					{
						if (mapa[kreska.y[k]][kreska.x[k]].wsk_obiekt->wysokosc == 2)
						{
							czy_zderz = 1; break;
						}
					}
				}

				kreska.usun ();

				if (czy_zderz == 0) mapa[skill_y][skill_x].czy_wyb = 1;
			}

			if (j >= 0 * i && j < 2 * i) skill_x++;
			if (j >= 2 * i && j < 4 * i) skill_y++;
			if (j >= 4 * i && j < 6 * i) skill_x--;
			if (j >= 6 * i && j < 8 * i) skill_y--;
		}
	}
}

void Pojedynczy_strzal::info ()
{
	//
}

void Pojedynczy_strzal::cel ()
{
	int obr = jak_obiekt->wsk_bron->obrazenia + jak_obiekt->wsk_ammo->obrazenia;

	mapa[kurs_y][kurs_x].znak_anim = 'X';
	mapa[kurs_y][kurs_x].kolor_anim = 12;
	mapa.ustal_anim (); pokaz (); Sleep (500);

	if (mapa[kurs_y][kurs_x].wsk_obiekt) mapa[kurs_y][kurs_x].wsk_obiekt->zadaj_obr (obr);

	jak_obiekt->poj_aktual -= 1;
}

//####################################################################################################

Podwojny_strzal::Podwojny_strzal ()
{
	nazwa = "Podwojny strzal";
	koszt_skill = 3;

	opis[0] = "Strzela 2 pociskami";
	opis[1] = "z magazynku";
	opis[2] = "";
	opis[3] = "";
	opis[4] = "";
	opis[5] = "";
	opis[6] = "";
	opis[7] = "";
}

void Podwojny_strzal::wybierz ()
{
	int skill_y, skill_x;
	bool czy_zderz;

	for (int i = 3; i <= 7; i++)
	{
		skill_y = jak_obiekt->wsp_y - i; skill_x = jak_obiekt->wsp_x - i;

		for (int j = 0; j < 8 * i; j++)
		{
			if (skill_y >= 0 && skill_y <= 22 && skill_x >= 0 && skill_x <= 22)
			{
				czy_zderz = 0;

				kreska (jak_obiekt->wsp_y, jak_obiekt->wsp_x, skill_y, skill_x);

				for (int k = 1; k < kreska.ile_pol - 1; k++)
				{
					if (mapa[kreska.y[k]][kreska.x[k]].wsk_obiekt)
					{
						if (mapa[kreska.y[k]][kreska.x[k]].wsk_obiekt->wysokosc == 2)
						{
							czy_zderz = 1; break;
						}
					}
				}

				kreska.usun ();

				if (czy_zderz == 0) mapa[skill_y][skill_x].czy_wyb = 1;
			}

			if (j >= 0 * i && j < 2 * i) skill_x++;
			if (j >= 2 * i && j < 4 * i) skill_y++;
			if (j >= 4 * i && j < 6 * i) skill_x--;
			if (j >= 6 * i && j < 8 * i) skill_y--;
		}
	}
}

void Podwojny_strzal::info ()
{
	//
}

void Podwojny_strzal::cel ()
{
	int obr = jak_obiekt->wsk_bron->obrazenia + jak_obiekt->wsk_ammo->obrazenia;

	mapa[kurs_y][kurs_x].znak_anim = 'X';
	mapa[kurs_y][kurs_x].kolor_anim = 12;
	mapa.ustal_anim (); pokaz (); Sleep (500);

	if (mapa[kurs_y][kurs_x].wsk_obiekt)
	{
		mapa[kurs_y][kurs_x].wsk_obiekt->zadaj_obr (obr);
		mapa[kurs_y][kurs_x].wsk_obiekt->zadaj_obr (obr);
	}

	jak_obiekt->poj_aktual -= 2;
}


//####################################################################################################

Dzgnij_bagnetem::Dzgnij_bagnetem ()
{
	nazwa = "Dzgnij bagnetem";
	koszt_skill = 2;

	opis[0] = "Rani przeciwnika";
	opis[1] = "w poblizu";
	opis[2] = "";
	opis[3] = "";
	opis[4] = "";
	opis[5] = "";
	opis[6] = "";
	opis[7] = "";
}

void Dzgnij_bagnetem::wybierz ()
{
	if (jak_obiekt->wsp_y > 0 && jak_obiekt->wsp_x > 0)
		mapa[jak_obiekt->wsp_y - 1][jak_obiekt->wsp_x - 1].czy_wyb = 1;

	if (jak_obiekt->wsp_y > 0)
		mapa[jak_obiekt->wsp_y - 1][jak_obiekt->wsp_x].czy_wyb = 1;

	if (jak_obiekt->wsp_y > 0 && jak_obiekt->wsp_x < 22)
		mapa[jak_obiekt->wsp_y - 1][jak_obiekt->wsp_x + 1].czy_wyb = 1;

	if (jak_obiekt->wsp_x > 0)
		mapa[jak_obiekt->wsp_y][jak_obiekt->wsp_x - 1].czy_wyb = 1;

	if (jak_obiekt->wsp_x < 22)
		mapa[jak_obiekt->wsp_y][jak_obiekt->wsp_x + 1].czy_wyb = 1;

	if (jak_obiekt->wsp_y < 22 && jak_obiekt->wsp_x > 0)
		mapa[jak_obiekt->wsp_y + 1][jak_obiekt->wsp_x - 1].czy_wyb = 1;

	if (jak_obiekt->wsp_y < 22)
		mapa[jak_obiekt->wsp_y + 1][jak_obiekt->wsp_x].czy_wyb = 1;

	if (jak_obiekt->wsp_y < 22 && jak_obiekt->wsp_x < 22)
		mapa[jak_obiekt->wsp_y + 1][jak_obiekt->wsp_x + 1].czy_wyb = 1;
}

void Dzgnij_bagnetem::info ()
{
	//
}

void Dzgnij_bagnetem::cel ()
{
	int obr = jak_obiekt->wsk_bron->obrazenia;

	mapa[kurs_y][kurs_x].znak_anim = 'X';
	mapa[kurs_y][kurs_x].kolor_anim = 12;
	mapa.ustal_anim (); pokaz (); Sleep (500);

	if (mapa[kurs_y][kurs_x].wsk_obiekt) mapa[kurs_y][kurs_x].wsk_obiekt->zadaj_obr (obr);
}

//####################################################################################################

Rzuc_kamieniem::Rzuc_kamieniem ()
{
	nazwa = "Rzuc kamieniem";
	koszt_skill = 1;

	opis[0] = "Kamien";
	opis[1] = "";
	opis[2] = "";
	opis[3] = "";
	opis[4] = "";
	opis[5] = "";
	opis[6] = "";
	opis[7] = "";
}

void Rzuc_kamieniem::wybierz ()
{
	int skill_y, skill_x;
	bool czy_zderz;

	for (int i = 1; i <= 5; i++)
	{
		skill_y = jak_obiekt->wsp_y - i; skill_x = jak_obiekt->wsp_x - i;

		for (int j = 0; j < 8 * i; j++)
		{
			if (skill_y >= 0 && skill_y <= 22 && skill_x >= 0 && skill_x <= 22)
			{
				czy_zderz = 0;

				kreska (jak_obiekt->wsp_y, jak_obiekt->wsp_x, skill_y, skill_x);

				for (int k = 1; k < kreska.ile_pol - 1; k++)
				{
					if (mapa[kreska.y[k]][kreska.x[k]].wsk_obiekt)
					{
						if (mapa[kreska.y[k]][kreska.x[k]].wsk_obiekt->wysokosc == 2)
						{
							czy_zderz = 1; break;
						}
					}
				}

				kreska.usun ();

				if (czy_zderz == 0) mapa[skill_y][skill_x].czy_wyb = 1;
			}

			if (j >= 0 * i && j < 2 * i) skill_x++;
			if (j >= 2 * i && j < 4 * i) skill_y++;
			if (j >= 4 * i && j < 6 * i) skill_x--;
			if (j >= 6 * i && j < 8 * i) skill_y--;
		}
	}
}

void Rzuc_kamieniem::info ()
{
	//
}

void Rzuc_kamieniem::cel ()
{
	int obr = jak_obiekt->wsk_ammo->obrazenia;

	mapa[kurs_y][kurs_x].znak_anim = 'X';
	mapa[kurs_y][kurs_x].kolor_anim = 12;
	mapa.ustal_anim (); pokaz (); Sleep (500);

	if (mapa[kurs_y][kurs_x].wsk_obiekt) mapa[kurs_y][kurs_x].wsk_obiekt->zadaj_obr (obr);

	jak_obiekt->poj_aktual -= 1;
}


//####################################################################################################

Piorun::Piorun ()
{
	nazwa = "Piorun";
	koszt_skill = 3;

	opis[0] = "Rani kazdego w lini";
	opis[1] = "";
	opis[2] = "";
	opis[3] = "";
	opis[4] = "";
	opis[5] = "";
	opis[6] = "";
	opis[7] = "";
}

void Piorun::wybierz ()
{
	int skill_y, skill_x;
	bool czy_zderz;

	for (int i = 1; i <= 5; i++)
	{
		skill_y = jak_obiekt->wsp_y - i; skill_x = jak_obiekt->wsp_x - i;

		for (int j = 0; j < 8 * i; j++)
		{
			if (skill_y >= 0 && skill_y <= 22 && skill_x >= 0 && skill_x <= 22)
			{
				czy_zderz = 0;

				kreska (jak_obiekt->wsp_y, jak_obiekt->wsp_x, skill_y, skill_x);

				for (int k = 1; k < kreska.ile_pol - 1; k++)
				{
					if (mapa[kreska.y[k]][kreska.x[k]].wsk_obiekt)
					{
						if (mapa[kreska.y[k]][kreska.x[k]].wsk_obiekt->wysokosc == 2)
						{
							czy_zderz = 1; break;
						}
					}
				}

				kreska.usun ();

				if (czy_zderz == 0) mapa[skill_y][skill_x].czy_wyb = 1;
			}

			if (j >= 0 * i && j < 2 * i) skill_x++;
			if (j >= 2 * i && j < 4 * i) skill_y++;
			if (j >= 4 * i && j < 6 * i) skill_x--;
			if (j >= 6 * i && j < 8 * i) skill_y--;
		}
	}
}

void Piorun::info ()
{
	kreska (jak_obiekt->wsp_y, jak_obiekt->wsp_x, kurs_y, kurs_x);

	for (int i = 1; i < kreska.ile_pol; i++)
	{
		mapa[kreska.y[i]][kreska.x[i]].czy_info = 1;
	}

	kreska.usun ();
}

void Piorun::cel ()
{
	int obr = 3;

	bool piorun;

	for (int k = 0; k < 3; k++)
	{
		if (k != 2) piorun = k;

		for (int i = 0; i < 23; i++)
		{
			for (int j = 0; j < 23; j++)
			{
				if (mapa[i][j].czy_info)
				{
					if (k != 2)
					{
						mapa[i][j].znak_anim = (piorun) ? ('/') : ('\\');
						mapa[i][j].kolor_anim = 14;

						piorun = !piorun;
					}
					else if (mapa[i][j].wsk_obiekt) mapa[i][j].wsk_obiekt->zadaj_obr (obr);
				}
			}
		}

		if (k != 2)
		{
			mapa.ustal_anim (); pokaz (); Sleep (500);
		}
	}
}

//####################################################################################################

Fireball::Fireball ()
{
	nazwa = "Fireball";
	koszt_skill = 5;

	opis[0] = "Rani cel i kazdego";
	opis[1] = "wokol w promieniu";
	opis[2] = "1 pola oraz kazdego";
	opis[3] = "w lini";
	opis[4] = "";
	opis[5] = "";
	opis[6] = "";
	opis[7] = "";
}

void Fireball::wybierz ()
{
	int skill_y, skill_x;
	bool czy_zderz;

	for (int i = 1; i <= 5; i++)
	{
		skill_y = jak_obiekt->wsp_y - i; skill_x = jak_obiekt->wsp_x - i;

		for (int j = 0; j < 8 * i; j++)
		{
			if (skill_y >= 0 && skill_y <= 22 && skill_x >= 0 && skill_x <= 22)
			{
				czy_zderz = 0;

				kreska (jak_obiekt->wsp_y, jak_obiekt->wsp_x, skill_y, skill_x);

				for (int k = 1; k < kreska.ile_pol - 1; k++)
				{
					if (mapa[kreska.y[k]][kreska.x[k]].wsk_obiekt)
					{
						if (mapa[kreska.y[k]][kreska.x[k]].wsk_obiekt->wysokosc == 2)
						{
							czy_zderz = 1; break;
						}
					}
				}

				kreska.usun ();

				if (czy_zderz == 0) mapa[skill_y][skill_x].czy_wyb = 1;
			}

			if (j >= 0 * i && j < 2 * i) skill_x++;
			if (j >= 2 * i && j < 4 * i) skill_y++;
			if (j >= 4 * i && j < 6 * i) skill_x--;
			if (j >= 6 * i && j < 8 * i) skill_y--;
		}
	}
}

void Fireball::info ()
{
	kreska (jak_obiekt->wsp_y, jak_obiekt->wsp_x, kurs_y, kurs_x);

	for (int i = 1; i < kreska.ile_pol - 1; i++)
	{
		mapa[kreska.y[i]][kreska.x[i]].czy_info = 1;
	}

	kreska.usun ();

	if (kurs_y > 0 && kurs_x > 0) mapa[kurs_y - 1][kurs_x - 1].czy_info = 1;
	if (kurs_y > 0) mapa[kurs_y - 1][kurs_x].czy_info = 1;
	if (kurs_y > 0 && kurs_x < 22) mapa[kurs_y - 1][kurs_x + 1].czy_info = 1;
	if (kurs_x > 0) mapa[kurs_y][kurs_x - 1].czy_info = 1;
	if (kurs_x < 22) mapa[kurs_y][kurs_x + 1].czy_info = 1;
	if (kurs_y < 22 && kurs_x > 0) mapa[kurs_y + 1][kurs_x - 1].czy_info = 1;
	if (kurs_y < 22) mapa[kurs_y + 1][kurs_x].czy_info = 1;
	if (kurs_y < 22 && kurs_x < 22) mapa[kurs_y + 1][kurs_x + 1].czy_info = 1;
}

void Fireball::cel ()
{
	int obr1 = jak_obiekt->wsk_bron->obrazenia;
	int obr2 = jak_obiekt->wsk_bron->obrazenia * 2;

	kreska (jak_obiekt->wsp_y, jak_obiekt->wsp_x, kurs_y, kurs_x);

	for (int i = 2; i < kreska.ile_pol; i++)
	{
		for (int j = 1; j < i; j++)
		{
			if (j == i - 1)
			{
				mapa[kreska.y[j]][kreska.x[j]].znak_anim = 'X';
				mapa[kreska.y[j]][kreska.x[j]].kolor_anim = 12;
			}
			else
			{
				mapa[kreska.y[j]][kreska.x[j]].znak_anim = '*';
				mapa[kreska.y[j]][kreska.x[j]].kolor_anim = 8;
			}
		}

		mapa.ustal_anim (); pokaz (); Sleep (500);
	}

	for (int i = 0; i < 23; i++)
	{
		for (int j = 0; j < 23; j++)
		{
			if (mapa[i][j].czy_info && mapa[i][j].wsk_obiekt) mapa[i][j].wsk_obiekt->zadaj_obr (obr1);
		}
	}

	if (mapa[kurs_y][kurs_x].wsk_obiekt) mapa[kurs_y][kurs_x].wsk_obiekt->zadaj_obr (obr2);

	for (int i = 1; i < kreska.ile_pol - 2; i++)
	{
		mapa[kreska.y[i]][kreska.x[i]].czy_info = 0;
	}

	for (int k = 0; k < 2; k++)
	{
		mapa[kurs_y][kurs_x].znak_anim = 'X';
		mapa[kurs_y][kurs_x].kolor_anim = 12;

		for (int i = 1; i < kreska.ile_pol - 1; i++)
		{
			mapa[kreska.y[i]][kreska.x[i]].znak_anim= '*';
			mapa[kreska.y[i]][kreska.x[i]].kolor_anim = 8;
		}

		if (k == 1)
		{
			for (int i = 0; i < 23; i++)
			{
				for (int j = 0; j < 23; j++)
				{
					if (mapa[i][j].czy_info)
					{
						mapa[i][j].znak_anim = 'X';
						mapa[i][j].kolor_anim = 12;
					}
				}
			}
		}

		mapa.ustal_anim (); pokaz (); Sleep (500);
	}

	kreska.usun ();
}

//####################################################################################################

Pozar::Pozar ()
{
	nazwa = "Pozar";
	koszt_skill = 5;

	opis[0] = "Rani kazdego w ";
	opis[1] = "promieniu 45 stopni";
	opis[2] = "na odleglosc 5 pol";
	opis[3] = "";
	opis[4] = "";
	opis[5] = "";
	opis[6] = "";
	opis[7] = "";
}

void Pozar::wybierz ()
{
	if (jak_obiekt->wsp_y > 0) mapa[jak_obiekt->wsp_y - 1][jak_obiekt->wsp_x].czy_wyb = 1;
	if (jak_obiekt->wsp_x > 0) mapa[jak_obiekt->wsp_y][jak_obiekt->wsp_x - 1].czy_wyb = 1;
	if (jak_obiekt->wsp_x < 22) mapa[jak_obiekt->wsp_y][jak_obiekt->wsp_x + 1].czy_wyb = 1;
	if (jak_obiekt->wsp_y < 22) mapa[jak_obiekt->wsp_y + 1][jak_obiekt->wsp_x].czy_wyb = 1;
}

void Pozar::info ()
{
	int skill_y, skill_x;

	for (int i = 0; i < 5; i++)
	{
		if (jak_obiekt->wsp_y - kurs_y < 0) { skill_y = jak_obiekt->wsp_y + i + 1; skill_x = jak_obiekt->wsp_x - i; }
		if (jak_obiekt->wsp_y - kurs_y > 0) { skill_y = jak_obiekt->wsp_y - i - 1; skill_x = jak_obiekt->wsp_x - i; }
		if (jak_obiekt->wsp_x - kurs_x < 0) { skill_y = jak_obiekt->wsp_y - i; skill_x = jak_obiekt->wsp_x + i + 1; }
		if (jak_obiekt->wsp_x - kurs_x > 0) { skill_y = jak_obiekt->wsp_y - i; skill_x = jak_obiekt->wsp_x - i - 1; }

		for (int j = 0; j < 2 * i + 1; j++)
		{
			if (skill_y >= 0 && skill_y <= 22 && skill_x >= 0 && skill_x <= 22)
			{
				mapa[skill_y][skill_x].czy_info = 1;
			}

			if (jak_obiekt->wsp_y - kurs_y != 0) skill_x++;
			if (jak_obiekt->wsp_x - kurs_x != 0) skill_y++;
		}
	}
}

void Pozar::cel ()
{
	int obr = jak_obiekt->wsk_bron->obrazenia;

	for (int k = 1; k <= 5; k++)
	{
		for (int i = 0; i < k; i++)
		{
			for (int j = 0; j < 23; j++)
			{
				if (jak_obiekt->wsp_y - kurs_y > 0)
				{
					if (mapa[kurs_y - i][j].czy_info)
					{
						mapa[kurs_y - i][j].znak_anim = 'X';
						mapa[kurs_y - i][j].kolor_anim = 12;
					}
				}

				if (jak_obiekt->wsp_y - kurs_y < 0)
				{
					if (mapa[kurs_y + i][j].czy_info)
					{
						mapa[kurs_y + i][j].znak_anim = 'X';
						mapa[kurs_y + i][j].kolor_anim = 12;
					}
				}

				if (jak_obiekt->wsp_x - kurs_x > 0)
				{
					if (mapa[j][kurs_x - i].czy_info)
					{
						mapa[j][kurs_x - i].znak_anim = 'X';
						mapa[j][kurs_x - i].kolor_anim = 12;
					}
				}

				if (jak_obiekt->wsp_x - kurs_x < 0)
				{
					if (mapa[j][kurs_x + i].czy_info)
					{
						mapa[j][kurs_x + i].znak_anim = 'X';
						mapa[j][kurs_x + i].kolor_anim = 12;
					}
				}
			}
		}

		mapa.ustal_anim (); pokaz (); Sleep (500);
	}

	for (int i = 0; i < 23; i++)
	{
		for (int j = 0; j < 23; j++)
		{
			if (mapa[i][j].wsk_obiekt && mapa[i][j].czy_info)
			{
				mapa[i][j].wsk_obiekt->zadaj_obr (obr);
			}
		}
	}
}

//####################################################################################################

Lodowy_kolec::Lodowy_kolec ()
{
	nazwa = "Lodowy kolec";
	koszt_skill = 3;

	opis[0] = "Moze przebic co";
	opis[1] = "najmniej jednego";
	opis[2] = "przeciwnika";
	opis[3] = "";
	opis[4] = "";
	opis[5] = "";
	opis[6] = "";
	opis[7] = "";
}

void Lodowy_kolec::wybierz ()
{
	int skill_y, skill_x;
	int przebicie;

	for (int i = 1; i <= 5; i++)
	{
		skill_y = jak_obiekt->wsp_y - i; skill_x = jak_obiekt->wsp_x - i;

		for (int j = 0; j < 8 * i; j++)
		{
			if (skill_y >= 0 && skill_y <= 22 && skill_x >= 0 && skill_x <= 22)
			{
				przebicie = 0;

				kreska (jak_obiekt->wsp_y, jak_obiekt->wsp_x, skill_y, skill_x);

				for (int k = 1; k < kreska.ile_pol - 1; k++)
				{
					if (mapa[kreska.y[k]][kreska.x[k]].wsk_obiekt)
					{
						if (mapa[kreska.y[k]][kreska.x[k]].wsk_obiekt->wysokosc == 2)
						{
							przebicie++;
						}
					}
				}

				kreska.usun ();

				if (przebicie <= 1) mapa[skill_y][skill_x].czy_wyb = 1;
			}

			if (j >= 0 * i && j < 2 * i) skill_x++;
			if (j >= 2 * i && j < 4 * i) skill_y++;
			if (j >= 4 * i && j < 6 * i) skill_x--;
			if (j >= 6 * i && j < 8 * i) skill_y--;
		}
	}
}

void Lodowy_kolec::info ()
{
	kreska (jak_obiekt->wsp_y, jak_obiekt->wsp_x, kurs_y, kurs_x);

	for (int i = 1; i < kreska.ile_pol - 1; i++)
	{
		mapa[kreska.y[i]][kreska.x[i]].czy_info = 1;
	}

	kreska.usun ();
}

void Lodowy_kolec::cel ()
{
	int obr = jak_obiekt->wsk_bron->obrazenia;

	kreska (jak_obiekt->wsp_y, jak_obiekt->wsp_x, kurs_y, kurs_x);

	for (int i = 1; i < kreska.ile_pol - 1; i++)
	{
		if (mapa[kreska.y[i]][kreska.x[i]].wsk_obiekt)
		{
			if (mapa[kreska.y[i]][kreska.x[i]].wsk_obiekt->wysokosc == 2)
			{
				mapa[kreska.y[i]][kreska.x[i]].znak_anim = 'X';
				mapa[kreska.y[i]][kreska.x[i]].kolor_anim = 12;
				mapa.ustal_anim (); pokaz (); Sleep (500);
				mapa[kreska.y[i]][kreska.x[i]].znak_anim = 0;

				mapa[kreska.y[i]][kreska.x[i]].wsk_obiekt->zadaj_obr (obr);
			}
			else
			{
				mapa[kreska.y[i]][kreska.x[i]].znak_anim = '*';
				mapa[kreska.y[i]][kreska.x[i]].kolor_anim = 11;
				mapa.ustal_anim (); pokaz (); Sleep (100);
				mapa[kreska.y[i]][kreska.x[i]].znak_anim = 0;
			}
		}
		else
		{
			mapa[kreska.y[i]][kreska.x[i]].znak_anim = '*';
			mapa[kreska.y[i]][kreska.x[i]].kolor_anim = 11;
			mapa.ustal_anim (); pokaz (); Sleep (100);
			mapa[kreska.y[i]][kreska.x[i]].znak_anim = 0;
		}
	}

	kreska.usun ();

	mapa[kurs_y][kurs_x].znak_anim = 'X';
	mapa[kurs_y][kurs_x].kolor_anim = 12;
	mapa.ustal_anim (); pokaz (); Sleep (500);

	if (mapa[kurs_y][kurs_x].wsk_obiekt) mapa[kurs_y][kurs_x].wsk_obiekt->zadaj_obr (obr);
}

//####################################################################################################

Lodowa_pulapka::Lodowa_pulapka ()
{
	nazwa = "Lodowa pulapka";
	koszt_skill = 5;

	opis[0] = "Tworzy bryly lodu";
	opis[1] = "lub rani w promieniu";
	opis[2] = "1 pola wokol celu";
	opis[3] = "";
	opis[4] = "";
	opis[5] = "";
	opis[6] = "";
	opis[7] = "";
}

void Lodowa_pulapka::wybierz ()
{
	int skill_y, skill_x;

	for (int i = 1; i <= 5; i++)
	{
		skill_y = jak_obiekt->wsp_y - i; skill_x = jak_obiekt->wsp_x - i;

		for (int j = 0; j < 8 * i; j++)
		{
			if (skill_y >= 0 && skill_y <= 22 && skill_x >= 0 && skill_x <= 22)
			{
				mapa[skill_y][skill_x].czy_wyb = 1;
			}

			if (j >= 0 * i && j < 2 * i) skill_x++;
			if (j >= 2 * i && j < 4 * i) skill_y++;
			if (j >= 4 * i && j < 6 * i) skill_x--;
			if (j >= 6 * i && j < 8 * i) skill_y--;
		}
	}
}

void Lodowa_pulapka::info ()
{
	if (kurs_y > 0 && kurs_x > 0) mapa[kurs_y - 1][kurs_x - 1].czy_info = 1;
	if (kurs_y > 0) mapa[kurs_y - 1][kurs_x].czy_info = 1;
	if (kurs_y > 0 && kurs_x < 22) mapa[kurs_y - 1][kurs_x + 1].czy_info = 1;
	if (kurs_x > 0) mapa[kurs_y][kurs_x - 1].czy_info = 1;
	if (kurs_x < 22) mapa[kurs_y][kurs_x + 1].czy_info = 1;
	if (kurs_y < 22 && kurs_x > 0) mapa[kurs_y + 1][kurs_x - 1].czy_info = 1;
	if (kurs_y < 22) mapa[kurs_y + 1][kurs_x].czy_info = 1;
	if (kurs_y < 22 && kurs_x < 22) mapa[kurs_y + 1][kurs_x + 1].czy_info = 1;
}

void Lodowa_pulapka::cel ()
{
	int obr = jak_obiekt->wsk_bron->obrazenia;

	for (int i = 0; i < 23; i++)
	{
		for (int j = 0; j < 23; j++)
		{
			if (mapa[i][j].czy_info)
			{
				if (mapa[i][j].wsk_obiekt)
				{
					mapa[i][j].znak_anim = 'X';
					mapa[i][j].kolor_anim = 12;

					mapa[i][j].wsk_obiekt->zadaj_obr (obr);
				}
				else
				{
					mapa[i][j].znak_anim = 'X';
					mapa[i][j].kolor_anim = 11;

					mapa[i][j].wsk_obiekt = new Bryla_lodu;
				}
			}
		}
	}

	mapa.ustal_anim (); pokaz (); Sleep (500);
}

//####################################################################################################

Slabe_leczenie::Slabe_leczenie ()
{
	nazwa = "Slabe leczenie";
	koszt_skill = 5;

	opis[0] = "Zwieksza HP o 5";
	opis[1] = "";
	opis[2] = "";
	opis[3] = "";
	opis[4] = "";
	opis[5] = "";
	opis[6] = "";
	opis[7] = "";
}

void Slabe_leczenie::wybierz ()
{
	int skill_y, skill_x;

	for (int i = 1; i <= 5; i++)
	{
		skill_y = jak_obiekt->wsp_y - i; skill_x = jak_obiekt->wsp_x - i;

		for (int j = 0; j < 8 * i; j++)
		{
			if (skill_y >= 0 && skill_y <= 22 && skill_x >= 0 && skill_x <= 22)
			{
				mapa[skill_y][skill_x].czy_wyb = 1;
			}

			if (j >= 0 * i && j < 2 * i) skill_x++;
			if (j >= 2 * i && j < 4 * i) skill_y++;
			if (j >= 4 * i && j < 6 * i) skill_x--;
			if (j >= 6 * i && j < 8 * i) skill_y--;
		}
	}
}

void Slabe_leczenie::info ()
{
	//
}

void Slabe_leczenie::cel ()
{
	mapa[kurs_y][kurs_x].znak_anim = '+';
	mapa[kurs_y][kurs_x].kolor_anim = 10;
	mapa.ustal_anim (); pokaz (); Sleep (500);

	if (mapa[kurs_y][kurs_x].wsk_obiekt) mapa[kurs_y][kurs_x].wsk_obiekt->hp_aktual += 5;
}