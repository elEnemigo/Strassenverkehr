#include "Welt.h"
#include "AktivesVO.h"
#include "Kreuzung.h"
#include "SimuClient.h"

Welt::Welt() :
	p_dZeit(0.0), p_bGrafik(false)
{
	dGlobaleZeit = 0.0;
}


Welt::~Welt()
{
	for (AktivesVO* pK : p_pKreuzungen)
		if (pK)
			delete pK;
	p_pKreuzungen.clear();

	if (p_bGrafik)
		vBeendeGrafik();
}

void Welt::vEinlesen(std::istream& In)
{
	std::string sType;

	while (In >> sType)
	{
		if (sType == "KREUZUNG")
		{
			Kreuzung* pK = new Kreuzung;

			In >> *pK;
			p_pKreuzungen.push_back(pK);
		}
		else
		{
			throw std::string("Fehler beim Einlesen!");
		}
	}
}

void Welt::vSimulation(double dT)
{
	dGlobaleZeit += dT;

	std::cout << "						T = " << dGlobaleZeit << std::endl;

	for (Kreuzung* pK : p_pKreuzungen)
	{
		pK->vAbfertigung();

		std::cout << pK->sGetName() << *pK << std::endl;

		if (p_bGrafik)
			pK->vZeichne();
	}
}