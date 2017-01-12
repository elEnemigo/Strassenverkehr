#pragma once
#include "FzgVerhalten.h"

#include <iostream>

extern double dGlobaleZeit;

class FzgParken :
	public FzgVerhalten
{
private:
	double p_dStartT;

public:
	FzgParken(Weg *pWeg, double dStartzeitpunkt);
	~FzgParken();

	virtual double dStrecke(Fahrzeug* pFahrzeug, double dT) const;
};

