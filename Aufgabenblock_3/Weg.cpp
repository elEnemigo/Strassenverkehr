#include "Weg.h"
#include "Fahrzeug.h"

Weg::Weg()
{
	vInitialisierung();
}

Weg::Weg(std::string sName, double dLaenge, Begrenzung eLimit, bool bUeberholverbot) :
	AktivesVO(sName)
{
	vInitialisierung();

	p_dLaenge = dLaenge;
	p_eLimit = eLimit;
	p_bUeberholverbot = bUeberholverbot;
}

Weg::~Weg()
{
}

void Weg::vInitialisierung()
{
	p_dLaenge = 0.0;
	p_eLimit = Autobahn;
}

// Fahrzeug zum Weg hinzufügen
void Weg::vAnnahme(Fahrzeug* pFahrzeug)
{
	if (pFahrzeug)
		p_pFahrzeuge.push_front(pFahrzeug);
}

// Fahrzeug zum Weg hinzufügen, jedoch erst nach dStartZeit losfahren lassen
void Weg::vAnnahme(Fahrzeug* pFahrzeug, double dStartZeit)
{
	if (pFahrzeug)
		p_pFahrzeuge.push_back(pFahrzeug);
}

// Fahrzeug vom Weg entfernen
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

bool Weg::bKeineFahrzeuge() const
{
	return p_pFahrzeuge.empty();
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

	p_dVirtuelleSchranke = p_dLaenge;
	for (it = p_pFahrzeuge.begin(); it != p_pFahrzeuge.end(); it++)
	{
		try {
			(*it)->vAbfertigung();
			p_dVirtuelleSchranke = (*it)->dGetAbschnittStrecke();
		}
		catch (Fahrausnahme& aExc) {
			aExc.vBearbeiten();
		}
	}

	p_pFahrzeuge.vAktualisieren();

	// Fahrzeuge nach abgefahrener Strecke sortieren (weitester vorn)
	p_pFahrzeuge.sort([](Fahrzeug* i, Fahrzeug* j) {
		return (i->dGetAbschnittStrecke() > j->dGetAbschnittStrecke());
	});
}

double Weg::dGetLaenge() const
{
	return p_dLaenge;
}

double Weg::dGetVirtuelleSchranke() const
{
	return p_bUeberholverbot ? p_dVirtuelleSchranke : dGetLaenge();
}

void Weg::dSetVirtuelleSchranke(double Schranke)
{
	p_dVirtuelleSchranke = Schranke;
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