#include "klasy.h"
#include "umiejetnosci.h"

extern Ruch ruch;
extern Skok skok;
extern Przewrot przewrot;
extern Bliski_atak bliski_atak;
extern Bliski_zamach bliski_zamach;
extern Daleki_atak daleki_atak;
extern Przebicie przebicie;
extern Pojedynczy_strzal pojedynczy_strzal;
extern Podwojny_strzal podwojny_strzal;
extern Dzgnij_bagnetem dzgnij_bagnetem;
extern Rzuc_kamieniem rzuc_kamieniem;
extern Piorun piorun;
extern Fireball fireball;
extern Pozar pozar;
extern Lodowy_kolec lodowy_kolec;
extern Lodowa_pulapka lodowa_pulapka;
extern Slabe_leczenie slabe_leczenie;

Rycerz::Rycerz ()
{
	symbol = 'R'; nazwa = "rycerz"; imie = nazwa;
	czy_umiej = 1; czy_ekwip = 1;
	czy_hp = 1; czy_ap = 1;
	wysokosc = 2; ekw_max = 20;
	hp_max = 20; ap_max = 5;
	hp_aktual = hp_max; ap_aktual = ap_max;
}

void Rycerz::ustaw_skill ()
{
	dodaj_umiej (&ruch);

	if (wsk_bron->item_id == 1 || wsk_bron->item_id == 2)
	{
		dodaj_umiej (&bliski_atak); dodaj_umiej (&bliski_zamach);
	}

	if (wsk_bron->item_id == 6)
	{
		dodaj_umiej (&dzgnij_bagnetem);
	}

	if (wsk_bron->item_id == 0 && wsk_ammo->item_id == 1 && poj_aktual > 0)
	{
		dodaj_umiej (&rzuc_kamieniem);
	}
}

Wlucznik::Wlucznik ()
{
	symbol = 'W'; nazwa = "wlucznik"; imie = nazwa;
	czy_umiej = 1; czy_ekwip = 1;
	czy_hp = 1; czy_ap = 1;
	wysokosc = 2; ekw_max = 15;
	hp_max = 15; ap_max = 9;
	hp_aktual = hp_max; ap_aktual = ap_max;
}

void Wlucznik::ustaw_skill ()
{
	dodaj_umiej (&ruch); dodaj_umiej (&skok);

	if (wsk_bron->item_id == 3 || wsk_bron->item_id == 4)
	{
		dodaj_umiej (&daleki_atak); dodaj_umiej (&przebicie);
	}

	if (wsk_bron->item_id == 6)
	{
		dodaj_umiej (&dzgnij_bagnetem);
	}

	if (wsk_bron->item_id == 0 && wsk_ammo->item_id == 1 && poj_aktual > 0)
	{
		dodaj_umiej (&rzuc_kamieniem);
	}
}

Lucznik::Lucznik ()
{
	symbol = 'L'; nazwa = "lucznik"; imie = nazwa;
	czy_umiej = 1; czy_ekwip = 1;
	czy_hp = 1; czy_ap = 1;
	wysokosc = 2; ekw_max = 10;
	hp_max = 10; ap_max = 9;
	hp_aktual = hp_max; ap_aktual = ap_max;
}

void Lucznik::ustaw_skill ()
{
	dodaj_umiej (&ruch); dodaj_umiej (&przewrot);

	if ((wsk_bron->item_id == 5 || wsk_bron->item_id == 6) && (wsk_ammo->item_id == 2 || wsk_ammo->item_id == 3))
	{
		if (poj_aktual == 1) dodaj_umiej (&pojedynczy_strzal);
		else if (poj_aktual == 2) dodaj_umiej (&podwojny_strzal);
	}

	if (wsk_bron->item_id == 6)
	{
		dodaj_umiej (&dzgnij_bagnetem);
	}

	if (wsk_bron->item_id == 0 && wsk_ammo->item_id == 1 && poj_aktual > 0)
	{
		dodaj_umiej (&rzuc_kamieniem);
	}
}

Mag::Mag ()
{
	symbol = 'M'; nazwa = "mag"; imie = nazwa;
	czy_umiej = 1; czy_ekwip = 1;
	czy_hp = 1; czy_ap = 1;
	wysokosc = 2; ekw_max = 10;
	hp_max = 10; ap_max = 10;
	hp_aktual = hp_max; ap_aktual = ap_max;
}

void Mag::ustaw_skill ()
{
	dodaj_umiej (&ruch); dodaj_umiej (&slabe_leczenie); dodaj_umiej (&piorun);

	if (wsk_bron->item_id == 7)
	{
		dodaj_umiej (&fireball);
	}

	if (wsk_bron->item_id == 8)
	{
		dodaj_umiej (&fireball); dodaj_umiej (&pozar);
	}

	if (wsk_bron->item_id == 9)
	{
		dodaj_umiej (&lodowy_kolec);
	}

	if (wsk_bron->item_id == 10)
	{
		dodaj_umiej (&lodowy_kolec); dodaj_umiej (&lodowa_pulapka);
	}
}

Sciana::Sciana ()
{
	symbol = 'X'; nazwa = "wysoki mur"; imie = nazwa;
	czy_umiej = 0; czy_ekwip = 0;
	czy_hp = 0; czy_ap = 0;
	wysokosc = 2; ekw_max = 0;
	hp_max = 1; ap_max = 1;
	hp_aktual = hp_max; ap_aktual = ap_max;
}

void Sciana::ustaw_skill ()
{
	//
}

Skrzynka::Skrzynka ()
{
	symbol = '#'; nazwa = "skrzynka"; imie = nazwa;
	czy_umiej = 0; czy_ekwip = 0;
	czy_hp = 1; czy_ap = 0;
	wysokosc = 1; ekw_max = 0;
	hp_max = 2; ap_max = 1;
	hp_aktual = hp_max; ap_aktual = ap_max;
}

void Skrzynka::ustaw_skill ()
{
	//
}

Bryla_lodu::Bryla_lodu ()
{
	symbol = 'O'; nazwa = "bryla lodu"; imie = nazwa;
	czy_umiej = 0; czy_ekwip = 0;
	czy_hp = 1; czy_ap = 0;
	wysokosc = 1; ekw_max = 0;
	hp_max = 5; ap_max = 1;
	hp_aktual = hp_max; ap_aktual = ap_max;
}

void Bryla_lodu::ustaw_skill ()
{
	//
}