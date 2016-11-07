#include "Weg.h"
#include "Fahrzeug.h"


Weg::Weg()
{
	vInitialisierung();
}

Weg::Weg(std::string sName, double dLaenge, Begrenzung eLimit) :
	AktivesVO(sName)
{
	vInitialisierung();

	p_dLaenge = dLaenge;
	p_eLimit = eLimit;
}

Weg::~Weg()
{
}

void Weg::vInitialisierung()
{
	p_dLaenge = 0.0;
	p_eLimit = Autobahn;
}

void Weg::vAnnahme(Fahrzeug* pFahrzeug)
{
	if (pFahrzeug)
		p_pFahrzeuge.push_back(pFahrzeug);
}

void Weg::vAnnahme(Fahrzeug* pFahrzeug, double dStartZeit)
{
	if (pFahrzeug)
		p_pFahrzeuge.push_back(pFahrzeug);
}

void Weg::vAbfertigung()
{
	for (Fahrzeug* i : p_pFahrzeuge)
		i->vAbfertigung();
}

double Weg::dGetLaenge() const
{
	return p_dLaenge;
}

Begrenzung Weg::eGetLimit() const
{
	return p_eLimit;
}

std::ostream& Weg::ostreamAusgabe(std::ostream& Out) const
{
	AktivesVO::ostreamAusgabe(Out);

	Out << std::setw(6)
		<< p_dLaenge;

	Out << " ( ";
	for (Fahrzeug* F : p_pFahrzeuge)
		Out << F->sGetName() << " ";
	Out << ")";

	return Out;
}