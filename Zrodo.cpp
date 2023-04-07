#include "Klasy/Gracz.h"
#include "Klasy/Karta.h"
#include "Klasy/Kasyno.h"
#include "Klasy/GraczKomputerowy.h"
#include <time.h>

int main()
{
	srand(time(NULL));
	Kasyno kasyno(2, 2);
	kasyno.graj();
	return 0;
};