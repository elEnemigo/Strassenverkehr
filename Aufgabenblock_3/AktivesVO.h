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
	static AktivesVO* ptObjekt(std::string sName);

	virtual void vAusgabe() const;
	virtual void vAbfertigung() = 0;
	virtual std::ostream& ostreamAusgabe(std::ostream& Out) const;
	virtual std::istream& istreamEingabe(std::istream& In);

	AktivesVO& operator= (AktivesVO& Rhs);
};

std::string vCentered(std::string const& sOriginal, int iTargetSize);
std::ostream& operator<<(std::ostream& Out, AktivesVO& Obj);
std::istream& operator>> (std::istream& In, AktivesVO& Obj);