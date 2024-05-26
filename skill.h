#ifndef SKILL
#define SKILL

#include <string>

class Skill
{
	public:

	Skill ();
	~Skill ();

	virtual void wybierz () = 0;  //oznacza na mapie pola ktore mozna obrac za cel
	virtual void info () = 0;     //tworzy specjalne oznaczenia podczas odbierania pola za cel
	virtual void cel () = 0;      //co dzieje po obraniu pola za cel w tym animacja

	std::string nazwa;    //nazwa umiejetnosci
	int koszt_skill;      //koszt uzycia umiejetnosci
	std::string opis[8];  //opis umiejetnosci
};

#endif