#include "Streckenende.h"
#include "Fahrzeug.h"
#include "Weg.h"


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
}