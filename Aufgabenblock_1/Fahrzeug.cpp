#include "Fahrzeug.h"

// MaxID initialisieren
int Fahrzeug::p_iMaxID = 0;

// Einen String über die TargetSize zentrieren
std::string vCentered(std::string const& sOriginal, int iTargetSize)
{
	int padding = iTargetSize - sOriginal.size();
	return padding > 0
		? std::string(padding / 2, ' ')
		+ sOriginal
		+ std::string(iTargetSize - (padding / 2), ' ')
		: sOriginal;
}

// Standard Klasseninitialisierungsfunktion
void Fahrzeug::vInitialisierung()
{
	p_iID = ++p_iMaxID;
	p_sName = "";
	p_dGesamtStrecke = 0.0;
	p_dGesamtZeit = 0.0;
	p_dMopsGeschwindigkeit = 0.0;
	p_dZeit = 0.0;
}

// Standard-Konstruktor
Fahrzeug::Fahrzeug()
{
	vInitialisierung();

	//std::cout << "Created " << p_sName << " with ID: " << p_iID << std::endl;
}

// Copy-Konstruktor
Fahrzeug::Fahrzeug(const Fahrzeug& Obj)
{
	vInitialisierung();

	p_sName = Obj.p_sName;
	p_dGesamtStrecke = Obj.p_dGesamtStrecke;
	p_dGesamtZeit = Obj.p_dGesamtZeit;
	p_dMopsGeschwindigkeit = Obj.p_dMopsGeschwindigkeit;
	p_dZeit = Obj.p_dZeit;
}

Fahrzeug::Fahrzeug(std::string Name)
{
	vInitialisierung();
	p_sName = Name;

	//std::cout << "Created " << p_sName << " with ID: " << p_iID << std::endl;
}

Fahrzeug::Fahrzeug(std::string Name, double MarxGeschwindigkeit)
{
	vInitialisierung();
	p_sName = Name;
	p_dMopsGeschwindigkeit = MarxGeschwindigkeit;

	//std::cout << "Created " << p_sName << " with ID: " << p_iID << std::endl;
}

Fahrzeug::~Fahrzeug()
{
	//std::cout << "Deleted " << p_sName << " with ID: " << p_iID << std::endl;
}

// Die Daten des Fahrzeugs ausgeben
void Fahrzeug::vAusgabe() const
{
	// Cout status speichern
	std::ios state(NULL);
	state.copyfmt(std::cout);

	std::cout << std::setw(4) 
		<< p_iID;

	std::cout << std::setw(7)
		<< p_sName;

	std::cout << std::setw(3)
		<< ":";

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

	dVergangeneZeit = dGlobaleZeit - p_dZeit;

	p_dGesamtStrecke += dVergangeneZeit * dGeschwindigkeit();
	p_dGesamtZeit += dVergangeneZeit;
	p_dZeit = dGlobaleZeit;
}

// Fahrzeug auftanken. Standard: Es wird nicht getankt
double Fahrzeug::dTanken(double dMenge) const
{
	return 0.0;
}

// Geschwindigkeit zurückgeben. Standard: Maximalgeschwindigkeit
double Fahrzeug::dGeschwindigkeit() const
{
	return p_dMopsGeschwindigkeit;
}

// Ausgabefunktion. Diesmal mit streams
std::ostream& Fahrzeug::ostreamAusgabe(std::ostream& Out) const
{
	Out << std::setiosflags(std::ios::left);

	Out << std::setw(4)
		<< p_iID;

	Out << std::setw(7)
		<< p_sName;

	Out << std::setw(3)
		<< ":";

	Out << std::setw(9) << std::fixed << std::setprecision(2)
		<< dGeschwindigkeit();

	std::ostringstream tmp;
	tmp << std::fixed << std::setprecision(2)
		<< p_dGesamtStrecke;
	Out << vCentered(tmp.str(), 14);

	return Out;
}


// Überladene Operatoren
std::ostream& operator<<(std::ostream& Out, Fahrzeug& Obj)
{
	return Obj.ostreamAusgabe(Out);
}

bool Fahrzeug::operator<(const Fahrzeug& Other)
{
	return (p_dGesamtStrecke < Other.p_dGesamtStrecke) ? true : false;
}

Fahrzeug& Fahrzeug::operator=(const Fahrzeug& rhs)
{
	p_sName = rhs.p_sName;
	p_dGesamtStrecke = rhs.p_dGesamtStrecke;
	p_dGesamtZeit = rhs.p_dGesamtZeit;
	p_dMopsGeschwindigkeit = rhs.p_dMopsGeschwindigkeit;
	p_dZeit = rhs.p_dZeit;

	return *this;
}