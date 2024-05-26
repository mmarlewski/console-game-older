#include "obiekt.h"
#include "przedmioty.h"

extern Bez_bron bez_bron;
extern Bez_ammo bez_ammo;
extern Bez_stroj bez_stroj;

Obiekt::Obiekt ()
{
	// obiekt na poczatku nie ma niczego zalozonego
	wsk_bron = &bez_bron;
	wsk_ammo = &bez_ammo;
	wsk_stroj = &bez_stroj;

	poj_aktual = 0;
	ile_skill = 0;
	ekw_aktual = 0;

	gracz = 0;
}

Obiekt::~Obiekt ()
{
	// usuwanie tablicy umiejetnosci i ekwipunku z przedmiotami

	if (ile_skill) delete[] umiejetnosci;
	if (ekw_aktual)
	{
		for (int i = 0; i < ekw_aktual; i++) delete ekwipunek[i];
		delete[] ekwipunek;
	}
}

void Obiekt::zadaj_obr (int _obr)
{
	// stroj chroni przed czescia lub caloscia obrazen

	if (czy_hp)
	{
		hp_aktual -= ((wsk_stroj->ochrona < _obr) ? (_obr - wsk_stroj->ochrona) : (0));
	}
}

void Obiekt::dodaj_umiej (Skill* umiej)
{
	// nowa tablica umiejetnosci...
	Skill** tab;

	// ...jest wieksza od starej o 1 ...
	tab = new Skill*[ile_skill + 1];

	// ...zawiera wszystkie umiejetnosci poprzedniej...
	for (int i = 0; i < ile_skill; i++)
	{
		tab[i] = umiejetnosci[i];
	}

	// ...oraz nowa umiejetnosc
	tab[ile_skill] = umiej;

	// stara tablica jest usuwana ( umiejetnosci nie sa usuwane )
	if (ile_skill) delete[] umiejetnosci;

	// nowa tablica zastepuje stara
	umiejetnosci = tab;

	// umiejetnosci jest o 1 wiecej
	ile_skill++;
}

void Obiekt::dodaj_przedm (Item* przedmiot)
{
	// jesli jest miejsce na wiecej przedmiotow
	if (ekw_aktual != ekw_max)
	{
		// nowy ekwipunek...
		Item** tab;

		// ...jest wiekszy od starego o 1...
		tab = new Item*[ekw_aktual + 1];

		// ...zawiera wszystkie przedmioty poprzedniego...
		for (int i = 0; i < ekw_aktual; i++)
		{
			tab[i] = ekwipunek[i];
		}

		// ...oraz nowy przedmiot
		tab[ekw_aktual] = przedmiot;

		// stary ekwipunek jest usuwany ( przedmioty nie sa usuwane )
		if (ekw_aktual) delete[] ekwipunek;

		// nowy ekwipunek zastepuje stary
		ekwipunek = tab;

		// przedmiotow jest o 1 wiecej
		ekw_aktual++;
	}
}

void Obiekt::zaloz_przedm (Item* przedmiot)
{
	switch (przedmiot->rodzaj)
	{
		case 1:

		// jesli zalozona jest amunicja odpowiednia dla nowej broni...
		if (wsk_ammo->item_id != 0)
		{
			// ..pociski ze starej broni wracaja do amunicji
			wsk_ammo->pojemnosc += poj_aktual;
			poj_aktual = 0;

		}

		// jesli jest zalozona bron...
		if (wsk_bron->item_id != 0)
		{
			// ...to juz nie jest
			wsk_bron->zaloz = 0;
		}

		// zalozona jest nowa bron
		wsk_bron = (Bron*) przedmiot;

		break;
		case 2:

		// jesli jest zalozona amunicja...
		if (wsk_ammo->item_id != 0)
		{
			//...to juz nie jest...
			wsk_ammo->zaloz = 0;

			// ...oraz pociski wracaja do niej z zalozonej broni...
			wsk_ammo->pojemnosc += poj_aktual;
			poj_aktual = 0;
		}

		// zalozona jest nowa amunicja
		wsk_ammo = (Ammo*) przedmiot;

		break;
		case 3:

		// jesli jest zalozony stroj...
		if (wsk_stroj->item_id != 0)
		{
			// ...to juz nie jest
			wsk_stroj->zaloz = 0;
		}

		// zalozony jest nowy stroj
		wsk_stroj = (Stroj*) przedmiot;

		break;
		default:break;
	}

	// przedmiot jest zalozony
	przedmiot->zaloz = 1;

	// zalozenie kosztuje 1 punkt ruchu
	ap_aktual -= 1;
}

