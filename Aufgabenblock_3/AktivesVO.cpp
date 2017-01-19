#include "AktivesVO.h"

// Static members initialisieren
int AktivesVO::p_iMaxID = 0;
std::map<std::string, AktivesVO*> AktivesVO::p_mObjekte = {};

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

	std::pair<std::map<std::string, AktivesVO*>::const_iterator, bool> it;
	it = p_mObjekte.insert(std::pair<std::string, AktivesVO*>(sName, this));
	if (!it.second)
		throw std::string("Key existiert bereits!");
}

AktivesVO::~AktivesVO()
{
	std::map<std::string, AktivesVO*>::const_iterator it;

	it = p_mObjekte.find(p_sName);
	p_mObjekte.erase(it->first);
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

AktivesVO* AktivesVO::ptObjekt(std::string sName)
{
	std::map<std::string, AktivesVO*>::const_iterator it;

	it = p_mObjekte.find(sName);

	if (it != p_mObjekte.end())
		return it->second;
	
	throw std::string("Key exisitiert nicht!");
	return nullptr;
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

std::istream& AktivesVO::istreamEingabe(std::istream& In)
{
	if (!p_sName.empty())
		throw "AAAH";
	else
	{
		In >> p_sName;
		std::pair<std::map<std::string, AktivesVO*>::const_iterator, bool> it;
		it = p_mObjekte.insert(std::pair<std::string, AktivesVO*>(p_sName, this));
		if (!it.second)
			throw std::string("Key existiert bereits!");

		//std::string tmp;
		//std::smatch m;
		//std::regex e("\\b\\w+\\b");
		//std::getline(In, tmp);
		//if (std::regex_search(tmp, m, e))
		//{
		//	std::smatch::iterator it = m.begin();
		//	p_sName = (*it);
		//}
	}

	return In;
}

// Überladene Operatoren
std::ostream& operator<<(std::ostream& Out, AktivesVO& Obj)
{
	return Obj.ostreamAusgabe(Out);
}

std::istream& operator>>(std::istream& In, AktivesVO& Obj)
{
	return Obj.istreamEingabe(In);
}

AktivesVO& AktivesVO::operator=(AktivesVO& Rhs)
{
	p_sName = Rhs.p_sName;
	p_dGesamtZeit = Rhs.p_dGesamtZeit;
	p_dZeit = Rhs.p_dZeit;

	return *this;
}