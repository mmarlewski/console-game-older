#ifndef UMIEJETNOSCI
#define UMIEJETNOSCI

#include "skill.h"

class Ruch :public Skill { public: Ruch (); void wybierz (); void info (); void cel (); };
class Skok :public Skill { public: Skok (); void wybierz (); void info (); void cel (); };
class Przewrot :public Skill { public: Przewrot (); void wybierz (); void info (); void cel (); };
class Bliski_atak :public Skill { public: Bliski_atak (); void wybierz (); void info (); void cel (); };
class Bliski_zamach :public Skill { public: Bliski_zamach (); void wybierz (); void info (); void cel (); };
class Daleki_atak :public Skill { public: Daleki_atak (); void wybierz (); void info (); void cel (); };
class Przebicie :public Skill { public: Przebicie (); void wybierz (); void info (); void cel (); };
class Pojedynczy_strzal :public Skill { public: Pojedynczy_strzal (); void wybierz (); void info (); void cel (); };
class Podwojny_strzal :public Skill { public: Podwojny_strzal (); void wybierz (); void info (); void cel (); };
class Dzgnij_bagnetem :public Skill { public: Dzgnij_bagnetem (); void wybierz (); void info (); void cel (); };
class Rzuc_kamieniem :public Skill { public: Rzuc_kamieniem (); void wybierz (); void info (); void cel (); };
class Piorun :public Skill { public: Piorun (); void wybierz (); void info (); void cel (); };
class Fireball :public Skill { public: Fireball (); void wybierz (); void info (); void cel (); };
class Pozar :public Skill { public: Pozar (); void wybierz (); void info (); void cel (); };
class Lodowy_kolec :public Skill { public: Lodowy_kolec (); void wybierz (); void info (); void cel (); };
class Lodowa_pulapka :public Skill { public: Lodowa_pulapka (); void wybierz (); void info (); void cel (); };
class Slabe_leczenie :public Skill { public: Slabe_leczenie (); void wybierz (); void info (); void cel (); };

#endif