#include "Welt.h"
#include "AktivesVO.h"
#include "Kreuzung.h"
#include "PKW.h"
#include "Fahrrad.h"
#include "SimuClient.h"

// Hilfsfunktion
void CheckInput(std::istream& In, bool Last = false)
{
	if (In.fail() && !In.eof())
		throw std::string("Falscher Datentyp!");

	if (!Last && (In.peek() == '\n'))
		throw std::string("Fehlende Argumente!");

	if (Last && (In.peek() != '\n'))
		throw std::string("Zu viele Argumente!");
}

Welt::Welt() :
	p_bGrafik(false)
{
	dGlobaleZeit = 0.0;
}

Welt::~Welt()
{
	if (p_bGrafik)
		vBeendeGrafik();

	for (Kreuzung* pK : p_pKreuzungen)
		if (pK)
			delete pK;
	p_pKreuzungen.clear();
	for (Fahrzeug* pP : p_pFahrzeuge)
		if (pP)
			delete pP;
	p_pFahrzeuge.clear();
}

void Welt::vEinlesen(std::istream& In)
{
	std::string sType;

	while (In >> sType)
	{
		if (sType == "KREUZUNG")
		{
			Kreuzung* pK = new Kreuzung;

			In >> *pK; CheckInput(In, true);

			p_pKreuzungen.push_back(pK);
		}
		else if (sType == "STRASSE")
		{
			Kreuzung *pQuellK, *pZielK;
			std::string sQuellK, sZielK;
			std::string sHinW, sRuckW;
			double dLang, dGeschwind;
			bool bUeberhol;
			Begrenzung Lim;

			In >> sQuellK; CheckInput(In);
			In >> sZielK; CheckInput(In);
			In >> sHinW; CheckInput(In);
			In >> sRuckW; CheckInput(In);
			In >> dLang; CheckInput(In);
			In >> dGeschwind; CheckInput(In);
			In >> bUeberhol; CheckInput(In, true);

			pQuellK = AktivesVO::ptObjekt<Kreuzung*>(sQuellK);
			pZielK = AktivesVO::ptObjekt<Kreuzung*>(sZielK);
			Lim = dGeschwind == 1 ? Innerorts : (dGeschwind == 2 ? Land : Autobahn);
			pQuellK->vVerbinde(sHinW, sRuckW, pZielK, dLang, Lim, bUeberhol);
		}
		else if (sType == "PKW")
		{
			PKW* pP = new PKW;
			Kreuzung* pStart;
			std::string sStart;
			double dStart;

			In >> *pP; CheckInput(In);
			In >> sStart; CheckInput(In);
			In >> dStart; CheckInput(In, true);

			pStart = AktivesVO::ptObjekt<Kreuzung*>(sStart);

			pStart->vAnnahme(pP, dStart);

			p_pFahrzeuge.push_back(pP);
		}
		else if (sType == "FAHRRAD")
		{
			Fahrrad* pP = new Fahrrad;
			Kreuzung* pStart;
			std::string sStart;
			double dStart;

			In >> *pP; CheckInput(In);
			In >> sStart; CheckInput(In);
			In >> dStart; CheckInput(In, true);

			pStart = AktivesVO::ptObjekt<Kreuzung*>(sStart);

			pStart->vAnnahme(pP, dStart);

			p_pFahrzeuge.push_back(pP);
		}
		else
		{
			throw std::string("Fehler beim Einlesen!");
		}
	}
}

void Welt::vEinlesenMitGrafik(std::istream& In)
{
	p_bGrafik = true;
	bInitialisiereGrafik(1920, 1080);

	std::string sType;

	while (In >> sType)
	{
		if (sType == "KREUZUNG")
		{
			Kreuzung* pK = new Kreuzung;

			In >> *pK;
			p_pKreuzungen.push_back(pK);

			// Zeichnen
			int xpos, ypos;
			In >> xpos >> ypos;
			bZeichneKreuzung(xpos, ypos);
		}
		else if (sType == "STRASSE")
		{
			Kreuzung *pQuellK, *pZielK;
			std::string sQuellK, sZielK;
			std::string sHinW, sRuckW;
			double dLang, dGeschwind;
			bool bUeberhol;
			Begrenzung Lim;

			In >> sQuellK >> sZielK >> sHinW >> sRuckW >> dLang >> dGeschwind >> bUeberhol;

			pQuellK = AktivesVO::ptObjekt<Kreuzung*>(sQuellK);
			pZielK = AktivesVO::ptObjekt<Kreuzung*>(sZielK);
			Lim = dGeschwind == 1 ? Innerorts : (dGeschwind == 2 ? Land : Autobahn);
			pQuellK->vVerbinde(sHinW, sRuckW, pZielK, dLang, Lim, bUeberhol);

			// Zeichnen
			int Size;
			In >> Size;
			Size *= 2;
			int P;
			int arr[256];
			int i = 0;
			while (In.peek() != '\n' && (In >> P) && (i < 256))
				arr[i++] = P;

			bZeichneStrasse(sHinW, sRuckW, dLang, i / 2, arr);
		}
		else if (sType == "PKW")
		{
			PKW* pP = new PKW;
			Kreuzung* pStart;
			std::string sStart;
			double dStart;

			In >> *pP;
			In >> sStart;
			In >> dStart;

			pStart = AktivesVO::ptObjekt<Kreuzung*>(sStart);

			pStart->vAnnahme(pP, dStart);

			p_pFahrzeuge.push_back(pP);
		}
		else if (sType == "FAHRRAD")
		{
			Fahrrad* pP = new Fahrrad;
			Kreuzung* pStart;
			std::string sStart;
			double dStart;

			In >> *pP;
			In >> sStart;
			In >> dStart;

			pStart = AktivesVO::ptObjekt<Kreuzung*>(sStart);

			pStart->vAnnahme(pP, dStart);

			p_pFahrzeuge.push_back(pP);
		}
		else
		{
			throw std::string("Fehler beim Einlesen!");
		}
	}
}

void Welt::vSimulation(double dT)
{
	dGlobaleZeit += dT;

	if (!p_bGrafik)
		std::cout << "						T = " << dGlobaleZeit << std::endl;

	for (Kreuzung* pK : p_pKreuzungen)
	{
		if (p_bGrafik)
			vSetzeZeit(dGlobaleZeit);

		pK->vAbfertigung();

		if (!p_bGrafik)
			std::cout << pK->sGetName() << *pK << std::endl;

		if (p_bGrafik)
		{
			pK->vZeichne();
			vSleep(dT * 1000.0);
		}
	}
}