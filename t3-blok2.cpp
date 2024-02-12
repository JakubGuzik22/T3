#include <iostream>
#include <cassert>
#include <exception>

using namespace std;

const char* const DOST[] = { "dostepny", "niedostepny", "w_produkcji", "zarezerwowany" };

enum class Dostepnosc {
	dostepny, niedostepny, w_produkcji, zarezerwowany
};

struct Autor
{
	char nazwa[100];
};

struct Obraz
{
	char nazwa[200];
	double wartosc;
	Autor * autor;
	Dostepnosc dostepnosc;
};

void obrazyAutora(Obraz* dane, uint16_t n, Autor* autor, Obraz* wynik, uint16_t& licznik) 
{
	int poprawny = 0;

	assert(dane != nullptr || sizeof(dane) == n);

	for (int i = 0; i < n; i++) {
		
		if (dane[i].autor == autor)  // nie sprawdzamy konkretnego pola ponieważ struktura ma tylko jedno pole
		{
			poprawny++;
			wynik[licznik++] = dane[i];
		}
	}
	if (poprawny == 0)
	{
		throw invalid_argument("");
	}
}

void wypelnijInstancje(Obraz * ob,  const char* nazwa, double wart, Autor* autor, Dostepnosc dostepnosc) {
	strcpy_s(ob->nazwa, 200, nazwa);
	ob->wartosc = wart;
	ob->autor = autor;
	ob->dostepnosc = dostepnosc;
}

void wypiszInstancje(Obraz* ob) {
	cout << "Autor: " << ob->autor->nazwa << '\t' << "Nazwa: " << ob->nazwa << endl;
	cout << "Wartosc: " << ob->wartosc << '\t' << "Dostepnosc: " << DOST[int(ob->dostepnosc)] << endl;
}

void test_wyjatku()
{
	Autor autorzy[] = {
		"Ja",
		"Pan Zdzisław z Wąchocka",
		"P.B.Bezołowiowy",
		"Kolega Andrzej",
		"Pan Radek"
	};
	Obraz bazgroly[] =
	{
		/*{"Ja i kury cioci Jadzi",2.99,&autorzy[0],Dostepnosc::dostepny},
		{"Dom na tle wysypiska",4.89,&autorzy[1],Dostepnosc::niedostepny},
		{"Plama ropy?",501.29,&autorzy[2],Dostepnosc::dostepny},
		{"Lorem",21.29,&autorzy[3],Dostepnosc::dostepny},
		{"Ipsum",51.29,&autorzy[4],Dostepnosc::w_produkcji},
		{"Plama niewiadomego pochodzenia",91.79,&autorzy[3],Dostepnosc::zarezerwowany},
		{"Bocian",101.29,&autorzy[4],Dostepnosc::niedostepny}*/
		{}
	};

	//zakomentowanie zawartości tabeli bazgroly (z zostawieniem jednego pustego nawiasu klamrowego {}) pozwala sprawdzić poprawność działania testu.
	//w obecnym stanie test zwraca "OK" natomiast gdy odkkomentuje sie zawartosc, wyjatek nie wystepuje, test zwraca "FAILED"
	//nie jestem pewny czy zrozumiałem polecenie 5, ale mam nadzieje że o to chodziło

	uint16_t n = sizeof(bazgroly) / sizeof(bazgroly[0]);

	Obraz wynik[100];
	uint16_t licznik = 0;

	try {
		obrazyAutora(bazgroly, n, &autorzy[3], wynik, licznik);
		cout << "Test FAILED!" << endl;
	}
	catch (const exception&) {
		cout << "Test OK!" << endl;
	}
}

int main()
{
	setlocale(LC_ALL, "");
	Autor autorzy[] = {
		"Ja",
		"Pan Zdzisław z Wąchocka",
		"P.B.Bezołowiowy",
		"Kolega Andrzej",
		"Pan Radek"
	};
	Obraz bazgroly[] =
	{
		{"Ja i kury cioci Jadzi",2.99,&autorzy[0],Dostepnosc::dostepny},
		{"Dom na tle wysypiska",4.89,&autorzy[1],Dostepnosc::niedostepny},
		{"Plama ropy?",501.29,&autorzy[2],Dostepnosc::dostepny},
		{"Lorem",21.29,&autorzy[3],Dostepnosc::dostepny},
		{"Ipsum",51.29,&autorzy[4],Dostepnosc::w_produkcji},
		{"Plama niewiadomego pochodzenia",91.79,&autorzy[3],Dostepnosc::zarezerwowany},
		{"Bocian",101.29,&autorzy[4],Dostepnosc::niedostepny},
		{}
	};
	uint16_t n = sizeof(bazgroly) / sizeof(bazgroly[0]);
	wypelnijInstancje(&bazgroly[7], "Dom nad stawem", 10.10, &autorzy[3], Dostepnosc::w_produkcji);
	wypiszInstancje(&bazgroly[7]); 

	Obraz wynik[100];
	uint16_t licznik = 0;

	obrazyAutora(bazgroly, n, &autorzy[4], wynik, licznik);

	cout << endl;
	cout << "OBRAZY WSKAZANEGO AUTORA: " << endl;
	for (int i = 0; i < licznik; i++) {
		wypiszInstancje(&wynik[i]);
	}


	cout << endl;
	cout << "Test wyjątku: ";
	test_wyjatku();
}

