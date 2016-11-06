#pragma once
#include "Fahrzeug.h"
#include <math.h>

class PKW :
	public Fahrzeug
{
private:
	double p_dVerbrauch;
	double p_dTankinhalt;
	double p_dTankvolumen;

public:
	PKW();
	PKW(std::string sName, double dMordsGeschwindigkeit, double dVerbrauch, double dTankvolumen = 55.0);
	~PKW();

	virtual void vAusgabe() const;
	virtual void vAbfertigung();
	virtual double dTanken(double dMenge = 0);
	virtual double dGeschwindigkeit() const;
	virtual std::ostream& ostreamAusgabe(std::ostream& Out) const;

	double dVerbrauch() const;
};

