#include "item.h"

Item::Item ()
{
	zaloz = 0;
}

Item::~Item ()
{
	//
}

Inne::Inne ()
{
	rodzaj = 0;
}

Inne::~Inne ()
{
	//
}

Bron::Bron ()
{
	rodzaj = 1;
}

Bron::~Bron ()
{
	if (czy_dyst) delete[] tab_ammo;
}

Ammo::Ammo ()
{
	rodzaj = 2;
}

Ammo::~Ammo ()
{
	//
}

Stroj::Stroj ()
{
	rodzaj = 3;
}

Stroj::~Stroj ()
{
	//
}