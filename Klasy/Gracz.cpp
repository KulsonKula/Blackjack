#include "Gracz.h"

Gracz::Gracz() {
	ile = 0;
	granie = 1;
	strcpy_s(nazwa, "gracz");
}
Gracz::Gracz(char n[20]) {
	ile = 0;
	granie = 1;
	strcpy_s(nazwa, n);
}
void Gracz::wezKarte(Karta* _karta)
{
	Reka[ile] = *_karta;
	ile++;
}
void Gracz::wyswielt()
{
	for (int i = 0; i < ile; i++)
	{
		Karta _k = Reka[i];
		std::cout << "Karta nr " << i+1 << ":" << "\n";
		_k.wypisz();
		std::cout << std::endl;
	}
}
int Gracz::ile_p() {
	int P = 0;
	for (int i = 0; i < ile; i++)
	{
		P += Reka[i].getWartosc();
	}

	return P;
}
bool Gracz::grasz() {
	if (ile_p() > 21)
	{
		std::cout << "Nie mozesz dobrac wiecej kart\n";
		granie = false;
		return false;
	}
	else if(granie)
	{
		std::cout << "Czy chesz dodac karte?\n";
		std::cout << "0 - Spasuj\n1 - Dobierz karte\n";
		while (true) {
			std::cin >> granie;
			if (std::cin.fail() == true) {
				std::cout << "Wykryto blad" << std::endl;
				std::cin.clear();
				std::cin.ignore(256, '\n');
			}
			else break;
		}
		if (granie)
			return true;
		else
			return false;
	}
	return false;
};
void Gracz::zeruj_gracza() {
	for (int i = 0; i < 10; i++) {
		Reka[i] = 0;
	}
	ile = 0;
	granie = 1;

}