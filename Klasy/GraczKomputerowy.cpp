#include "GraczKomputerowy.h"
#include <string>

GraczKomputerowy::GraczKomputerowy(int o) : odwaga(o) {};
bool GraczKomputerowy::grasz() {
	/*
	21-2.3*odwaga-0.6
	odwaga 1 : gra do 18 - ryzykuj�cy
	odwaga 2 : gra do 15 - normalny
	odwaga 3 : gra do 13 - zachowawczy
	*/
	if (ile_p() > 21) {
		std::cout << "Nie mozesz dobrac wiecej kart\n";
		granie = false;
	}
	else if (ile_p() < (21 - 2.3 * odwaga - 0.6)) {
		granie = true;
	}
	else {
		granie = false;
	}

	return granie;
}
void GraczKomputerowy::nadaj_identyfikator(int nr_bota) {
	std::string n = "Bot";
	n += std::to_string(nr_bota);
	strcpy_s(nazwa, n.c_str());
}