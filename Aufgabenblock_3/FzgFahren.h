#pragma once
#include "FzgVerhalten.h"

class FzgFahren :
	public FzgVerhalten
{
public:
	FzgFahren(Weg* pWeg);
	~FzgFahren();

	virtual double dStrecke(Fahrzeug* pFahrzeug, double dT) const;
};

