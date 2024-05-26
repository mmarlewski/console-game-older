#ifndef KLASY
#define KLASY

#include "obiekt.h"

class Rycerz :public Obiekt { public: Rycerz (); void ustaw_skill (); };
class Wlucznik :public Obiekt { public: Wlucznik (); void ustaw_skill (); };
class Lucznik :public Obiekt { public: Lucznik (); void ustaw_skill (); };
class Mag :public Obiekt { public: Mag (); void ustaw_skill (); };
class Sciana :public Obiekt { public: Sciana (); void ustaw_skill (); };
class Skrzynka :public Obiekt { public: Skrzynka (); void ustaw_skill (); };
class Bryla_lodu :public Obiekt { public: Bryla_lodu (); void ustaw_skill (); };

#endif