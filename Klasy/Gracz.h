#pragma once
#include <iostream>
#include <string>
#include "Karta.h"

class Kasyno;

class Gracz {
protected:
	Karta Reka[10] = { 0 };
	Kasyno* kasyno;
	int ile; 
	bool granie;
	char nazwa[20];

public:
	Gracz();
	Gracz(char n[20]);
	Karta* getReka() { return Reka; }
	void wezKarte(Karta* _karta);
	void wyswielt();
	void zeruj_gracza();
	bool grasz();
	bool get_granie() const { return granie; };
	int getIle() { return ile; }
	int ile_p();
	char* getNazwa() { return nazwa; }

	
};