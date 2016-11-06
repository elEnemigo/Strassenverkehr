#include "PKW.h"


// Standardkonstruktor
// Verbrauch: 10l/100km
// Tankvolumen: 55l
// Tankinhalt: Halb voll
PKW::PKW() :
	p_dVerbrauch(10.0), p_dTankvolumen(55), p_dTankinhalt(p_dTankvolumen / 2.0)
{
	
}

// Konstruktor von Fahrzeug aufrufen
PKW::PKW(std::string sName, double dMordsGeschwindigkeit, double dVerbrauch, double dTankvolumen)
	: Fahrzeug(sName, dMordsGeschwindigkeit), p_dVerbrauch(dVerbrauch), p_dTankvolumen(dTankvolumen), p_dTankinhalt(dTankvolumen / 2.0)
{

}

PKW::~PKW()
{
}

// Spezialisierte Ausgabe f�r Klasse PKW
void PKW::vAusgabe() const
{
	// Vorerst Standard-Ausgabefunktion aufrufen
	Fahrzeug::vAusgabe();

	// Status speichern
	std::ios state(NULL);
	state.copyfmt(std::cout);

	// Zwei extra Spalten ausgeben f�r den Gesamtverbrauch und aktuellen Tankinhalt
	std::cout << std::setw(9) << std::fixed << std::setprecision(2)
		<< p_dVerbrauch * (p_dGesamtStrecke / 100.0);

	std::cout << std::setw(6) << std::fixed << std::setprecision(2)
		<< p_dTankinhalt;

	// Status wiederherstellen
	std::cout.copyfmt(state);
}

// Spezialisierte Abfertigungsfunktion f�r Klasse PKW
void PKW::vAbfertigung()
{
	double dHinterlegteStrecke = p_dGesamtStrecke;

	// Wenn Tank nicht leer -> Standard-Abfertigungsfunktion aufrufen, sonst nichts tun
	if (p_dTankinhalt > 0.0)
		Fahrzeug::vAbfertigung();
	else
		return;

	// Wie weit wir in diesem Schritt gefahren sind
	dHinterlegteStrecke = p_dGesamtStrecke - dHinterlegteStrecke;

	// Tankinhalt entsprechend reduzieren, mindestens jedoch auf 0 setzen
	p_dTankinhalt = std::fmax(p_dTankinhalt - ((dHinterlegteStrecke / 100.0) * p_dVerbrauch), 0.0);
}

// PKW um angegebene Menge Tanken
double PKW::dTanken(double dMenge)
{
	double dVorhInhalt = p_dTankinhalt;

	if (dMenge == 0)	// Wenn 0 -> volltanken
		p_dTankinhalt = p_dTankvolumen;
	else                // Sonst um angebene Menge tanken, max jedoch auf Tankvolumen
		p_dTankinhalt = std::fmin(p_dTankinhalt + dMenge, p_dTankvolumen);

	// Getankte Menge zur�ckgeben
	return p_dTankinhalt - dVorhInhalt;
}

// Aktuelle Geschwindigkeit
double PKW::dGeschwindigkeit() const
{
	return Fahrzeug::dGeschwindigkeit(); // MaxGeschwindigkeit
}

// Aktueller Gesamtverbrauch
double PKW::dVerbrauch() const
{
	return p_dVerbrauch * (p_dGesamtStrecke / 100.0);
}

// Ausgabefunktion. Diesmal mit streams
std::ostream& PKW::ostreamAusgabe(std::ostream& Out) const
{
	Fahrzeug::ostreamAusgabe(Out);

	std::ostringstream tmp;
	tmp << std::fixed << std::setprecision(2)
		<< p_dVerbrauch * (p_dGesamtStrecke / 100.0);
	Out << vCentered(tmp.str(), 6);

	tmp.str("");
	tmp.clear();
	tmp << std::fixed << std::setprecision(2)
		<< p_dTankinhalt;
	Out << vCentered(tmp.str(), 10);

	return Out;
}