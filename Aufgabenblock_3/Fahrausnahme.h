#pragma once

#include <iostream>

// Prototypen
class Fahrzeug;
class Weg;

class Fahrausnahme
{
protected:
	Fahrzeug* p_pFahrzeug;
	Weg* p_pWeg;

public:
	Fahrausnahme(Fahrzeug* pFahrzeug, Weg* pWeg);
	~Fahrausnahme();

	virtual void vBearbeiten() = 0;
};

