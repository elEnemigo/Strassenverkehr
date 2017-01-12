#include "FzgParken.h"
#include "Weg.h"

FzgParken::FzgParken(Weg* pWeg, double dStartZeitpunkt) :
	FzgVerhalten(pWeg), p_dStartT(dStartZeitpunkt)
{
}


FzgParken::~FzgParken()
{
}

double FzgParken::dStrecke(Fahrzeug* pFahrzeug, double dT) const
{
	if ((dGlobaleZeit + DBL_EPSILON) < p_dStartT)
		return 0.0;
	else
	{
		//std::cout << "Startzeit erreicht!\n";
		throw Losfahren(pFahrzeug, p_pWeg);
		return 0.0;
		//exit(2);
	}
}