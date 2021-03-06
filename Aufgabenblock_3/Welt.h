#pragma once

#include <istream>
#include <list>

class Kreuzung;
class Fahrzeug;

class Welt
{
private:
	std::list<Kreuzung*> p_pKreuzungen;
	std::list<Fahrzeug*> p_pFahrzeuge;
	bool p_bGrafik;

public:
	Welt();
	~Welt();

	void vEinlesen(std::istream& In);
	void vEinlesenMitGrafik(std::istream& In);
	void vSimulation(double dT);
};

