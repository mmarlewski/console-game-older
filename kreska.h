#ifndef KRESKA
#define KRESKA

class Kreska
{
	public:

	Kreska ();
	~Kreska ();

	void operator()(int, int, int, int);
	void usun ();

	int ile_pol;     //ile pol zawiera kreska w tym pole poczatku i konca
	int* y;          //tablica wspolrzednych y pol kreski
	int* x;          //tablica wspolrzednych x pol kreski
};

#endif