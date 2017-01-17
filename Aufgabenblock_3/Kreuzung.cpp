#include "Kreuzung.h"
#include "Weg.h"
#include "Fahrzeug.h"
#include <random>

Kreuzung::Kreuzung()
{
}

Kreuzung::Kreuzung(std::string sName) :
	AktivesVO(sName)
{

}

Kreuzung::~Kreuzung()
{
	for (Weg* W : p_pWege)
		delete W;
	p_pWege.clear();
}

void Kreuzung::vVerbinde(std::string WegHin, std::string WegZruck, Kreuzung* pGegenKreuzung, double dWegLaenge, Begrenzung eLimit, bool bUeberholverbot)
{
	Weg* Hin, *Zuruck;

	Hin = new Weg(WegHin, dWegLaenge, eLimit, bUeberholverbot);
	Zuruck = new Weg(WegZruck, dWegLaenge, eLimit, bUeberholverbot);
	Hin->vSetRueckweg(Zuruck);
	Hin->vSetNaechsteKreuzung(pGegenKreuzung);

	pGegenKreuzung->vVerbinde(Zuruck, Hin, this);

	p_pWege.push_back(Hin);
}

void Kreuzung::vVerbinde(Weg* pWegHin, Weg* pWegZruck, Kreuzung* pGegenKreuzung)
{
	pWegHin->vSetRueckweg(pWegZruck);
	pWegHin->vSetNaechsteKreuzung(pGegenKreuzung);

	p_pWege.push_back(pWegHin);
}

void Kreuzung::vTanken(Fahrzeug *pFahrzeug)
{
	if (p_dTankstelle > (0.0+DBL_EPSILON))
	{
		p_dTankstelle = std::fmax(p_dTankstelle - pFahrzeug->dTanken(0.0), 0.0);
	}
}

void Kreuzung::vAnnahme(Fahrzeug* pFahrzeug, double dStartzeit)
{
	if (p_pWege.size() > 0)
	{
		std::list<Weg*>::iterator it;
		it = p_pWege.begin();

		pFahrzeug->vNeueStrecke(*it, dStartzeit);
		//(*it)->vAnnahme(pFahrzeug, dStartzeit);
		//(*it)->vSetNaechsteKreuzung(this);
		vTanken(pFahrzeug);
	}
}

void Kreuzung::vAnnahme(Fahrzeug* pFahrzeug, Weg* pWeg)
{
	for (Weg* W : p_pWege)
		if (W == pWeg)
		{
			//W->vAnnahme(pFahrzeug);
			pFahrzeug->vNeueStrecke(W);
			vTanken(pFahrzeug);
		}
}

void Kreuzung::vAbfertigung()
{
	for (Weg* W : p_pWege)
		W->vAbfertigung();
}

void Kreuzung::vZeichne() const
{
	for (Weg* W : p_pWege)
		W->vZeichne();
}

void Kreuzung::vSetTankstelle(double dInhalt)
{
	p_dTankstelle = dInhalt;
}

double Kreuzung::dGetTankstelle() const
{
	return p_dTankstelle;
}

Weg* Kreuzung::ptZufaelligerWeg(Weg* pWeg) const
{
	if (p_pWege.size() > 1)
	{
		std::random_device random_dev;
		std::default_random_engine Generator{random_dev()};
		std::uniform_real_distribution<double> Distribution(0.0, 1.0);
		while (true)
		{
			for (Weg* W : p_pWege)
			{
				if (W != pWeg->pGetRueckweg())
					if (Distribution(Generator) < (1.0 / (p_pWege.size() - 1)))
						return W;
			}
		}
	}
	else
		return pWeg->pGetRueckweg();
}

std::ostream& Kreuzung::ostreamAusgabe(std::ostream& Out) const
{
	AktivesVO::ostreamAusgabe(Out);

	for (Weg* W : p_pWege)
		Out << *W << std::endl;

	return Out;
}