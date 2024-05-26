#include "mapa.h"
#include "kreska.h"
#include "pole.h"
#include "obiekt.h"
#include "klasy.h"
#include "skill.h"
#include "umiejetnosci.h"
#include "item.h"
#include "przedmioty.h"

#include <iostream>
#include <windows.h>
#include <string>
#include <conio.h>

// zmienne globalne dostepne dla kazdego pliku .h i .cpp

Mapa mapa;            //na mapie znajduja sie obiekty
Kreska kreska;        //zawiera wspolrzedne pol tworzacych linie miedzy dwoma punktami
int kurs_y, kurs_x;   //wspolrzedne kursora
int znak;             //znak wprowadzony przez klawiature

bool czy_gra;         //czy gra ma nadal sie toczyc
int tryb;             //aktualny tryb ( 1-wybor postaci , 2-wybor celu , 3-umiejetnosci , 4-ekwipunek )
int tura;             //czyja tura ( 1-gracz nr1 , 2-gracz nr2 )
bool czy_przel;       //czy mozna przeladowac zalozona bron
bool czy_rozl;        //czy mozna rozladowac zalozona bron
int nr_umiej;         //numer wybranej umiejetnosc ( tryb 3 )
int nr_przedm;        //numer wybranego przedmiot z ekwipunku ( tryb 4 )
bool czy_zaloz;       //czy mozna zalozyc wybrany przedmiot z ekwipunku

Obiekt* jak_obiekt;   //wybrany obiekt
Obiekt* cel_obiekt;   //obiekt obrany za cel ( tryb 2 )
Skill* jak_umiej;     //wybrana umiejetnosc ( tryb 3 )
Item* jak_przedm;     //wybrany przedmiot ( tryb 4 )

Bez_bron bez_bron;    //zalozona bron w przypadku braku zalozonej broni
Bez_ammo bez_ammo;    //zalozona amunicja w przypadku braku zalozonej amunicji
Bez_stroj bez_stroj;  //zalozony stroj w przypadku braku zalozonego stroju

// umiejetnosci z ktorych moga korzystac obiekty

Ruch ruch;
Skok skok;
Przewrot przewrot;
Bliski_atak bliski_atak;
Bliski_zamach bliski_zamach;
Daleki_atak daleki_atak;
Przebicie przebicie;
Pojedynczy_strzal pojedynczy_strzal;
Podwojny_strzal podwojny_strzal;
Dzgnij_bagnetem dzgnij_bagnetem;
Rzuc_kamieniem rzuc_kamieniem;
Piorun piorun;
Fireball fireball;
Pozar pozar;
Lodowy_kolec lodowy_kolec;
Lodowa_pulapka lodowa_pulapka;
Slabe_leczenie slabe_leczenie;

