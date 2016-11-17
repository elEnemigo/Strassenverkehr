#include "Weg.h"
#include "Fahrzeug.h"
#include "Fahrrad.h"
#include "PKW.h"
#include "SimuClient.h"
#include "LazyListe.h"

#include <vector>
#include <random>

#pragma comment(lib, "SimuClient.lib")

// Globals
double dGlobaleZeit = 0.0;

// Prototypen
void vAufgabe_1();
void vAufgabe_1_deb();
void vAufgabe_2();
void vAufgabe_3();
void vAufgabe_4();
void vAufgabe_5();
void vAufgabe_6();
void vAufgabe_6a();

int main()
{
	//vAufgabe_1();
	//vAufgabe_1_deb();
	
	//vAufgabe_2();

	//vAufgabe_3();
	
	vAufgabe_4();

	vAufgabe_5();

	vAufgabe_6();

	vAufgabe_6a();

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

// Testfunktion der Aufgabe 4
void vAufgabe_4()
{
	Weg DieserWeg("WEG", 100);
	Fahrzeug Fahrzeug1("F1", 50);
	Fahrzeug Fahrzeug2("F2", 80);

	std::cout << DieserWeg << std::endl;

	Fahrzeug1.vNeueStrecke(&DieserWeg);
	Fahrzeug2.vNeueStrecke(&DieserWeg, 1.5);
	std::cout << DieserWeg << std::endl;

	dGlobaleZeit = 0.0;
	while (dGlobaleZeit < 6.0)
	{
		DieserWeg.vAbfertigung();
		std::cout << Fahrzeug1 << "    T = " << dGlobaleZeit << std::endl;
		std::cout << Fahrzeug2 << std::endl;
		dGlobaleZeit += 0.5;
	}
}

void vAufgabe_5()
{
	Weg DieserWeg("WEG", 100);
	Fahrzeug Fahrzeug1("F1", 50);
	Fahrzeug Fahrzeug2("F2", 80);

	std::cout << DieserWeg << std::endl;

	Fahrzeug1.vNeueStrecke(&DieserWeg);
	Fahrzeug2.vNeueStrecke(&DieserWeg, 3.0);
	std::cout << DieserWeg << std::endl;

	dGlobaleZeit = 0.0;
	while (dGlobaleZeit < 6.0)
	{
		std::cout << "						T = " << dGlobaleZeit << std::endl;
		DieserWeg.vAbfertigung();
		std::cout << Fahrzeug1 << std::endl;
		std::cout << Fahrzeug2 << std::endl;
		dGlobaleZeit += 0.3;
	}


	Weg W1("HIN", 500);
	Weg W2("RUCK", 500, Begrenzung::Innerorts);
	std::vector<Fahrzeug*> FahrzeugListe;
	FahrzeugListe.push_back(new PKW("F1P", 130, 5.4));
	FahrzeugListe.push_back(new PKW("F1F", 80, 6.5));
	FahrzeugListe.push_back(new Fahrrad("F2P", 25));
	FahrzeugListe.push_back(new Fahrrad("F2F", 18));
	int Points[4] = { 100, 100, 500, 500 };

	FahrzeugListe.at(0)->vNeueStrecke(&W1, 1.5);
	FahrzeugListe.at(1)->vNeueStrecke(&W1);
	FahrzeugListe.at(2)->vNeueStrecke(&W2, 3.25);
	FahrzeugListe.at(3)->vNeueStrecke(&W2);

	system("java.exe -version");
	bInitialisiereGrafik(800, 600);
	bZeichneStrasse(W1.sGetName(), W2.sGetName(), (int)W1.dGetLaenge(), 2, Points);

	dGlobaleZeit = 0.0;
	while (dGlobaleZeit < 6.0 + DBL_EPSILON)
	{
		vSetzeZeit(dGlobaleZeit);
		W1.vAbfertigung();
		W2.vAbfertigung();

		FahrzeugListe.at(0)->vZeichnen(&W1);
		FahrzeugListe.at(1)->vZeichnen(&W1);
		FahrzeugListe.at(2)->vZeichnen(&W1);
		FahrzeugListe.at(3)->vZeichnen(&W1);

		vSleep(125);
		dGlobaleZeit += 0.125;
	}

	vBeendeGrafik();
	for (Fahrzeug* pF : FahrzeugListe)
		delete pF;
	FahrzeugListe.clear();
}

void vAufgabe_6()
{

}

void vAufgabe_6a()
{
	LazyListe<int> Test;

	// Initialisieren
	for (int i = 0; i < 10; i++)
		Test.push_back(rand() % 11 + 1);

	// Ausgeben
	for (std::list<int>::iterator it = Test.begin(); it != Test.end(); it++)
		std::cout << (*it) << ", ";
	std::cout << std::endl;

	// Elemente >5 löschen
	for (std::list<int>::iterator it = Test.begin(); it != Test.end(); it++)
		if ((*it) > 5)
			Test.erase(it);

	// Ausgeben
	for (std::list<int>::iterator it = Test.begin(); it != Test.end(); it++)
		std::cout << (*it) << ", ";
	std::cout << std::endl;

	// Aktualisieren
	Test.vAktualisieren();

	// Ausgeben
	for (std::list<int>::iterator it = Test.begin(); it != Test.end(); it++)
		std::cout << (*it) << ", ";
	std::cout << std::endl;

	// Am Anfang und Ende Zahlen einfügen
	Test.push_front(-100);
	Test.push_back(100);
	
	// Aktualisieren
	Test.vAktualisieren();

	// Ausgeben
	for (std::list<int>::iterator it = Test.begin(); it != Test.end(); it++)
		std::cout << (*it) << ", ";
	std::cout << std::endl;
}