#pragma once

#include "Gracz.h"

class GraczKomputerowy : public Gracz {
	int odwaga;
public:
	GraczKomputerowy(int o);
	bool grasz();
	void nadaj_identyfikator(int nr_bota);
};