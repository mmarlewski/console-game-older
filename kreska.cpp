#include "kreska.h"

#include <math.h>
#include <windows.h>

Kreska::Kreska ()
{
	ile_pol = 0;
}

Kreska::~Kreska ()
{
	if (ile_pol)
	{
		delete[] y; delete[] x;
	}
}

void Kreska::operator() (int y1, int x1, int y2, int x2)
{
	double t;

	ile_pol = max (abs (y2 - y1), abs (x2 - x1)) + 1;

	y = new int[ile_pol];
	x = new int[ile_pol];

	for (int i = 0; i < ile_pol; i++)
	{
		t = i / double (ile_pol - 1);

		y[i] = int (round ((double) y1 + t * double (y2 - y1)));
		x[i] = int (round ((double) x1 + t * double (x2 - x1)));
	}
}

void Kreska::usun ()
{
	if (ile_pol)
	{
		delete[] y; delete[] x;

		ile_pol = 0;
	}
}