void pokaz ()
{
	// czysci konsole
	system ("cls");

	for (int i = 0; i < 23; i++)
	{
		for (int j = 0; j < 23; j++)
		{
			// wyswietla znaki ustalonego wczesniej koloru w miejscach pol mapy
			SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), mapa[i][j].kolor_pola);
			std::cout << mapa[i][j].znak_pola;
		}

		SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 15);
		std::cout << "     ";

		// wyswietla interfejs

		switch (i)
		{
			case 0:

			if (tura == 1)
			{
				SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 10);
				std::cout << "Gracz nr 1";
			}
			else
			{
				SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 11);
				std::cout << "Gracz nr 2";
			}

			break;
			case 2:

			switch (tryb)
			{
				case 1:

				if (jak_obiekt)
				{
					SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 13);
					std::cout << jak_obiekt->imie;
				}

				break;
				case 2:

				if (cel_obiekt)
				{
					SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 13);
					std::cout << cel_obiekt->imie;
				}

				break;
				case 3:

				SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 15);
				std::cout << "       " << nr_umiej << " / " << jak_obiekt->ile_skill;

				break;
				case 4:

				SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 15);
				std::cout << "       " << nr_przedm << " / " << jak_obiekt->ekw_aktual;

				break;
				default:break;
			}

			break;
			case 4:

			switch (tryb)
			{
				case 1:

				if (jak_obiekt)
				{
					SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 15);
					std::cout << "Przyn. : ";

					if (jak_obiekt->gracz == 1)
					{
						SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 10);
						std::cout << "gracz nr 1";
					}
					else if (jak_obiekt->gracz == 2)
					{
						SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 11);
						std::cout << "gracz nr 2";
					}
					else
					{
						SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 15);
						std::cout << "neutralny";
					}
				}

				break;
				case 2:

				if (cel_obiekt)
				{
					SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 15);
					std::cout << "Przyn. : ";

					if (cel_obiekt->gracz == 1)
					{
						SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 10);
						std::cout << "gracz nr 1";
					}
					else if (cel_obiekt->gracz == 2)
					{
						SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 11);
						std::cout << "gracz nr 2";
					}
					else
					{
						SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 15);
						std::cout << "neutralny";
					}
				}

				break;
				case 3:

				SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 13);
				std::cout << jak_umiej->nazwa;

				break;
				case 4:

				SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 13);
				std::cout << jak_przedm->nazwa;

				break;
				default:break;
			}

			break;
			case 5:

			switch (tryb)
			{
				case 1:

				SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 15);
				if (jak_obiekt) std::cout << "Klasa  : " << jak_obiekt->nazwa;

				break;
				case 2:

				SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 15);
				if (cel_obiekt) std::cout << "Klasa  : " << cel_obiekt->nazwa;

				break;
				default:break;
			}

			break;
			case 6:

			switch (tryb)
			{
				case 1:

				if (jak_obiekt)
				{
					SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 15);
					std::cout << "Wysok. : " << jak_obiekt->wysokosc << " - ";
					if (jak_obiekt->wysokosc == 1) std::cout << "niski"; else std::cout << "wysoki";
				}

				break;
				case 2:

				if (cel_obiekt)
				{
					SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 15);
					std::cout << "Wysok. : " << cel_obiekt->wysokosc << " - ";
					if (cel_obiekt->wysokosc == 1) std::cout << "niski"; else std::cout << "wysoki";
				}

				break;
				case 3:

				std::cout << "Koszt  : ";
				SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 10);
				std::cout << jak_umiej->koszt_skill;

				break;
				case 4:

				std::cout << ((jak_przedm->zaloz) ? ("X") : (" ")) << " | ";

				switch (jak_przedm->rodzaj)
				{
					case 0:

					SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 10);
					std::cout << "Koszt  ";
					SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 15);
					std::cout << ": " << ((Inne*) jak_przedm)->koszt_item;

					break;
					case 1:

					SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 12);
					std::cout << "Obraz. ";
					SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 15);
					std::cout << ": " << ((Bron*) jak_przedm)->obrazenia;

					break;
					case 2:

					SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 12);
					std::cout << "Obraz. ";
					SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 15);
					std::cout << ": " << ((Ammo*) jak_przedm)->obrazenia;
					SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 14);
					std::cout << "   " << ((Ammo*) jak_przedm)->pojemnosc;

					break;
					case 3:

					SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 11);
					std::cout << "Ochr.  ";
					SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 15);
					std::cout << ": " << ((Stroj*) jak_przedm)->ochrona;

					break;
					default:break;
				}
			}

			break;
			case 7:

			switch (tryb)
			{
				case 1:

				if (jak_obiekt)
				{
					SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 15);
					std::cout << "HP     : ";

					SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 12);
					if (jak_obiekt->czy_hp)
					{
						std::cout << jak_obiekt->hp_aktual << " / " << jak_obiekt->hp_max;
					}
					else std::cout << "-----";
				}

				break;
				case 2:

				if (cel_obiekt)
				{
					SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 15);
					std::cout << "HP     : ";

					SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 12);
					if (cel_obiekt->czy_hp)
					{
						std::cout << cel_obiekt->hp_aktual << " / " << cel_obiekt->hp_max;
					}
					else std::cout << "-----";
				}

				break;
				default:break;
			}

			break;
			case 8:

			switch (tryb)
			{
				case 1:

				if (jak_obiekt && jak_obiekt->gracz == tura)
				{
					SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 15);
					std::cout << "AP     : ";

					SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 10);
					if (jak_obiekt->czy_ap)
					{
						std::cout << jak_obiekt->ap_aktual << " / " << jak_obiekt->ap_max;
					}
					else std::cout << "-----";
				}

				break;
				case 3:

				SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 15);
				std::cout << jak_umiej->opis[0];

				break;
				case 4:

				SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 15);
				std::cout << jak_przedm->opis[0];

				break;
				default:break;
			}

			break;
			case 9:

			switch (tryb)
			{
				case 3:

				SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 15);
				std::cout << jak_umiej->opis[1];

				break;
				case 4:

				SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 15);
				std::cout << jak_przedm->opis[1];

				break;
				default:break;
			}

			break;
			case 10:

			switch (tryb)
			{
				case 1:

				if (jak_obiekt)
				{
					SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 12);
					std::cout << jak_obiekt->wsk_bron->nazwa;
					if (jak_obiekt->wsk_bron->czy_dyst && jak_obiekt->wsk_ammo->item_id != 0)
					{
						std::cout << " " << jak_obiekt->poj_aktual;
					}
				}

				break;
				case 3:

				SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 15);
				std::cout << jak_umiej->opis[2];

				break;
				case 4:

				SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 15);
				std::cout << jak_przedm->opis[2];

				break;
				default:break;
			}

			break;
			case 11:

			switch (tryb)
			{
				case 1:

				if (jak_obiekt)
				{
					SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 14);
					std::cout << jak_obiekt->wsk_ammo->nazwa;
					if (jak_obiekt->wsk_ammo->item_id != 0)
					{
						std::cout << " " << jak_obiekt->wsk_ammo->pojemnosc;
					}
				}


				break;
				case 3:

				SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 15);
				std::cout << jak_umiej->opis[3];

				break;
				case 4:

				SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 15);
				std::cout << jak_przedm->opis[3];

				break;
				default:break;
			}

			break;
			case 12:

			switch (tryb)
			{
				case 1:

				if (jak_obiekt)
				{
					SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 11);
					std::cout << jak_obiekt->wsk_stroj->nazwa;
				}

				break;
				case 3:

				SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 15);
				std::cout << jak_umiej->opis[4];

				break;
				case 4:

				SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 15);
				std::cout << jak_przedm->opis[4];

				break;
				default:break;
			}

			break;
			case 13:

			switch (tryb)
			{
				case 3:

				SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 15);
				std::cout << jak_umiej->opis[5];

				break;
				case 4:

				SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 15);
				std::cout << jak_przedm->opis[5];

				break;
				default:break;
			}

			break;
			case 14:

			switch (tryb)
			{
				case 1:

				if (jak_obiekt)
				{
					if (czy_przel)
					{
						SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 14);
						std::cout << "[W] ";
						SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 15);
						std::cout << "przeladuj  ";
						SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 10);
						std::cout << "1";
					}
				}

				break;
				case 3:

				SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 15);
				std::cout << jak_umiej->opis[6];

				break;
				case 4:

				SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 15);
				std::cout << jak_przedm->opis[6];

				break;
				default:break;
			}

			break;
			case 15:

			switch (tryb)
			{
				case 1:

				if (jak_obiekt)
				{
					if (czy_rozl)
					{
						SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 14);
						std::cout << "[S] ";
						SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 15);
						std::cout << "rozladuj";
					}
				}

				break;
				case 3:

				SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 15);
				std::cout << jak_umiej->opis[7];

				break;
				case 4:

				SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 15);
				std::cout << jak_przedm->opis[7];

				break;
				default:break;
			}

			break;
			case 17:

			switch (tryb)
			{
				case 1:

				if (jak_obiekt)
				{
					if (jak_obiekt->czy_ekwip && jak_obiekt->ekw_aktual != 0 && jak_obiekt->gracz == tura)
					{
						SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 14);
						std::cout << "[E] ";
						SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 15);
						std::cout << "ekwipunek";
					}
				}

				break;
				case 3:

				if (jak_obiekt->ap_aktual >= jak_umiej->koszt_skill)
				{
					SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 14);
					std::cout << "[E] ";
					SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 15);
					std::cout << "wybierz umiej.";
				}

				break;
				case 4:

				if (jak_przedm->rodzaj == 0)
				{
					if (jak_obiekt->ap_aktual >= ((Inne*) jak_przedm)->koszt_item)
					{
						SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 14);
						std::cout << "[E] ";
						SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 15);
						std::cout << "uzyj";
					}
				}
				else
				{
					if (!jak_przedm->zaloz && czy_zaloz)
					{
						SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 14);
						std::cout << "[E] ";
						SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 15);
						std::cout << "zaloz ";
						SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 10);
						std::cout << "1";
					}
					else if (jak_przedm->zaloz)
					{
						SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 14);
						std::cout << "[E] ";
						SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 15);
						std::cout << "zdejmij";
					}
				}

				break;
				default:break;
			}

			break;
			case 18:

			switch (tryb)
			{
				case 1:

				if (jak_obiekt && jak_obiekt->czy_umiej && jak_obiekt->gracz == tura)
				{
					SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 14);
					std::cout << "[U] ";
					SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 15);
					std::cout << "umiejetnosci";
				}

				break;
				case 2:

				if (mapa[kurs_y][kurs_x].czy_wyb)
				{
					SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 14);
					std::cout << "[E] ";
					SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 15);
					std::cout << "wybierz cel";
				}
				else
				{
					SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 15);
					std::cout << "[Poza zasiegiem]";
				}

				break;
				case 3:

				SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 14);
				std::cout << "[A,D] ";
				SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 15);
				std::cout << "zmien umiej.";

				break;
				case 4:

				SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 14);
				std::cout << "[A,D] ";
				SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 15);
				std::cout << "zmien przedm.";

				break;
				default:break;
			}

			break;
			case 20:

			switch (tryb)
			{
				case 1:

				SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 14);
				std::cout << "[Q] ";
				SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 15);
				std::cout << "zakoncz ture";

				break;
				case 2:case 3:case 4:

				SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 12);
				std::cout << "[R] ";
				SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 15);
				std::cout << "wstecz";

				break;
				default:break;
			}

			break;
			case 22:

			SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 11);

			switch (tryb)
			{
				case 1: std::cout << "Wybierz postac"; break;
				case 2: std::cout << "Wybierz cel"; break;
				case 3: std::cout << "Umiejetnosci"; break;
				case 4: std::cout << "Ekwipunek"; break;
				default:break;
			}

			break;
			default:break;
		}

		std::cout << std::endl;

		SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 15);
	}
}

