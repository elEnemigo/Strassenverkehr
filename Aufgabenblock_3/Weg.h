#pragma once
#include "AktivesVO.h"
#include "LazyListe.h"
#include <list>

class Fahrzeug;
class FzgVerhalten;
//template <T> class LazyListe;

enum Begrenzung {
	Innerorts = 50,
	Land = 100,
	Autobahn = 0
};

class Weg :
	public AktivesVO
{
private:
	double p_dLaenge;
	double p_dVirtuelleSchranke;
	Begrenzung p_eLimit;
	bool p_bUeberholverbot;
	//std::list<Fahrzeug*> p_pFahrzeuge;	// Pointer, da es viel effizienter ist einen Pointer in der Liste zu ändern als ein Objekt zu löschen und eine Kopie davon in einer neuen Liste zu speichern.
	LazyListe<Fahrzeug*> p_pFahrzeuge;

	void vInitialisierung();
public:
	Weg();
	Weg(std::string sName, double dLaenge, Begrenzung eLimit = Autobahn, bool bUeberholverbot = true);
	~Weg();

	void vAnnahme(Fahrzeug* pFahrzeug);
	void vAnnahme(Fahrzeug* pFahrzeug, double dStartZeit);
	void vAbgabe(Fahrzeug* pFahrzeug);
	double dGetLaenge() const;
	double dGetVirtuelleSchranke() const;
	void dSetVirtuelleSchranke(double Schranke);
	Begrenzung eGetLimit() const;

	bool bKeineFahrzeuge() const;
	virtual void vAbfertigung();
	virtual std::ostream& ostreamAusgabe(std::ostream& Out) const;
};

