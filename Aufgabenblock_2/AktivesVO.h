#pragma once
#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>

class AktivesVO
{
private:
	static int p_iMaxID;
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

	virtual void vAusgabe() const;
	virtual void vAbfertigung() = 0;
	virtual std::ostream& ostreamAusgabe(std::ostream& Out) const;

	AktivesVO& operator= (AktivesVO& Rhs);
};

std::string vCentered(std::string const& sOriginal, int iTargetSize);
std::ostream& operator<<(std::ostream& Out, AktivesVO& Obj);