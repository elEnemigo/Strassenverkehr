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

	// Pointer zum Weg zur�ckgeben
	Weg* pGetWeg() const;

	// In dT zur�cklegbare Strecke ohne Wegende zu erreichen
	virtual double dStrecke(Fahrzeug* pFahrzeug, double dT) const;
};