void Obiekt::zdejmij_przedm (Item* przedmiot)
{
	switch (przedmiot->rodzaj)
	{
		case 1:

		// jesli zalozona jest amunicja...
		if (wsk_ammo->item_id != 0)
		{
			// ...pociski wracaja do amunicji
			wsk_ammo->pojemnosc += poj_aktual;
			poj_aktual = 0;
		}

		// amunicja jest zdjeta
		wsk_ammo->zaloz = 0;
		wsk_ammo = &bez_ammo;

		// bron jest zdjeta
		przedmiot->zaloz = 0;
		wsk_bron = &bez_bron;

		break;
		case 2:

		// pociski wracaja do amunicji
		wsk_ammo->pojemnosc += poj_aktual;
		poj_aktual = 0;

		// amunicja jest zdjeta
		przedmiot->zaloz = 0;
		wsk_ammo = &bez_ammo;

		break;
		case 3:

		// stroj jest zdjety
		przedmiot->zaloz = 0;
		wsk_stroj = &bez_stroj;

		break;
		default:break;
	}
}

void Obiekt::usun_przedm (Item* przedmiot)
{
	// mowy ekwipunek...
	Item** tab;

	// ...jest mniejszy od starego o 1...
	tab = new Item*[ekw_aktual];

	// ...zawiera wszystkie przedmioty...
	for (int i = 0, j = 0; i < ekw_aktual; i++, j++)
	{
		if (i == przedmiot->nr_ekw) j++;

		tab[i] = ekwipunek[j];
	}

	// ...oprocz tego do usuniecia
	delete przedmiot;

	// stary ekwipunek jest usuwany
	delete[] ekwipunek;

	// nowy ekwipunek zastepuje stary
	ekwipunek = tab;

	// przedmiotow jest o 1 mniej
	ekw_aktual--;
}

void Obiekt::poloz_przedm ()
{
	for (int i = 0; i < ekw_aktual; i++)
	{
		ekwipunek[i]->nr_ekw = i;
	}
}

void Obiekt::sprawdz_ammo ()
{
	// jesli ani amunicja ani obiekt nie ma pociskow...
	if (wsk_ammo->item_id != 0 && wsk_ammo->pojemnosc == 0 && poj_aktual == 0)
	{
		// ...amunicja jest usuwana
		usun_przedm (wsk_ammo);
		wsk_ammo = &bez_ammo;
	}
}

bool Obiekt::ustal_przel ()
{
	// jesli zalozona jest bron dystansowa i amunicja
	if (wsk_bron->czy_dyst && wsk_ammo->item_id != 0)
	{
		// jesli amunicja ma jeszcze pociski , bron moze jeszcze przyjac wiecej i liczba punktow ruchu jest wystarczajaca
		if (wsk_ammo->pojemnosc != 0 && poj_aktual + wsk_ammo->przel <= wsk_bron->poj_max && ap_aktual >= 1) return 1;
	}

	return 0;
}

bool Obiekt::ustal_rozl ()
{
	//  jesli zalozona jest bron dystansowa i amunicja oraz bron jest wyposazona w pociski
	if (wsk_bron->czy_dyst && wsk_ammo->item_id != 0 && poj_aktual != 0) return 1;

	return 0;
}

bool Obiekt::ustal_zaloz (Item* przedmiot)
{
	switch (przedmiot->rodzaj)
	{
		case 1:

		// jesli jest zalozona amunicja
		if (wsk_ammo->item_id != 0)
		{
			// jesli nowa bron jest odpowiednia dla zalozonej amunicji
			for (int i = 0; i < ((Bron*) przedmiot)->ile_ammo; i++)
			{
				if (((Bron*) przedmiot)->tab_ammo[i] == wsk_ammo->item_id) return 1;
			}
		}
		else return 1;

		break;
		case 2:

		// jesli nowa amunicja jest odpowiednia dla zalozonej broni
		for (int i = 0; i < wsk_bron->ile_ammo; i++)
		{
			if (wsk_bron->tab_ammo[i] == przedmiot->item_id) return 1;
		}

		break;
		case 3:

		return 1;

		break;
		default:break;
	}

	return 0;
}