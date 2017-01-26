#pragma once
#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <map>

#define EPS 0.000001

extern double dGlobaleZeit;

class AktivesVO
{
private:
	static int p_iMaxID;
	static std::map<std::string, AktivesVO*> p_mObjekte;
	int p_iID;
	std::string p_sName;

protected:
	double p_dGesamtZeit;
	double p_dZeit;

	virtual void vInitialisierung();

public:
	AktivesVO();
	AktivesVO(const AktivesVO& Obj);
	AktivesVO(std::string sName);
	~AktivesVO();

	std::string sGetName() const;
	template <class T>
	static T ptObjekt(std::string sName);

	virtual void vAusgabe() const;
	virtual void vAbfertigung() = 0;
	virtual std::ostream& ostreamAusgabe(std::ostream& Out) const;
	virtual std::istream& istreamEingabe(std::istream& In);

	AktivesVO& operator= (AktivesVO& Rhs);
};

std::string vCentered(std::string const& sOriginal, int iTargetSize);
std::ostream& operator<<(std::ostream& Out, AktivesVO& Obj);
std::istream& operator>> (std::istream& In, AktivesVO& Obj);


template <class T>
static T AktivesVO::ptObjekt(std::string sName)
{
	std::map<std::string, AktivesVO*>::const_iterator it;

	it = p_mObjekte.find(sName);

	if (it != p_mObjekte.end())
		return dynamic_cast<T>(it->second);

	throw std::string("Key '" + sName + "' exisitiert nicht!");
	return nullptr;
}