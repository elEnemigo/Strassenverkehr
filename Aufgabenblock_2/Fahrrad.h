#pragma once
#include "Fahrzeug.h"

class Fahrrad :
	public Fahrzeug
{
public:
	Fahrrad();
	Fahrrad(std::string Name, double dGeschwind);
	~Fahrrad();

	virtual void vZeichnen(Weg* pWeg) const;
	virtual double dGeschwindigkeit() const;
};

