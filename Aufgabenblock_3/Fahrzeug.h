#pragma once
#include "AktivesVO.h"
#include "Streckenende.h"

// Prototypen
class FzgVerhalten;
class Weg;

class Fahrzeug : public AktivesVO
{
private:
	virtual void vInitialisierung();

protected:
	double p_dMopsGeschwindigkeit;
	double p_dGesamtStrecke;
	double p_dAbschnittStrecke;
	FzgVerhalten* p_pVerhalten;

public:
	// Konstruktoren/Destruktoren
	Fahrzeug();
	Fahrzeug(const Fahrzeug& Obj);
	Fahrzeug(const std::string sName);
	Fahrzeug(const std::string sName, double dMaxGeschwindigkeit);
	~Fahrzeug();

	// Methoden
	void vNeueStrecke(Weg* pWeg);
	void vNeueStrecke(Weg* pWeg, double dStartzeit);
	double dGetAbschnittStrecke() const;

	// Virtuelle Methoden
	virtual void vAusgabe() const;
	virtual void vAbfertigung();
	virtual void vZeichnen(const Weg* pWeg) const;
	virtual double dTanken(double dMenge = 0);
	virtual double dGeschwindigkeit() const;
	virtual double dGetTankinhalt() const;
	virtual std::ostream& ostreamAusgabe(std::ostream& Out) const;
	virtual std::istream& istreamEingabe(std::istream& In);

	// Überladene Operatoren
	bool operator<(const Fahrzeug& Other);
	Fahrzeug& operator=(const Fahrzeug& Rhs);
};