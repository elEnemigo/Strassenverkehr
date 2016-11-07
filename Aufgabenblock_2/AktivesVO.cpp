#include "AktivesVO.h"

// MaxID initialisieren
int AktivesVO::p_iMaxID = 0;


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

AktivesVO::AktivesVO()
{
	vInitialisierung();
}

AktivesVO::AktivesVO(const AktivesVO& Obj)
{
	vInitialisierung();
	p_sName = Obj.p_sName;
	p_dGesamtZeit = Obj.p_dGesamtZeit;
	p_dZeit = Obj.p_dZeit;
}

AktivesVO::AktivesVO(std::string sName)
{
	vInitialisierung();
	p_sName = sName;
}

AktivesVO::~AktivesVO()
{
}

void AktivesVO::vInitialisierung()
{
	p_iID = ++p_iMaxID;
	p_sName = "";
	p_dGesamtZeit = 0.0;
	p_dZeit = 0.0;
}

std::string AktivesVO::sGetName() const
{
	return p_sName;
}

void AktivesVO::vAusgabe() const
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

	// Cout status wiederherstellen
	std::cout.copyfmt(state);
}

std::ostream& AktivesVO::ostreamAusgabe(std::ostream& Out) const
{
	Out << std::setiosflags(std::ios::left);

	Out << std::setw(4)
		<< p_iID;

	Out << std::setw(7)
		<< p_sName;

	Out << std::setw(3)
		<< ":";

	return Out;
}

// Überladene Operatoren
std::ostream& operator<<(std::ostream& Out, AktivesVO& Obj)
{
	return Obj.ostreamAusgabe(Out);
}

AktivesVO& AktivesVO::operator=(AktivesVO& Rhs)
{
	p_sName = Rhs.p_sName;
	p_dGesamtZeit = Rhs.p_dGesamtZeit;
	p_dZeit = Rhs.p_dZeit;

	return *this;
}