#include "przedmioty.h"
#include "obiekt.h"

extern Obiekt* jak_obiekt;

Slab_mikst_zdrowia::Slab_mikst_zdrowia ()
{
	item_id = 1; nazwa = "Slab. mikst. zdrowia";
	koszt_item = 1;

	opis[0] = "Zwieksza HP o 5";
	opis[1] = "";
	opis[2] = "";
	opis[3] = "";
	opis[4] = "";
	opis[5] = "";
	opis[6] = "";
	opis[7] = "";
}

void Slab_mikst_zdrowia::uzyj ()
{
	jak_obiekt->hp_aktual += 5;
}

Mocn_mikst_zdrowia::Mocn_mikst_zdrowia ()
{
	item_id = 2; nazwa = "Mocn. mikst. zdrowia";
	koszt_item = 1;

	opis[0] = "Zwieksza HP o 10";
	opis[1] = "";
	opis[2] = "";
	opis[3] = "";
	opis[4] = "";
	opis[5] = "";
	opis[6] = "";
	opis[7] = "";
}

void Mocn_mikst_zdrowia::uzyj ()
{
	jak_obiekt->hp_aktual += 10;
}

Slab_mikst_energii::Slab_mikst_energii ()
{
	item_id = 3; nazwa = "Slab. mikst. energii";
	koszt_item = 0;

	opis[0] = "Zwieksza AP o 5";
	opis[1] = "";
	opis[2] = "";
	opis[3] = "";
	opis[4] = "";
	opis[5] = "";
	opis[6] = "";
	opis[7] = "";
}

void Slab_mikst_energii::uzyj ()
{
	jak_obiekt->ap_aktual += 5;
}

Mocn_mikst_energii::Mocn_mikst_energii ()
{
	item_id = 4; nazwa = "Mocn. mikst. energii";
	koszt_item = 0;

	opis[0] = "Zwieksza AP o 10";
	opis[1] = "";
	opis[2] = "";
	opis[3] = "";
	opis[4] = "";
	opis[5] = "";
	opis[6] = "";
	opis[7] = "";
}

void Mocn_mikst_energii::uzyj ()
{
	jak_obiekt->ap_aktual += 10;
}

//####################################################################################################

Bez_bron::Bez_bron ()
{
	item_id = 0; nazwa = "Bez broni";

	czy_dyst = 1;
	obrazenia = 1;
	poj_max = 10;

	ile_ammo = 1;
	tab_ammo = new int[ile_ammo];
	tab_ammo[0] = 1;

	opis[0] = "";
	opis[1] = "";
	opis[2] = "";
	opis[3] = "";
	opis[4] = "";
	opis[5] = "";
	opis[6] = "";
	opis[7] = "";
}

Tepy_miecz::Tepy_miecz ()
{
	item_id = 1; nazwa = "Tepy miecz";

	czy_dyst = 0;
	obrazenia = 3;
	poj_max = 0;

	ile_ammo = 0;

	opis[0] = "";
	opis[1] = "";
	opis[2] = "";
	opis[3] = "";
	opis[4] = "";
	opis[5] = "";
	opis[6] = "";
	opis[7] = "";
}

Ostry_miecz::Ostry_miecz ()
{
	item_id = 2; nazwa = "Ostry miecz";

	czy_dyst = 0;
	obrazenia = 6;
	poj_max = 0;

	ile_ammo = 0;

	opis[0] = "";
	opis[1] = "";
	opis[2] = "";
	opis[3] = "";
	opis[4] = "";
	opis[5] = "";
	opis[6] = "";
	opis[7] = "";
}

Dzida::Dzida ()
{
	item_id = 3; nazwa = "Dzida";

	czy_dyst = 0;
	obrazenia = 4;
	poj_max = 0;

	ile_ammo = 0;

	opis[0] = "";
	opis[1] = "";
	opis[2] = "";
	opis[3] = "";
	opis[4] = "";
	opis[5] = "";
	opis[6] = "";
	opis[7] = "";
}

Wlucznia::Wlucznia ()
{
	item_id = 4; nazwa = "Wlucznia";

	czy_dyst = 0;
	obrazenia = 6;
	poj_max = 0;

	ile_ammo = 0;

	opis[0] = "";
	opis[1] = "";
	opis[2] = "";
	opis[3] = "";
	opis[4] = "";
	opis[5] = "";
	opis[6] = "";
	opis[7] = "";
}

Luk::Luk ()
{
	item_id = 5; nazwa = "Luk";

	czy_dyst = 1;
	obrazenia = 1;
	poj_max = 5;

	ile_ammo = 2;
	tab_ammo = new int[ile_ammo];
	tab_ammo[0] = 2;
	tab_ammo[1] = 3;

	opis[0] = "Miota strzalami";
	opis[1] = "";
	opis[2] = "";
	opis[3] = "";
	opis[4] = "";
	opis[5] = "";
	opis[6] = "";
	opis[7] = "";
}

Kusza::Kusza ()
{
	item_id = 6; nazwa = "Kusza";

	czy_dyst = 1;
	obrazenia = 3;
	poj_max = 1;

	ile_ammo = 2;
	tab_ammo = new int[ile_ammo];
	tab_ammo[0] = 2;
	tab_ammo[1] = 3;

	opis[0] = "Miota strzalami";
	opis[1] = "mocno";
	opis[2] = "";
	opis[3] = "";
	opis[4] = "";
	opis[5] = "";
	opis[6] = "";
	opis[7] = "";
}

