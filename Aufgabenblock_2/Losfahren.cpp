#include "Losfahren.h"
#include "Fahrzeug.h"
#include "Weg.h"

Losfahren::Losfahren(Fahrzeug* pFahrzeug, Weg* pWeg) :
	Fahrausnahme(pFahrzeug, pWeg)
{
}


Losfahren::~Losfahren()
{
}

void Losfahren::vBearbeiten()
{
	std::cout << "----------Exception----------" << std::endl;
	std::cout << *p_pFahrzeug << std::endl;
	std::cout << *p_pWeg << std::endl;
	std::cout << "Losgefahren!" << std::endl;
	std::cout << "----------noitpecxE----------" << std::endl;

	p_pWeg->vAbgabe(p_pFahrzeug);
	p_pFahrzeug->vNeueStrecke(p_pWeg);
	//p_pWeg->vAnnahme(p_pFahrzeug);
}