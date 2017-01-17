#include "Streckenende.h"
#include "Fahrzeug.h"
#include "Weg.h"
#include "Kreuzung.h"


Streckenende::Streckenende(Fahrzeug* pFahrzeug, Weg* pWeg) :
	Fahrausnahme(pFahrzeug, pWeg)
{
}


Streckenende::~Streckenende()
{
}

void Streckenende::vBearbeiten()
{
	std::cout << "----------Exception----------" << std::endl;
	std::cout << *p_pFahrzeug << std::endl;
	std::cout << *p_pWeg << std::endl;
	std::cout << "Streckenende erreicht!" << std::endl;
	std::cout << "----------noitpecxE----------" << std::endl;

	p_pWeg->vAbgabe(p_pFahrzeug);
	Weg* ZRuck = p_pWeg->pGetRueckweg();
	Weg* Neu = nullptr;
	Kreuzung* pK = p_pWeg->pGetNaechsteKreuzung();

	if (pK)
	{
		Neu = pK->ptZufaelligerWeg(p_pWeg);
		pK->vAnnahme(p_pFahrzeug, Neu);

		std::cout << "ZEIT		: " << dGlobaleZeit << std::endl;
		std::cout << "KREUZUNG	: " << pK->sGetName() << " | " << pK->dGetTankstelle() << std::endl;
		std::cout << "WECHSEL	: " << p_pWeg->sGetName() << " -> " << Neu->sGetName() << std::endl;
		std::cout << "FAHRZEUG	: " << *p_pFahrzeug << std::endl;
	}
}