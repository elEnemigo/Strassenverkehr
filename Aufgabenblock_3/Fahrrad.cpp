#include "Fahrrad.h"
#include "Weg.h"
#include "SimuClient.h"

// Standardkonstruktor
Fahrrad::Fahrrad()
{
}

// Expliziter Konstruktoraufruf von Fahrzeug
Fahrrad::Fahrrad(std::string Name, double dGeschwind) :
	Fahrzeug(Name, dGeschwind)
{

}

Fahrrad::~Fahrrad()
{
}

void Fahrrad::vZeichnen(Weg* pWeg) const
{
	bZeichneFahrrad(sGetName(), pWeg->sGetName(), p_dAbschnittStrecke / pWeg->dGetLaenge(), dGeschwindigkeit());
}

// Geschwindigkeit abhängend von der gefahrenen Strecke berechnen
double Fahrrad::dGeschwindigkeit() const
{
	// v = v_max * e^(-0.1 * floor(s / 20)) oder 12
	return std::fmax(p_dMopsGeschwindigkeit * std::exp(-0.1 * (std::floor(p_dGesamtStrecke / 20.0))), 12.0);
}