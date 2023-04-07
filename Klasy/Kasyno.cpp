#include "Kasyno.h"


Kasyno::Kasyno(int GP,int GK) {
	int i = 0;
	for (int k=0;k < 4;k++)
	{
		for (int w = 0; w < 13; w++)
		{
			Karta* _karta = new Karta(k, w);
			talia[i] = _karta;
			i++;
		}
	}


	ktora = 0;
	ilu_graczyP = GP;
	ilu_graczyK = GK;

	for (i = 0; i < GP; i++)
	{
		char n[20];
		std::cout << "Podaj nazwe gracza " << i+1 << ": ";
		while (true) {
			std::cin >> n;
			if (std::cin.fail() == true) {
				std::cout << "Wykryto blad" << std::endl;
				std::cin.clear();
				std::cin.ignore(256, '\n');
			}
			else break;
		}
		Gracz* _gracz = new Gracz(n);
		graczeP[i] = _gracz;
	}


	for (i = 0; i < GK; i++)
	{
		int odwaga_bota = rand() % 3 + 1;
		GraczKomputerowy* _gracz = new GraczKomputerowy(odwaga_bota);
		_gracz->nadaj_identyfikator(i);
		graczeK[i] = _gracz;
	} 
}
void Kasyno::Tasuj() 
{
	for (int i=1; i <= 100; i++)
	{
		int L1 = rand() % 52;
		int L2 = rand() % 52;
		std::swap(talia[L1], talia[L2]);
		ktora = 0;
	}

}
Karta* Kasyno::dajKarte()
{
	Karta* _z = talia[ktora];
	ktora++;
	return _z;
}
void Kasyno::zapisz(Gracz* gracz) {
	std::ofstream plik;
	plik.open("gracze.txt", std::ofstream::app);
	plik.width(20);
	plik << std::left << gracz->getNazwa();
	for (int i = 0; i < gracz->getIle(); i++) {
		plik << std::left << gracz->getReka()[i].getFigura();

		char kolor[10];

		switch (gracz->getReka()[i].getKolor()) {
		case 3: {
			strcpy_s(kolor, "kier");
			break;
		}
		case 4: {
			strcpy_s(kolor, "karo");
			break;
		}
		case 5: {
			strcpy_s(kolor, "trefl");
			break;
		}
		case 6: {
			strcpy_s(kolor, "pik");
			break;
		}
		
		}
		plik << kolor << " " ;
	}
	plik.width(20);
	plik << std::right <<gracz->ile_p()<<"\n";
	

	plik.close();
}
void Kasyno::oddziel_gry() {
	std::ofstream plik;
	plik.open("gracze.txt", std::ofstream::app);

	plik << "\n---------------------------\n";

	plik.close();
}
void Kasyno::graj()
{
	bool running = 1;
	while (running)
	{
		bool czy_gramy_k = 1;
		bool czy_gramy_p = 1;
		int i = 0;

		for (i = 0; i < ilu_graczyP; i++) {
			graczeP[i]->zeruj_gracza();
		}
		for (i = 0; i < ilu_graczyK; i++) {
			graczeK[i]->zeruj_gracza();
		}

		Tasuj();
 
		for (i = 0; i < ilu_graczyP; i++) 
		{
			graczeP[i]->wezKarte(dajKarte());
			graczeP[i]->wezKarte(dajKarte());
		}
		for (i = 0; i < ilu_graczyK; i++)
		{
			graczeK[i]->wezKarte(dajKarte());
			graczeK[i]->wezKarte(dajKarte());
		}


		while (true)
		{
			// Sprawdzanie czy jakikolwiek gracz prawdziwy wyraza chec dobrania karty
			for (i = 0; i < ilu_graczyP; i++) 
			{
				if (graczeP[i]->get_granie())
				{
					czy_gramy_p = true;
					break;
				}

			}
			
			//jezeli wszyscy nie spasowali - tura graczy prawdziwych
			if (czy_gramy_p)
			{
				
				for (i = 0; i < ilu_graczyP; i++)
				{
					std::cout << "\nTura gracza nr: " << i + 1;
					std::cout << "\nMasz aktualnie: " << graczeP[i]->ile_p() << " punktow\n";
					if (graczeP[i]->grasz())
					{
						graczeP[i]->wezKarte(dajKarte());
						std::cout << "Masz aktualnie: " << graczeP[i]->ile_p() << " punktow\n";
					}
				}
			}

			// Sprawdzanie czy jakikolwiek gracz komputerowy wyraza chec dobrania karty
			for (i = 0; i < ilu_graczyK; i++)
			{
				if (graczeK[i]->get_granie())
				{
					czy_gramy_k = true;
					break;
				}
			}

			// jezeli wszyscy nie spasowali - tura graczy komputerowych
				if (czy_gramy_k)
				{

					for (i = 0; i < ilu_graczyK; i++)
					{
						std::cout << graczeK[i]->getNazwa();
						std::cout << " ma aktualnie: " << graczeK[i]->ile_p() << " punktow\n";
						if (graczeK[i]->grasz())
						{
							graczeK[i]->wezKarte(dajKarte());
							std::cout << graczeK[i]->getNazwa();
							std::cout << " ma aktualnie: " << graczeK[i]->ile_p() << " punktow\n";
						}
					}
					
				}
			if(!czy_gramy_k && !czy_gramy_p)
			{
				int MAX = 0;
				int ilosc_zw = 1;
				
				for (i = 0; i < ilu_graczyP; i++)
				{
					if (graczeP[i]->ile_p() <= 21) {
						if (MAX < graczeP[i]->ile_p()){
							MAX = graczeP[i]->ile_p();
							ilosc_zw = 1;

						}
						else if (MAX == graczeP[i]->ile_p()) {
							ilosc_zw++;
						}
					}
				}
				for (i = 0; i < ilu_graczyK; i++)
				{
					if (graczeK[i]->ile_p() <= 21) {
						if (MAX < graczeK[i]->ile_p()) {
							MAX = graczeK[i]->ile_p();
							ilosc_zw = 1;
						}
						else if (MAX == graczeK[i]->ile_p()) {
							ilosc_zw++;
						}
					}
				}
				int* NRM = new int[ilosc_zw]();
				bool* NRM_czy_gracz = new bool[ilosc_zw]();
				

				int j = 0;
				for (i = 0; i < ilu_graczyP;i++) {
					if (MAX == graczeP[i]->ile_p()) {
						NRM[j] = i;
						NRM_czy_gracz[j] = true;
						j++;
					}
				}
				for (i = 0; i < ilu_graczyK; i++) {
					if (MAX == graczeK[i]->ile_p()) {
						NRM[j] = i;
						NRM_czy_gracz[j] = false;
						j++;
					}
				}

				if (MAX != 0) {
					if (ilosc_zw == 1) {
						std::cout << "Wygrywa: ";
						if (NRM_czy_gracz[0]) {
							std::cout << graczeP[NRM[0]]->getNazwa() << std::endl;
						}
						else {
							std::cout << graczeK[NRM[0]]->getNazwa() << std::endl;
						}
					}
					else if (ilosc_zw > 1) {
						std::cout << "\nWygrywaja:\n";
						for (i = 0; i < ilosc_zw; i++) {
							if (NRM_czy_gracz[i]) {
								std::cout << graczeP[NRM[i]]->getNazwa() << std::endl;
							}
							else {
								std::cout << graczeK[NRM[i]]->getNazwa() << std::endl;
							}
							
						}
					}
				}
				else {
					std::cout << "\nWszyscy przegrali :(";
				}

				bool zapisac_graczy = false;
				std::cout << "\n\nCzy chcesz zapisac graczy?\n0- nie\n1- tak\n";
				while (true) {
					std::cin >> zapisac_graczy;
					if (std::cin.fail() == true) {
						std::cout << "Wykryto blad" << std::endl;
						std::cin.clear();
						std::cin.ignore(256, '\n');
					}
					else break;
				}
				//zapisanie graczy do pliku
				if (zapisac_graczy) {
					for (i = 0; i < ilu_graczyP; i++) {
						zapisz(graczeP[i]);
					}
				}
				if (zapisac_graczy) {
					for (i = 0; i < ilu_graczyK; i++) {
						zapisz(graczeK[i]);
					}
					oddziel_gry();
				}
				

				delete[]NRM;
				delete[]NRM_czy_gracz;

				break;
			}
			czy_gramy_k = false;
			czy_gramy_p = false;
		}

		

		std::cout << "\nCzy chcesz rozpoczac kolejna gre?";
		std::cout << "\n0 - koniec grania\n1 - nastepna gra\n";
		while (true) {
			std::cin >> running;
			if (std::cin.fail() == true) {
				std::cout << "Wykryto blad" << std::endl;
				std::cin.clear();
				std::cin.ignore(256, '\n'); 
			} 
			else break;
		}

	}
};