Rozdzka_ognia::Rozdzka_ognia ()
{
	item_id = 7; nazwa = "Rozdzka ognia";

	czy_dyst = 0;
	obrazenia = 3;
	poj_max = 0;

	ile_ammo = 0;

	opis[0] = "Umozliwia zucanie";
	opis[1] = "zaklecia kuli ognia";
	opis[2] = "";
	opis[3] = "";
	opis[4] = "";
	opis[5] = "";
	opis[6] = "";
	opis[7] = "";
}

Kostur_ognia::Kostur_ognia ()
{
	item_id = 8; nazwa = "Kostur ognia";

	czy_dyst = 0;
	obrazenia = 5;
	poj_max = 0;

	ile_ammo = 0;

	opis[0] = "Umozliwia zucanie";
	opis[1] = "zaklec kuli ognia";
	opis[2] = "i pozaru";
	opis[3] = "";
	opis[4] = "";
	opis[5] = "";
	opis[6] = "";
	opis[7] = "";
}

Rozdzka_lodu::Rozdzka_lodu ()
{
	item_id = 9; nazwa = "Rozdzka lodu";

	czy_dyst = 0;
	obrazenia = 3;
	poj_max = 0;

	ile_ammo = 0;

	opis[0] = "Umozliwia zucanie";
	opis[1] = "zaklecia lodowego";
	opis[2] = "kolca";
	opis[3] = "";
	opis[4] = "";
	opis[5] = "";
	opis[6] = "";
	opis[7] = "";
}

Kostur_lodu::Kostur_lodu ()
{
	item_id = 10; nazwa = "Kostur lodu";

	czy_dyst = 0;
	obrazenia = 5;
	poj_max = 0;

	ile_ammo = 0;

	opis[0] = "Umozliwia zucanie";
	opis[1] = "zaklec lodowego";
	opis[2] = "kolca i lodowej";
	opis[3] = "pulapki";
	opis[4] = "";
	opis[5] = "";
	opis[6] = "";
	opis[7] = "";
}

//####################################################################################################

Bez_ammo::Bez_ammo ()
{
	item_id = 0; nazwa = "Bez amunicji";

	obrazenia = 0;
	pojemnosc = 0;
	przel = 0;

	opis[0] = "";
	opis[1] = "";
	opis[2] = "";
	opis[3] = "";
	opis[4] = "";
	opis[5] = "";
	opis[6] = "";
	opis[7] = "";
}

Kamienie::Kamienie ()
{
	item_id = 1; nazwa = "Kamienie";

	obrazenia = 1;
	pojemnosc = 10;
	przel = 1;

	opis[0] = "";
	opis[1] = "";
	opis[2] = "";
	opis[3] = "";
	opis[4] = "";
	opis[5] = "";
	opis[6] = "";
	opis[7] = "";
}

Slabe_strzaly::Slabe_strzaly ()
{
	item_id = 2; nazwa = "Slabe strzaly";

	obrazenia = 3;
	pojemnosc = 10;
	przel = 1;

	opis[0] = "";
	opis[1] = "";
	opis[2] = "";
	opis[3] = "";
	opis[4] = "";
	opis[5] = "";
	opis[6] = "";
	opis[7] = "";
}

Mocne_strzaly::Mocne_strzaly ()
{
	item_id = 3; nazwa = "Mocne strzaly";

	obrazenia = 6;
	pojemnosc = 10;
	przel = 1;

	opis[0] = "";
	opis[1] = "";
	opis[2] = "";
	opis[3] = "";
	opis[4] = "";
	opis[5] = "";
	opis[6] = "";
	opis[7] = "";
}

//####################################################################################################

Bez_stroj::Bez_stroj ()
{
	item_id = 0; nazwa = "Bez stroju";

	ochrona = 0;

	opis[0] = "";
	opis[1] = "";
	opis[2] = "";
	opis[3] = "";
	opis[4] = "";
	opis[5] = "";
	opis[6] = "";
	opis[7] = "";
}

Lachmany::Lachmany ()
{
	item_id = 1; nazwa = "Lachmany";

	ochrona = 2;

	opis[0] = "";
	opis[1] = "";
	opis[2] = "";
	opis[3] = "";
	opis[4] = "";
	opis[5] = "";
	opis[6] = "";
	opis[7] = "";
}

Skorzana_zbroja::Skorzana_zbroja ()
{
	item_id = 2; nazwa = "Skorzana zbroja";

	ochrona = 4;

	opis[0] = "";
	opis[1] = "";
	opis[2] = "";
	opis[3] = "";
	opis[4] = "";
	opis[5] = "";
	opis[6] = "";
	opis[7] = "";
}

Plytowa_zbroja::Plytowa_zbroja ()
{
	item_id = 3; nazwa = "Plytowa zbroja";

	ochrona = 7;

	opis[0] = "";
	opis[1] = "";
	opis[2] = "";
	opis[3] = "";
	opis[4] = "";
	opis[5] = "";
	opis[6] = "";
	opis[7] = "";
}