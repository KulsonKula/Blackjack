#pragma once
#include <iostream>
#include <fstream>
#include "Karta.h"
#include "Gracz.h"
#include "GraczKomputerowy.h"

class Kasyno {
private: 
	Karta* talia[52];
	Gracz* graczeP[5];
	GraczKomputerowy* graczeK[3];
	int ktora;
	int ilu_graczyP;
	int ilu_graczyK;
public:
	Kasyno(int GP,int GK);
	Karta* dajKarte();
	void Tasuj();
	void graj();
	void zapisz(Gracz* gracz);
	void oddziel_gry();
};