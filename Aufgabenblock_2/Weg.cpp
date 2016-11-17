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
		p_pFahrzeuge.push_front(pFahrzeug);
}

void Weg::vAbgabe(Fahrzeug* pFahrzeug)
{
	//p_pFahrzeuge.erase(std::remove(p_pFahrzeuge.begin(), p_pFahrzeuge.end(), pFahrzeug));
	//p_pFahrzeuge.remove(pFahrzeug);

	LazyListe<Fahrzeug*>::iterator it;
	for (it = p_pFahrzeuge.begin(); it != p_pFahrzeuge.end(); it++)
		if ((*it) == pFahrzeug)
		{
			p_pFahrzeuge.erase(it);
			break;
		}
}

void Weg::vAbfertigung()
{
	//std::list<Fahrzeug*>::iterator it = p_pFahrzeuge.begin();
	//bool bCaught;

	////for (Fahrzeug* i : p_pFahrzeuge)
	//while (it != p_pFahrzeuge.end())
	//{
	//	bCaught = false;

	//	try {
	//		(*it)->vAbfertigung();
	//	} catch (Fahrausnahme& aExc) {
	//		it++;
	//		aExc.vBearbeiten();
	//		if (p_pFahrzeuge.size() < 2)
	//			break;
	//		bCaught = true;
	//	}

	//	if (!bCaught)
	//		it++;
	//}
	p_pFahrzeuge.vAktualisieren();

	LazyListe<Fahrzeug*>::const_iterator it;

	for (it = p_pFahrzeuge.begin(); it != p_pFahrzeuge.end(); it++)
	{
		try {
			(*it)->vAbfertigung();
		}
		catch (Fahrausnahme& aExc) {
			aExc.vBearbeiten();
		}
	}

	p_pFahrzeuge.vAktualisieren();
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