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
	Begrenzung p_eLimit;
	//std::list<Fahrzeug*> p_pFahrzeuge;	// Pointer, da es viel effizienter ist einen Pointer in der Liste zu �ndern als ein Objekt zu l�schen und eine Kopie davon in einer neuen Liste zu speichern.
	LazyListe<Fahrzeug*> p_pFahrzeuge;

	void vInitialisierung();
public:
	Weg();
	Weg(std::string sName, double dLaenge, Begrenzung eLimit = Autobahn);
	~Weg();

	void vAnnahme(Fahrzeug* pFahrzeug);
	void vAnnahme(Fahrzeug* pFahrzeug, double dStartZeit);
	void vAbgabe(Fahrzeug* pFahrzeug);
	double dGetLaenge() const;
	Begrenzung eGetLimit() const;

	virtual void vAbfertigung();
	virtual std::ostream& ostreamAusgabe(std::ostream& Out) const;
};

