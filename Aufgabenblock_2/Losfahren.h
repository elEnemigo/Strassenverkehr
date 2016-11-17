#pragma once
#include "Fahrausnahme.h"

class Losfahren :
	public Fahrausnahme
{
public:
	Losfahren(Fahrzeug* pFahrzeug, Weg* pWeg);
	~Losfahren();

	virtual void vBearbeiten();
};

