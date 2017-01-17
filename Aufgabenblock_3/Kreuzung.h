#pragma once

#include "AktivesVO.h"
#include "Weg.h"
#include <list>

// Prototypen / Forward declarations
class Weg;
class Fahrzeug;

class Kreuzung : public AktivesVO
{
public:
	Kreuzung();
	Kreuzung(std::string sName);
	~Kreuzung();

	void vVerbinde(std::string WegHin, std::string WegZruck, Kreuzung* pGegenKreuzung, double dWegLaenge, Begrenzung eLimit = Autobahn, bool bUeberholverbot = true);
	void vVerbinde(Weg* pWegHin, Weg* pWegZruck, Kreuzung* pGegenKreuzung);
	void vTanken(Fahrzeug* pFahrzeug);
	void vAnnahme(Fahrzeug* pFahrzeug, double dStartzeit);
	void vAnnahme(Fahrzeug* pFahrzeug, Weg* pWeg);
	void vAbfertigung();
	void vZeichne() const;
	void vSetTankstelle(double dInhalt);
	double dGetTankstelle() const;
	Weg* ptZufaelligerWeg(Weg* pWeg) const;

	virtual std::ostream& ostreamAusgabe(std::ostream& Out) const;

private:
	std::list<Weg*> p_pWege;	// Alle von der Kreuzung wegführenden Wege
	double p_dTankstelle;	// Tankinhalt der Tankstelle
};

