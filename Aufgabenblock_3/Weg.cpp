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
	p_bUeberholverbot = true;
	p_pRueckweg = nullptr;
	p_pNaechsteKreuzung = nullptr;
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

	// Fahrzeuge nach abgefahrener Strecke sortieren (weitester vorn)
	p_pFahrzeuge.sort([](Fahrzeug* i, Fahrzeug* j) {
		return (i->dGetAbschnittStrecke() > j->dGetAbschnittStrecke());
	});

	p_dVirtuelleSchranke = p_dLaenge;
	for (it = p_pFahrzeuge.begin(); it != p_pFahrzeuge.end(); it++)
	{
		try {
			(*it)->vAbfertigung();
			if ((*it)->dGetTankinhalt() > 0.0 || (*it)->dGetTankinhalt() < 0.0)
				p_dVirtuelleSchranke = (*it)->dGetAbschnittStrecke();
		}
		catch (Fahrausnahme& aExc) {
			aExc.vBearbeiten();
		}
	}

	p_pFahrzeuge.vAktualisieren();
}

void Weg::vZeichne() const
{
	for (Fahrzeug* F : p_pFahrzeuge)
		F->vZeichnen(this);
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

void Weg::vSetRueckweg(Weg* pWeg)
{
	p_pRueckweg = pWeg;
}

void Weg::vSetNaechsteKreuzung(Kreuzung* pKreuzung)
{
	p_pNaechsteKreuzung = pKreuzung;
}

Begrenzung Weg::eGetLimit() const
{
	return p_eLimit;
}

Weg* Weg::pGetRueckweg() const
{
	return p_pRueckweg;
}

Kreuzung* Weg::pGetNaechsteKreuzung() const
{
	return p_pNaechsteKreuzung;
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

std::istream& Weg::istreamEingabe(std::istream& In)
{
	double Lim;
	AktivesVO::istreamEingabe(In);

	In >> p_dLaenge;
	In >> Lim;
	p_eLimit = Lim == 1 ? Innerorts : (Lim == 2 ? Land : Autobahn);
	In >> p_bUeberholverbot;

	return In;
}