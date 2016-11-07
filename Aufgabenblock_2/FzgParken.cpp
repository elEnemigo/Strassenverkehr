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
	if (dGlobaleZeit < p_dStartT)
		return 0.0;
	else
	{
		std::cout << "Startzeit erreicht!\n";
		exit(2);
	}
}