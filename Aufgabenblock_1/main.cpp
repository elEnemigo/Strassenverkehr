#include <vector>
#include <random>

#include "Fahrzeug.h"
#include "Fahrrad.h"
#include "PKW.h"

// Globals
double dGlobaleZeit = 0.0;

// Prototypen
void vAufgabe_1();
void vAufgabe_1_deb();
void vAufgabe_2();
void vAufgabe_3();

int main()
{
	vAufgabe_1();
	//vAufgabe_1_deb();
	
	vAufgabe_2();

	vAufgabe_3();
	
	system("PAUSE");
}

// Automatische Erstellung der Tabelle
void vFahrzeugTabelle(Fahrzeug** FahrzeugFeld, int iNumFahrzeuge)
{
	std::ios state(NULL);
	state.copyfmt(std::cout);

	std::cout << std::setiosflags(std::ios::left) << std::setw(4)
		<< "ID";
	std::cout << std::setw(7)
		<< "Name";
	std::cout << std::setw(3)
		<< ":";
	std::cout << std::setw(9) << std::setprecision(2)
		<< "MaxKmh ";
	std::cout << std::setw(18)
		<< "Gesamtstrecke ";
	std::cout << std::endl << std::setfill('+') << std::setw(40) << "+" << std::setfill(' ') << std::endl;

	for (int i = 0; i < iNumFahrzeuge; i++)
	{
		FahrzeugFeld[i]->vAusgabe();
		std::cout << std::endl;
	}

	std::cout << std::endl << std::resetiosflags(std::ios::left);

	std::cout.copyfmt(state);
}

// Testfunktion der Aufgabe 1
void vAufgabe_1()
{
	// 1.3
	Fahrzeug F1Stat;
	Fahrzeug F2Stat("F2Stat");

	Fahrzeug* F1Dyn;
	Fahrzeug* F2Dyn;
	F1Dyn = new Fahrzeug();
	F2Dyn = new Fahrzeug("F2Dyn");

	delete F2Dyn;
	delete F1Dyn;

	// 1.5/1.6
	Fahrzeug F1("PKW1", 40.0);
	Fahrzeug F2("AUTO3", 30.0);
	Fahrzeug* Liste[2];
	Liste[0] = &F1;
	Liste[1] = &F2;

	vFahrzeugTabelle( Liste, 2);

	// 1.9
	while (dGlobaleZeit < 2.0)
	{
		dGlobaleZeit += 0.25;

		F1.vAbfertigung();
		F2.vAbfertigung();
		vFahrzeugTabelle(Liste, 2);
	}
}

// Testfunktion zum Debuggen der Aufgabe 1
void vAufgabe_1_deb()
{
	Fahrzeug* Fahrzeuge[4];

	Fahrzeuge[0] = new Fahrzeug("F1", 40.0);
	Fahrzeuge[1] = new Fahrzeug("F2", 60.0);
	Fahrzeuge[2] = new Fahrzeug("F3", 80.0);
	Fahrzeuge[3] = new Fahrzeug("F4", 100.0);

	for (int i = 0; i < 4; i++)
	{
		Fahrzeuge[i]->vAusgabe();
		std::cout << std::endl;
	}

	Fahrzeuge[2] = nullptr;
	for (int i = 0; i < 4; i++)		// Crash
	{
		Fahrzeuge[i]->vAusgabe();	// Adresse 0 | Inhalt nicht lesbar
		std::cout << std::endl;
	}

	delete Fahrzeuge[0];
	delete Fahrzeuge[1];
	delete Fahrzeuge[2];
	delete Fahrzeuge[3];
}

