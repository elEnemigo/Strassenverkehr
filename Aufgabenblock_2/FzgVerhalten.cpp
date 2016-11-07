#include "FzgVerhalten.h"
#include "Fahrzeug.h"
#include "Weg.h"

FzgVerhalten::FzgVerhalten(Weg* pWeg) :
	p_pWeg(pWeg)
{
}

FzgVerhalten::~FzgVerhalten()
{
}

Weg* FzgVerhalten::pGetWeg() const
{
	return p_pWeg;
}

double FzgVerhalten::dStrecke(Fahrzeug* pFahrzeug, double dT) const
{
	double dStrecke;
	double dRestStrecke;

	dRestStrecke = p_pWeg->dGetLaenge() - pFahrzeug->dGetAbschnittStrecke();
	dStrecke = std::fmin(dRestStrecke, pFahrzeug->dGeschwindigkeit() * dT);

	return dStrecke;
}