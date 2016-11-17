#pragma once

#include "Losfahren.h"

// Prototypen
class Weg;
class Fahrzeug;

class FzgVerhalten
{
protected:
	Weg* p_pWeg;

public:
	FzgVerhalten(Weg* pWeg);
	~FzgVerhalten();

	Weg* pGetWeg() const;

	virtual double dStrecke(Fahrzeug* pFahrzeug, double dT) const;
};