// Testfunktion der Aufgabe 2
void vAufgabe_2()
{
	double dAnzahlF;
	double dAnzahlA;
	std::vector<Fahrzeug*> Fahrzeuge;
	std::default_random_engine Generator;
	std::uniform_real_distribution<double> Distribution(0.0, 1.0);

	// Cout status speichern
	std::ios state(NULL);
	state.copyfmt(std::cout);

	std::cout << "Wieviele Fahrraeder wollen sie erzeugen? ";
	std::cin >> dAnzahlF;

	std::cout << "Und Autos? ";
	std::cin >> dAnzahlA;

	// Fahrzeuge generieren
	for (int i = 0; i < dAnzahlF; i++)
	{
		std::ostringstream out;
		out << "FRad" << i + 1;
		double Geschwindigkeit = Distribution(Generator) * 10.0 + 12.0;
		Fahrzeuge.push_back(new Fahrrad(out.str(), Geschwindigkeit));
	}
	for (int i = 0; i < dAnzahlA; i++)
	{
		std::ostringstream out;
		out << "PKW" << i+1;
		double Geschwindigkeit = Distribution(Generator) * 100.0 + 30.0;
		double Verbrauch = Distribution(Generator) * 10.0 + 4.0;
		Fahrzeuge.push_back(new PKW(out.str(), Geschwindigkeit, Verbrauch));
	}

	dGlobaleZeit = 0.0;
	bool bGetankt = false;
	while (dGlobaleZeit < 6.0)
	{
		// Spaltennamen ausgeben
		std::cout << std::endl << std::setiosflags(std::ios::left) << std::setw(4)
			<< "ID";
		std::cout << std::setw(7)
			<< "Name";
		std::cout << std::setw(3)
			<< ":";
		std::cout << std::setw(9) << std::setprecision(2)
			<< "MaxKmh ";
		std::cout << std::setw(18)
			<< "Gesamtstrecke ";
		std::cout << std::setw(12)
			<< "Verbrauch ";
		std::cout << std::setw(12)
			<< "Tankinhalt ";
		std::cout << std::endl << std::setfill('+') << std::setw(70) << "+" << std::setfill(' ') << std::endl;

		// Jedes einzelne Fahrzeug abfertigen
		for (Fahrzeug* F : Fahrzeuge)
		{
			F->vAbfertigung();
			std::cout << *F << std::endl;
		}

		// Nach 3 Stunden volltanken
		if (dGlobaleZeit >= 3.0 && !bGetankt)
		{
			for (Fahrzeug* F : Fahrzeuge)
				F->dTanken();
			bGetankt = true;
		}

		dGlobaleZeit += 0.5;
	}

	// Dynamische Objekte löschen
	for (Fahrzeug* F : Fahrzeuge)
		delete F;
	Fahrzeuge.clear();

	// cout resetten
	std::cout << std::endl << std::resetiosflags(std::ios::left);
	std::cout.copyfmt(state);
}

// Testfunktion der Aufgabe 3
void vAufgabe_3()
{
	Fahrzeug F("F-zeug", 40);
	PKW P("PKW", 100, 12);
	Fahrrad FR("FAHRRAD", 20);

	// Streamoperator testen
	std::cout << F <<  std::endl << P << std::endl << FR << std::endl;
	dGlobaleZeit += 0.5;
	F.vAbfertigung();
	P.vAbfertigung();
	FR.vAbfertigung();
	std::cout << F << std::endl << P << std::endl << FR << std::endl;

	// kleiner-als Operator testen
	if (F < P && F < FR)
		std::cout << "Das Fahrzeug ist der Langsamste\n";
	else if (P < F && P < FR)
		std::cout << "Der PKW ist der Langsamste\n";
	else if (FR < P && FR < F)
		std::cout << "Das Fahrrad ist der Langsamste\n";

	// Zuweisungsoperator und Copy-Konstruktor testen
	Fahrzeug Test(F);
	std::cout << "\nKopie von Fahrzeug\n" << Test << std::endl;
	Fahrzeug Test2;
	Test2 = FR;
	std::cout << "Neue Zuweisung von FAHRRAD\n" << Test2 << std::endl;
}