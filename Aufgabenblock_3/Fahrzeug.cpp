#include "Fahrzeug.h"
#include "Weg.h"
#include "FzgVerhalten.h"
#include "FzgFahren.h"
#include "FzgParken.h"
#include "SimuClient.h"

// Standard Klasseninitialisierungsfunktion
void Fahrzeug::vInitialisierung()
{
	p_dGesamtStrecke = 0.0;
	p_dAbschnittStrecke = 0.0;
	p_dMopsGeschwindigkeit = 0.0;
	p_pVerhalten = nullptr;
}

// Standard-Konstruktor
Fahrzeug::Fahrzeug()
{
	vInitialisierung();

	//std::cout << "Created " << p_sName << " with ID: " << p_iID << std::endl;
}

// Copy-Konstruktor
Fahrzeug::Fahrzeug(const Fahrzeug& Obj) :
	AktivesVO(Obj)
{
	vInitialisierung();

	p_dGesamtStrecke = Obj.p_dGesamtStrecke;
	p_dMopsGeschwindigkeit = Obj.p_dMopsGeschwindigkeit;
}

Fahrzeug::Fahrzeug(std::string Name) :
	AktivesVO(Name)
{
	vInitialisierung();

	//std::cout << "Created " << p_sName << " with ID: " << p_iID << std::endl;
}

Fahrzeug::Fahrzeug(std::string Name, double MarxGeschwindigkeit) :
	AktivesVO(Name)
{
	vInitialisierung();

	p_dMopsGeschwindigkeit = MarxGeschwindigkeit;

	//std::cout << "Created " << p_sName << " with ID: " << p_iID << std::endl;
}

Fahrzeug::~Fahrzeug()
{
	//std::cout << "Deleted " << p_sName << " with ID: " << p_iID << std::endl;
}

// Fahrzeug zum Weg hinzufügen
void Fahrzeug::vNeueStrecke(Weg* pWeg)
{
	if (p_pVerhalten)
		delete p_pVerhalten;
	p_dAbschnittStrecke = 0.0;

	p_pVerhalten = new FzgFahren(pWeg);
	pWeg->vAnnahme(this);
}

// Fahrzeug zum Weg hinzufügen, jedoch erst nach dStartZeit losfahren lassen
void Fahrzeug::vNeueStrecke(Weg* pWeg, double dStartzeit)
{
	if (dStartzeit <= (0.0 + DBL_EPSILON))
		return vNeueStrecke(pWeg);

	if (p_pVerhalten)
		delete p_pVerhalten;
	p_dAbschnittStrecke = 0.0;

	p_pVerhalten = new FzgParken(pWeg, dStartzeit);
	pWeg->vAnnahme(this, dStartzeit);
}

// Auf dem Weg hinterlegte Strecke
double Fahrzeug::dGetAbschnittStrecke() const
{
	return p_dAbschnittStrecke;
}

// Die Daten des Fahrzeugs ausgeben
void Fahrzeug::vAusgabe() const
{
	// Cout status speichern
	std::ios state(NULL);
	state.copyfmt(std::cout);

	AktivesVO::vAusgabe();

	std::cout << std::setw(9) << std::fixed << std::setprecision(2) 
		<< dGeschwindigkeit();

	std::ostringstream out;
	out << std::fixed << std::setprecision(2) 
		<< p_dGesamtStrecke;
	std::cout << vCentered(out.str(), 14);

	// Cout status wiederherstellen
	std::cout.copyfmt(state);
}

// Fahrzeug nach neuem Zeitschritt abfertigen
void Fahrzeug::vAbfertigung()
{
	double dVergangeneZeit;
	double dRestStrecke;


	if (!p_pVerhalten)
		return;

	if (p_pVerhalten->pGetWeg()->dGetLaenge() <= p_dAbschnittStrecke)
		throw Streckenende(this, p_pVerhalten->pGetWeg());//exit(1);

	dVergangeneZeit = dGlobaleZeit - p_dZeit;
	dRestStrecke = p_pVerhalten->dStrecke(this, dVergangeneZeit);

	//if (dRestStrecke == 0 && dVergangeneZeit > 0)
	//	exit(1);

	p_dGesamtStrecke += dRestStrecke; // dVergangeneZeit * dGeschwindigkeit();
	p_dAbschnittStrecke += dRestStrecke;
	p_dGesamtZeit += dVergangeneZeit;
	p_dZeit = dGlobaleZeit;
}

void Fahrzeug::vZeichnen(const Weg* pWeg) const
{
	bZeichnePKW(sGetName(), pWeg->sGetName(), p_dAbschnittStrecke / pWeg->dGetLaenge(), dGeschwindigkeit(), std::fmax(0.0, dGetTankinhalt()));
}

// Fahrzeug auftanken. Standard: Es wird nicht getankt
double Fahrzeug::dTanken(double dMenge)
{
	return 0.0;
}

// Geschwindigkeit zurückgeben. Standard: Maximalgeschwindigkeit
double Fahrzeug::dGeschwindigkeit() const
{
	return p_dMopsGeschwindigkeit;
}

double Fahrzeug::dGetTankinhalt() const
{
	return -1.0;
}

// Ausgabefunktion. Diesmal mit streams
std::ostream& Fahrzeug::ostreamAusgabe(std::ostream& Out) const
{
	AktivesVO::ostreamAusgabe(Out);

	Out << std::setw(9) << std::fixed << std::setprecision(2)
		<< dGeschwindigkeit();

	std::ostringstream tmp;
	tmp << std::fixed << std::setprecision(2)
		<< p_dGesamtStrecke;
	Out << vCentered(tmp.str(), 14);

	return Out;
}

std::istream& Fahrzeug::istreamEingabe(std::istream& In)
{
	AktivesVO::istreamEingabe(In);

	if (In.peek() == '\n')
		throw std::string("Zu wenige Argumente für Fahrzeug");
	In >> p_dMopsGeschwindigkeit;

	//std::string tmp;
	//std::smatch m;
	//std::regex e("\\b[\\d]+\\b");
	//std::getline(In, tmp);
	//if (std::regex_search(tmp, m, e))
	//{
	//	std::smatch::iterator it = m.begin();
	//	p_dMopsGeschwindigkeit = std::stod((*it));
	//}

	return In;
}


// Überladene Operatoren
bool Fahrzeug::operator<(const Fahrzeug& Other)
{
	return (p_dGesamtStrecke < Other.p_dGesamtStrecke) ? true : false;
}

Fahrzeug& Fahrzeug::operator=(const Fahrzeug& rhs)
{
	AktivesVO::operator=((AktivesVO&)rhs);
	p_dGesamtStrecke = rhs.p_dGesamtStrecke;
	p_dMopsGeschwindigkeit = rhs.p_dMopsGeschwindigkeit;

	return *this;
}