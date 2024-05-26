#include "pole.h"

Pole::Pole ()
{
	wsk_obiekt = 0;
}

Pole::~Pole ()
{
	if (wsk_obiekt) delete wsk_obiekt;
}