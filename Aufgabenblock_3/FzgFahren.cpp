#include "FzgFahren.h"
#include "Weg.h"
#include "Fahrzeug.h"

FzgFahren::FzgFahren(Weg* pWeg) :
	FzgVerhalten(pWeg)
{
}


FzgFahren::~FzgFahren()
{
}

double FzgFahren::dStrecke(Fahrzeug* pFahrzeug, double dT) const
{
	double dStrecke;
	double dRestStrecke;

	dRestStrecke = p_pWeg->dGetVirtuelleSchranke() - pFahrzeug->dGetAbschnittStrecke();
	dStrecke = std::fmin(dRestStrecke, pFahrzeug->dGeschwindigkeit() * dT);

	p_pWeg->dSetVirtuelleSchranke(pFahrzeug->dGetAbschnittStrecke() + dStrecke);

	return dStrecke;
}