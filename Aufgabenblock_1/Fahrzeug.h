#pragma once
#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>

using namespace std;

extern double dGlobaleZeit;

class Fahrzeug
{
private:
	static int p_iMaxID;
	int p_iID;
	std::string p_sName;

	void vInitialisierung();

protected:
	double p_dMopsGeschwindigkeit;
	double p_dGesamtStrecke;
	double p_dGesamtZeit;
	double p_dZeit;

public:
	Fahrzeug();
	Fahrzeug(const Fahrzeug& Obj);
	Fahrzeug(const std::string sName);
	Fahrzeug(const std::string sName, double dMaxGeschwindigkeit);
	~Fahrzeug();

	virtual void vAusgabe() const;
	virtual void vAbfertigung();
	virtual double dTanken(double dMenge = 0) const;
	virtual double dGeschwindigkeit() const;
	virtual std::ostream& ostreamAusgabe(std::ostream& Out) const;

	bool operator<(const Fahrzeug& Other);
	Fahrzeug& operator=(const Fahrzeug& Rhs);
};

std::ostream& operator<<(std::ostream& Out, Fahrzeug& Obj);
std::string vCentered(std::string const& sOriginal, int iTargetSize);