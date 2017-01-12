#pragma once
#include "Fahrausnahme.h"

class Streckenende :
	public Fahrausnahme
{
public:
	Streckenende(Fahrzeug* pFahrzeug, Weg* pWeg);
	~Streckenende();

	virtual void vBearbeiten();
};