int main ()
{
	std::ios_base::sync_with_stdio (0);

	// tworzenie mapy

	if (1)
	{
		for (int i = 0; i < 23; i++)
		{
			mapa[0][i].wsk_obiekt = new Sciana;
			mapa[22][i].wsk_obiekt = new Sciana;
		}

		for (int i = 1; i < 22; i++)
		{
			mapa[i][0].wsk_obiekt = new Sciana;
			mapa[i][22].wsk_obiekt = new Sciana;
		}

		for (int i = 0; i < 6; i++)
		{
			mapa[10][i].wsk_obiekt = new Sciana;
			mapa[11][i].wsk_obiekt = new Sciana;
			mapa[12][i].wsk_obiekt = new Sciana;
			mapa[10][22 - i].wsk_obiekt = new Sciana;
			mapa[11][22 - i].wsk_obiekt = new Sciana;
			mapa[12][22 - i].wsk_obiekt = new Sciana;
		}

		for (int i = 6; i < 17; i++)
		{
			mapa[10][i].wsk_obiekt = new Skrzynka;
			mapa[11][i].wsk_obiekt = new Skrzynka;
			mapa[12][i].wsk_obiekt = new Skrzynka;
		}

		mapa[3][3].wsk_obiekt = new Sciana;
		mapa[3][4].wsk_obiekt = new Sciana;
		mapa[4][3].wsk_obiekt = new Sciana;
		mapa[4][4].wsk_obiekt = new Sciana;
		mapa[3][18].wsk_obiekt = new Sciana;
		mapa[3][19].wsk_obiekt = new Sciana;
		mapa[4][18].wsk_obiekt = new Sciana;
		mapa[4][19].wsk_obiekt = new Sciana;
		mapa[18][3].wsk_obiekt = new Sciana;
		mapa[18][4].wsk_obiekt = new Sciana;
		mapa[19][3].wsk_obiekt = new Sciana;
		mapa[19][4].wsk_obiekt = new Sciana;
		mapa[18][18].wsk_obiekt = new Sciana;
		mapa[18][19].wsk_obiekt = new Sciana;
		mapa[19][18].wsk_obiekt = new Sciana;
		mapa[19][19].wsk_obiekt = new Sciana;

		mapa[8][11].wsk_obiekt = new Wlucznik;
		mapa[8][11].wsk_obiekt->gracz = 2;
		mapa[8][11].wsk_obiekt->imie = "Waclaw";
		mapa[8][11].wsk_obiekt->dodaj_przedm (new Dzida);
		mapa[8][11].wsk_obiekt->dodaj_przedm (new Wlucznia);
		mapa[8][11].wsk_obiekt->dodaj_przedm (new Kamienie);
		mapa[8][11].wsk_obiekt->dodaj_przedm (new Skorzana_zbroja);
		mapa[8][11].wsk_obiekt->dodaj_przedm (new Slab_mikst_zdrowia);
		mapa[8][11].wsk_obiekt->dodaj_przedm (new Slab_mikst_energii);

		mapa[14][11].wsk_obiekt = new Wlucznik;
		mapa[14][11].wsk_obiekt->gracz = 1;
		mapa[14][11].wsk_obiekt->imie = "Wojciech";
		mapa[14][11].wsk_obiekt->dodaj_przedm (new Dzida);
		mapa[14][11].wsk_obiekt->dodaj_przedm (new Wlucznia);
		mapa[14][11].wsk_obiekt->dodaj_przedm (new Kamienie);
		mapa[14][11].wsk_obiekt->dodaj_przedm (new Skorzana_zbroja);
		mapa[14][11].wsk_obiekt->dodaj_przedm (new Slab_mikst_zdrowia);
		mapa[14][11].wsk_obiekt->dodaj_przedm (new Slab_mikst_energii);

		mapa[8][8].wsk_obiekt = new Rycerz;
		mapa[8][8].wsk_obiekt->gracz = 2;
		mapa[8][8].wsk_obiekt->imie = "Rafal";
		mapa[8][8].wsk_obiekt->dodaj_przedm (new Tepy_miecz);
		mapa[8][8].wsk_obiekt->dodaj_przedm (new Ostry_miecz);
		mapa[8][8].wsk_obiekt->dodaj_przedm (new Kamienie);
		mapa[8][8].wsk_obiekt->dodaj_przedm (new Plytowa_zbroja);

		mapa[8][14].wsk_obiekt = new Rycerz;
		mapa[8][14].wsk_obiekt->gracz = 2;
		mapa[8][14].wsk_obiekt->imie = "Robert";
		mapa[8][14].wsk_obiekt->dodaj_przedm (new Tepy_miecz);
		mapa[8][14].wsk_obiekt->dodaj_przedm (new Ostry_miecz);
		mapa[8][14].wsk_obiekt->dodaj_przedm (new Kamienie);
		mapa[8][14].wsk_obiekt->dodaj_przedm (new Plytowa_zbroja);

		mapa[14][8].wsk_obiekt = new Rycerz;
		mapa[14][8].wsk_obiekt->gracz = 1;
		mapa[14][8].wsk_obiekt->imie = "Roman";
		mapa[14][8].wsk_obiekt->dodaj_przedm (new Tepy_miecz);
		mapa[14][8].wsk_obiekt->dodaj_przedm (new Ostry_miecz);
		mapa[14][8].wsk_obiekt->dodaj_przedm (new Kamienie);
		mapa[14][8].wsk_obiekt->dodaj_przedm (new Plytowa_zbroja);

		mapa[14][14].wsk_obiekt = new Rycerz;
		mapa[14][14].wsk_obiekt->gracz = 1;
		mapa[14][14].wsk_obiekt->imie = "Ryszard";
		mapa[14][14].wsk_obiekt->dodaj_przedm (new Tepy_miecz);
		mapa[14][14].wsk_obiekt->dodaj_przedm (new Ostry_miecz);
		mapa[14][14].wsk_obiekt->dodaj_przedm (new Kamienie);
		mapa[14][14].wsk_obiekt->dodaj_przedm (new Plytowa_zbroja);

		mapa[8][5].wsk_obiekt = new Lucznik;
		mapa[8][5].wsk_obiekt->gracz = 2;
		mapa[8][5].wsk_obiekt->imie = "Sebastian";
		mapa[8][5].wsk_obiekt->dodaj_przedm (new Luk);
		mapa[8][5].wsk_obiekt->dodaj_przedm (new Slabe_strzaly);
		mapa[8][5].wsk_obiekt->dodaj_przedm (new Mocne_strzaly);
		mapa[8][5].wsk_obiekt->dodaj_przedm (new Kamienie);
		mapa[8][5].wsk_obiekt->dodaj_przedm (new Skorzana_zbroja);
		mapa[8][5].wsk_obiekt->dodaj_przedm (new Slab_mikst_zdrowia);
		mapa[8][5].wsk_obiekt->dodaj_przedm (new Slab_mikst_energii);

		mapa[8][17].wsk_obiekt = new Lucznik;
		mapa[8][17].wsk_obiekt->gracz = 2;
		mapa[8][17].wsk_obiekt->imie = "Slawomir";
		mapa[8][17].wsk_obiekt->dodaj_przedm (new Kusza);
		mapa[8][17].wsk_obiekt->dodaj_przedm (new Slabe_strzaly);
		mapa[8][17].wsk_obiekt->dodaj_przedm (new Mocne_strzaly);
		mapa[8][17].wsk_obiekt->dodaj_przedm (new Kamienie);
		mapa[8][17].wsk_obiekt->dodaj_przedm (new Skorzana_zbroja);
		mapa[8][17].wsk_obiekt->dodaj_przedm (new Slab_mikst_zdrowia);
		mapa[8][17].wsk_obiekt->dodaj_przedm (new Slab_mikst_energii);

		mapa[14][5].wsk_obiekt = new Lucznik;
		mapa[14][5].wsk_obiekt->gracz = 1;
		mapa[14][5].wsk_obiekt->imie = "Stanislaw";
		mapa[14][5].wsk_obiekt->dodaj_przedm (new Luk);
		mapa[14][5].wsk_obiekt->dodaj_przedm (new Slabe_strzaly);
		mapa[14][5].wsk_obiekt->dodaj_przedm (new Mocne_strzaly);
		mapa[14][5].wsk_obiekt->dodaj_przedm (new Kamienie);
		mapa[14][5].wsk_obiekt->dodaj_przedm (new Skorzana_zbroja);
		mapa[14][5].wsk_obiekt->dodaj_przedm (new Slab_mikst_zdrowia);
		mapa[14][5].wsk_obiekt->dodaj_przedm (new Slab_mikst_energii);

		mapa[14][17].wsk_obiekt = new Lucznik;
		mapa[14][17].wsk_obiekt->gracz = 1;
		mapa[14][17].wsk_obiekt->imie = "Sylwester";
		mapa[14][17].wsk_obiekt->dodaj_przedm (new Kusza);
		mapa[14][17].wsk_obiekt->dodaj_przedm (new Slabe_strzaly);
		mapa[14][17].wsk_obiekt->dodaj_przedm (new Mocne_strzaly);
		mapa[14][17].wsk_obiekt->dodaj_przedm (new Kamienie);
		mapa[14][17].wsk_obiekt->dodaj_przedm (new Skorzana_zbroja);
		mapa[14][17].wsk_obiekt->dodaj_przedm (new Slab_mikst_zdrowia);
		mapa[14][17].wsk_obiekt->dodaj_przedm (new Slab_mikst_energii);

		mapa[6][11].wsk_obiekt = new Mag;
		mapa[6][11].wsk_obiekt->gracz = 2;
		mapa[6][11].wsk_obiekt->imie = "Marek";
		mapa[6][11].wsk_obiekt->dodaj_przedm (new Rozdzka_lodu);
		mapa[6][11].wsk_obiekt->dodaj_przedm (new Kostur_lodu);
		mapa[6][11].wsk_obiekt->dodaj_przedm (new Lachmany);
		mapa[6][11].wsk_obiekt->dodaj_przedm (new Mocn_mikst_zdrowia);
		mapa[6][11].wsk_obiekt->dodaj_przedm (new Mocn_mikst_energii);

		mapa[16][11].wsk_obiekt = new Mag;
		mapa[16][11].wsk_obiekt->gracz = 1;
		mapa[16][11].wsk_obiekt->imie = "Mariusz";
		mapa[16][11].wsk_obiekt->dodaj_przedm (new Rozdzka_ognia);
		mapa[16][11].wsk_obiekt->dodaj_przedm (new Kostur_ognia);
		mapa[16][11].wsk_obiekt->dodaj_przedm (new Lachmany);
		mapa[16][11].wsk_obiekt->dodaj_przedm (new Mocn_mikst_zdrowia);
		mapa[16][11].wsk_obiekt->dodaj_przedm (new Mocn_mikst_energii);
	}

	// ustawianie poczatkowych wartosci

	czy_gra = 1;
	tura = 1;
	tryb = 1;

	kurs_y = 11; kurs_x = 11;

	mapa.ustal_poloz ();

	mapa.czysc_wyb ();
	mapa.czysc_info ();
	mapa.czysc_anim ();

	// gra

	while (czy_gra)
	{
		for (int i = 0; i < 23; i++)
		{
			for (int j = 0; j < 23; j++)
			{
				if (mapa[i][j].wsk_obiekt)
				{
					// jesli obiektowi nie powinno zmieniac sie zdrowie lub jesli obiektowi dodano zbyt duzo HP
					if (!mapa[i][j].wsk_obiekt->czy_hp || mapa[i][j].wsk_obiekt->hp_aktual > mapa[i][j].wsk_obiekt->hp_max)
					{
						mapa[i][j].wsk_obiekt->hp_aktual = mapa[i][j].wsk_obiekt->hp_max;
					}

					// jesli obiektowi nie powinny zmieniac sie punkty ruchu lub jesli obiektowi dodano zbyt duzo AP
					if (!mapa[i][j].wsk_obiekt->czy_ap || mapa[i][j].wsk_obiekt->ap_aktual > mapa[i][j].wsk_obiekt->ap_max)
					{
						mapa[i][j].wsk_obiekt->ap_aktual = mapa[i][j].wsk_obiekt->ap_max;
					}

					// tutaj nastepuje smierc obiektow
					if (mapa[i][j].wsk_obiekt->hp_aktual <= 0)
					{
						delete mapa[i][j].wsk_obiekt;
						mapa[i][j].wsk_obiekt = 0;
					}
				}
			}
		}

		// jesli amunicja sie wyczerpala to jest usuwana
		if (jak_obiekt) jak_obiekt->sprawdz_ammo ();

		switch (tryb)
		{
			case 1:

			// ustalanie jak_obiekt
			if (mapa[kurs_y][kurs_x].wsk_obiekt) jak_obiekt = mapa[kurs_y][kurs_x].wsk_obiekt;
			else jak_obiekt = 0;

			// ustalanie czy_przel i czy_rozl
			if (jak_obiekt)
			{
				czy_przel = jak_obiekt->ustal_przel ();

				czy_rozl = jak_obiekt->ustal_rozl ();
			}

			break;
			case 2:

			// ustalanie cel_obiekt
			if (mapa[kurs_y][kurs_x].wsk_obiekt) cel_obiekt = mapa[kurs_y][kurs_x].wsk_obiekt;
			else cel_obiekt = 0;

			// usuwa poprzednie specjalne oznaczenia
			mapa.czysc_info ();

			// tworzy nowe specjalne oznaczenia
			if (mapa[kurs_y][kurs_x].czy_wyb)
			{
				jak_umiej->info ();
			}

			break;
			case 3:

			// ustala jak_umiej
			jak_umiej = jak_obiekt->umiejetnosci[nr_umiej - 1];

			break;
			case 4:

			// ustala polozenia przedmiotow w ekwipunkow
			jak_obiekt->poloz_przedm ();

			// ustala jak_przedm
			jak_przedm = jak_obiekt->ekwipunek[nr_przedm - 1];

			// ustala czy_zaloz
			if (jak_obiekt->ap_aktual >= 1 && !jak_przedm->zaloz)
			{
				czy_zaloz = jak_obiekt->ustal_zaloz (jak_przedm);
			}
			else czy_zaloz = 0;

			break;
			default:break;
		}

		// ustala wyglad wyswietlanej mapy
		mapa.ustal_wyglad ();

		// wyswietla mape z interfejsem
		pokaz ();

		// pobiera znak z klawiatury
		znak = _getch ();

		// jesli wcisnieto strzalki
		if (znak == 224)
		{
			znak = _getch ();

			if (tryb == 1 || tryb == 2)
			{
				switch (znak)
				{
					case 72: if (kurs_y > 0)  kurs_y--; break;
					case 77: if (kurs_x < 22) kurs_x++; break;
					case 80: if (kurs_y < 22) kurs_y++; break;
					case 75: if (kurs_x > 0)  kurs_x--; break;
					default:break;
				}
			}
		}
		else
		{
			// w zaleznosci od znaku i trybu robi co innego
			switch (znak)
			{
				// ESC
				case 27:

				// gra moze byc przerwana w kazdym momencie
				czy_gra = 0;

				break;
				case 'q':

				if (tryb == 1)
				{
					// odnawia kazdemu obiektowi punkty ruchu
					for (int i = 0; i < 23; i++)
					{
						for (int j = 0; j < 23; j++)
						{
							if (mapa[i][j].wsk_obiekt)
							{
								mapa[i][j].wsk_obiekt->ap_aktual = mapa[i][j].wsk_obiekt->ap_max;
							}
						}
					}

					// kursor na srodku mapy
					kurs_y = 11; kurs_x = 11;

					// zmiana gracza
					if (tura == 1) tura = 2; else tura = 1;
				}

				break;
				case 'r':

				switch (tryb)
				{
					case 2:

					// oczyszcza mape z oznaczen
					mapa.czysc_wyb ();
					mapa.czysc_info ();

					// kursor z powrotem na miejscu obiektu
					kurs_y = jak_obiekt->wsp_y;
					kurs_x = jak_obiekt->wsp_x;

					// z powrotem do umiejetnosci
					tryb = 3;

					break;
					case 3:

					// usuwa tablice umiejetnosci
					delete[] jak_obiekt->umiejetnosci;
					jak_obiekt->ile_skill = 0;

					// z powrotem do wyboru obiektu
					tryb = 1;

					break;
					case 4:

					// z powrotem do wyboru obiektu
					tryb = 1;

					break;
					default:break;
				}

				break;
				case 'e':

				switch (tryb)
				{
					case 1:

					if (jak_obiekt)
					{
						// jesli obiekt posiada ekwipunek i nalezy do gracza
						if (jak_obiekt->czy_ekwip && jak_obiekt->ekw_aktual != 0 && jak_obiekt->gracz == tura)
						{
							// pierwszy przedmiot w ekwipunku
							nr_przedm = 1;

							// do ekwipunku
							tryb = 4;
						}
					}

					break;
					case 2:

					// gdy obrano cel
					if (mapa[kurs_y][kurs_x].czy_wyb)
					{
						// wykonuje umiejetnosc
						jak_umiej->cel ();

						// zmniejsza pukty ruchu o koszt uzycia umiejetnosci
						jak_obiekt->ap_aktual -= jak_umiej->koszt_skill;

						// usuwa tablice umiejetnosci
						delete[] jak_obiekt->umiejetnosci;
						jak_obiekt->ile_skill = 0;

						// czysci mape z oznaczen i animacji
						mapa.czysc_wyb ();
						mapa.czysc_info ();
						mapa.czysc_anim ();

						// ustala polozenie obiektow
						mapa.ustal_poloz ();

						// kursor na srodku mapy
						kurs_y = 11; kurs_x = 11;

						// z powrotem do wyboru obiektu
						tryb = 1;
					}

					break;
					case 3:
					
					// gdy wybrano umiejetnosc
					if (jak_obiekt->ap_aktual >= jak_umiej->koszt_skill)
					{
						// tworzy oznaczenia na mapie
						jak_umiej->wybierz ();

						tryb = 2;
					}

					break;
					case 4:

					// uzycie przedmiotu z rodzaji 0-inne
					if (jak_przedm->rodzaj == 0)
					{
						if (jak_obiekt->ap_aktual >= ((Inne*) jak_przedm)->koszt_item)
						{
							// "animacja" uzycia przedmiotu
							jak_przedm->zaloz = 1;
							pokaz (); Sleep (500);
							jak_przedm->zaloz = 0;

							// uzycie przedmiotu
							((Inne*) jak_przedm)->uzyj ();

							// zmniejszenie punktow ruchu o koszt uzycia przedmiotu
							jak_obiekt->ap_aktual -= ((Inne*) jak_przedm)->koszt_item;

							// usuniecie uzytego przedmiotu z ekwipunku
							jak_obiekt->usun_przedm (jak_przedm);

							// przejscie do przedmiotu postawionego nizej
							nr_przedm--;
						}
					}
					// zdjecie zalozonego przedmiotu
					else if (jak_przedm->zaloz)
					{
						jak_obiekt->zdejmij_przedm (jak_przedm);
					}
					// zalozenie nadajacego sie przedmiotu
					else if (czy_zaloz)
					{
						jak_obiekt->zaloz_przedm (jak_przedm);
					}

					break;
					default:break;
				}

				break;
				case 'u':

				switch (tryb)
				{
					case 1:

					if (jak_obiekt)
					{
						if (jak_obiekt->czy_umiej && jak_obiekt->gracz == tura)
						{
							// tworzy tablice umiejetnosci
							jak_obiekt->ustaw_skill ();

							// pierwsza umiejetnosc w tablicy
							nr_umiej = 1;

							// do umiejetnosci
							tryb = 3;
						}
					}

					break;
					default:break;
				}

				break;
				case 'a':

				switch (tryb)
				{
					case 3:

					// poprzednia umiejetnosc
					if (nr_umiej > 1) nr_umiej--;

					break;
					case 4:

					// poprzedni przedmiot
					if (nr_przedm > 1) nr_przedm--;

					break;
					default:break;
				}

				break;
				case 'd':

				switch (tryb)
				{
					case 3:

					// nastepna umiejetnosc
					if (nr_umiej < jak_obiekt->ile_skill) nr_umiej++;

					break;
					case 4:

					// nastepny przedmiot
					if (nr_przedm < jak_obiekt->ekw_aktual) nr_przedm++;

					break;
					default:break;
				}

				break;
				case 'w':

				switch (tryb)
				{
					case 1:

					if (czy_przel)
					{
						// laduje pociski
						jak_obiekt->poj_aktual += jak_obiekt->wsk_ammo->przel;
						jak_obiekt->wsk_ammo->pojemnosc -= jak_obiekt->wsk_ammo->przel;

						// zmniejsza punkty ruchu o 1
						jak_obiekt->ap_aktual -= 1;
					}

					break;
					default:break;
				}

				break;
				case 's':

				switch (tryb)
				{
					case 1:

					if (czy_rozl)
					{
						// przywraca pociski z powrotem do amunicji
						jak_obiekt->wsk_ammo->pojemnosc += jak_obiekt->poj_aktual;
						jak_obiekt->poj_aktual = 0;
					}

					break;
					default:break;
				}

				break;
				default:break;
			}
		}
	}

	return 0;
}
