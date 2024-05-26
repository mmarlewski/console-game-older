#ifndef PRZEDMIOTY
#define PRZEDMIOTY

#include "item.h"

/*  1 */class Slab_mikst_zdrowia :public Inne { public: Slab_mikst_zdrowia (); void uzyj (); };
/*  2 */class Mocn_mikst_zdrowia :public Inne { public: Mocn_mikst_zdrowia (); void uzyj (); };
/*  3 */class Slab_mikst_energii :public Inne { public: Slab_mikst_energii (); void uzyj (); };
/*  4 */class Mocn_mikst_energii :public Inne { public: Mocn_mikst_energii (); void uzyj (); };

/*  0 */class Bez_bron :public Bron { public: Bez_bron (); };
/*  1 */class Tepy_miecz :public Bron { public: Tepy_miecz (); };
/*  2 */class Ostry_miecz :public Bron { public: Ostry_miecz (); };
/*  3 */class Dzida :public Bron { public: Dzida (); };
/*  4 */class Wlucznia :public Bron { public: Wlucznia (); };
/*  5 */class Luk :public Bron { public: Luk (); };
/*  6 */class Kusza :public Bron { public: Kusza (); };
/*  7 */class Rozdzka_ognia :public Bron { public: Rozdzka_ognia (); };
/*  8 */class Kostur_ognia :public Bron { public: Kostur_ognia (); };
/*  9 */class Rozdzka_lodu :public Bron { public: Rozdzka_lodu (); };
/* 10 */class Kostur_lodu :public Bron { public: Kostur_lodu (); };


/*  0 */class Bez_ammo :public Ammo { public: Bez_ammo (); };
/*  1 */class Kamienie :public Ammo { public: Kamienie (); };
/*  2 */class Slabe_strzaly :public Ammo { public: Slabe_strzaly (); };
/*  3 */class Mocne_strzaly :public Ammo { public: Mocne_strzaly (); };

/*  0 */class Bez_stroj :public Stroj { public: Bez_stroj (); };
/*  1 */class Lachmany :public Stroj { public: Lachmany (); };
/*  2 */class Skorzana_zbroja :public Stroj { public: Skorzana_zbroja (); };
/*  3 */class Plytowa_zbroja :public Stroj { public: Plytowa_zbroja (); };

#endif