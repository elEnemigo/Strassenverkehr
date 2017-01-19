#include "Weg.h"
#include "Fahrzeug.h"
#include "Fahrrad.h"
#include "PKW.h"
#include "SimuClient.h"
#include "LazyListe.h"
#include "Kreuzung.h"
#include "Welt.h"

#include <vector>
#include <random>
#include <fstream>

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
void vAufgabe_7();
void vAufgabe_8();
void vAufgabe_9a();
void vAufgabe_9b();
void vAufgabe_9c();

int main()
{
	//vAufgabe_1();
	//vAufgabe_1_deb();
	
	//vAufgabe_2();

	//vAufgabe_3();
	
	//vAufgabe_4();

	//vAufgabe_5();

	//vAufgabe_6();

	//vAufgabe_6a();

	//vAufgabe_7();

	//vAufgabe_8();

	vAufgabe_9a();

	vAufgabe_9b();

	vAufgabe_9c();

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
	std::cout << "---------------------------Aufgabe 4 -------------------------------" << std::endl;
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
	std::cout << "---------------------------Aufgabe 5 -------------------------------" << std::endl;
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


	Weg W1("HIN", 500, Begrenzung::Innerorts);
	Weg W2("RUCK", 500, Begrenzung::Innerorts);
	std::vector<Fahrzeug*> FahrzeugListe;
	FahrzeugListe.push_back(new PKW("F1P", 130, 5.4));
	FahrzeugListe.push_back(new PKW("F1F", 80, 6.5));
	FahrzeugListe.push_back(new Fahrrad("F2P", 25));
	FahrzeugListe.push_back(new Fahrrad("F2F", 18));
	int Points[4] = { 100, 100, 500, 100 };

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
		FahrzeugListe.at(2)->vZeichnen(&W2);
		FahrzeugListe.at(3)->vZeichnen(&W2);

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
	std::cout << "---------------------------Aufgabe 6 -------------------------------" << std::endl;
	Weg DieserWeg("WEG", 100);
	Fahrzeug Fahrzeug1("F1", 50);
	Fahrzeug Fahrzeug2("F2", 80);

	std::cout << DieserWeg << std::endl;

	DieserWeg.vAnnahme(&Fahrzeug1);
	DieserWeg.vAnnahme(&Fahrzeug2);
	DieserWeg.vAbfertigung();

	std::cout << DieserWeg << std::endl;

	DieserWeg.vAbgabe(&Fahrzeug1);
	DieserWeg.vAbfertigung();

	std::cout << DieserWeg << std::endl;
}

void vAufgabe_6a()
{
	std::cout << "---------------------------Aufgabe 6a -------------------------------" << std::endl;
	LazyListe<int> Test;

	// Initialisieren
	for (int i = 0; i < 10; i++)
		Test.push_back(rand() % 11 + 1);

	// Ausgeben
	Test.vAktualisieren();
	for (std::list<int>::iterator it = Test.begin(); it != Test.end(); it++)
		std::cout << (*it) << ", ";
	std::cout << std::endl;

	// Elemente >5 löschen
	Test.vAktualisieren();
	for (std::list<int>::iterator it = Test.begin(); it != Test.end(); it++)
		if ((*it) > 5)
			Test.erase(it);
	Test.vAktualisieren();

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

void vAufgabe_7()
{
	std::cout << "--------------------------- Aufgabe 7 -------------------------------" << std::endl;
	Weg Einweg("Weg", 100, Autobahn, true);
	Fahrrad F1("Fahrrad", 20);
	PKW P1("PKW", 140, 6.0);
	Fahrzeug FZ1("Fahrzeug", 100);

	F1.vNeueStrecke(&Einweg, 0.5);
	P1.vNeueStrecke(&Einweg, 5.5);

	dGlobaleZeit = 0.0;
	bool bHalbzeit = false;
	double dMaxZeit = 60.0;
	while (dGlobaleZeit < dMaxZeit + DBL_EPSILON)
	{
		// Nach hälfte der Zeit neues Fahrzeug hinzufügen
		if (dGlobaleZeit >= 3.0 && !bHalbzeit)
		{
			//Einweg.vAnnahme(&FZ1, 5.0);
			FZ1.vNeueStrecke(&Einweg, 5.0);
			bHalbzeit = true;
		}

		Einweg.vAbfertigung();
		std::cout << Einweg << "						T = " << dGlobaleZeit << std::endl;

		if (Einweg.bKeineFahrzeuge())
			break;

		//vSleep(125);
		dGlobaleZeit += 0.125;
	}
}

void vAufgabe_8()
{
	std::cout << "--------------------------- Aufgabe 8 -------------------------------" << std::endl;
	Kreuzung Kr1("Kr1"), Kr2("Kr2"), Kr3("Kr3"), Kr4("Kr4");

	// Kreuzungen
	Kr1.vVerbinde("W12", "W21", &Kr2, 40.0, Innerorts);
	Kr2.vVerbinde("W23a", "W32a", &Kr3, 115.0, Autobahn, false);
	Kr2.vVerbinde("W23b", "W32b", &Kr3, 40.0, Innerorts);
	Kr2.vVerbinde("W24", "W42", &Kr4, 55.0, Innerorts);
	Kr3.vVerbinde("W34", "W43", &Kr4, 85.0, Autobahn, false);
	Kr4.vVerbinde("W44a", "W44b", &Kr4, 130.0, Land, false);
	Kr2.vSetTankstelle(1000.0);

	// Fahrzeuge
	Fahrzeug F1("F1", 80.0);
	PKW P1("P1", 200.0, 8.0, 65.0);
	PKW P2("P2", 120.0, 6.0);
	Fahrrad F2("F2", 25);
	PKW P3("P3", 130, 7.0);
	Kr1.vAnnahme(&F1, 0.0);
	Kr1.vAnnahme(&P1, 2.5);
	Kr1.vAnnahme(&P2, 1.0);
	Kr1.vAnnahme(&F2, 2.0);
	Kr1.vAnnahme(&P3, 0.0);

	dGlobaleZeit = 0.0;
	bInitialisiereGrafik(1024, 768);
	int pos1[4] = { 680, 40, 680, 300 };
	int pos2[12] = {680, 300, 850, 300, 970, 390, 970, 500, 850, 570, 680, 570};
	int pos3[4] = {680, 300, 680, 570};
	int pos4[4] = {680, 300, 320, 300};
	int pos5[10] = {680, 570, 500, 570, 350, 510, 320, 420, 320, 300};
	int pos6[14] = {320, 300, 320, 150, 200, 60, 80, 90, 70, 250, 170, 300, 320, 300};
	bZeichneStrasse("W12", "W21", 40, 2, pos1);
	bZeichneStrasse("W23a", "W32a", 115, 6, pos2);
	bZeichneStrasse("W23b", "W32b", 40, 2, pos3);
	bZeichneStrasse("W24", "W42", 50, 2, pos4);
	bZeichneStrasse("W34", "W43", 85, 5, pos5);
	bZeichneStrasse("W44a", "W44b", 130, 7, pos6);

	bZeichneKreuzung(680, 40);
	bZeichneKreuzung(680, 300);
	bZeichneKreuzung(680, 570);
	bZeichneKreuzung(320, 300);

	while (dGlobaleZeit < 6.0 + DBL_EPSILON)
	{
		vSetzeZeit(dGlobaleZeit);

		Kr1.vAbfertigung();
		Kr2.vAbfertigung();
		Kr3.vAbfertigung();
		Kr4.vAbfertigung();

		Kr1.vZeichne();
		Kr2.vZeichne();
		Kr3.vZeichne();
		Kr4.vZeichne();

		std::cout << "Kr1: " << Kr1 << "						T = " << dGlobaleZeit << std::endl;
		std::cout << "Kr2: " << Kr2;
		std::cout << "Kr3: " << Kr3;
		std::cout << "Kr4: " << Kr4;

		vSleep(33);
		dGlobaleZeit += 0.033;
	}

	vBeendeGrafik();
}

void vAufgabe_9a()
{
	std::cout << "--------------------------- Aufgabe 9a -------------------------------" << std::endl;

	// Locals
	std::ifstream VOFile;
	PKW P1;
	Fahrrad FR1;
	Kreuzung K1;
	// Kreuzung K2("Kr1"); // Zum Testen der Exception
	AktivesVO* pTest = nullptr;

	// Startup
	VOFile.open("VO.dat", std::ifstream::in);
	if (!VOFile)
	{
		std:cerr << "Failed to Open File!" << std::endl;
		return;
	}

	// Einlesen
	try {
		VOFile >> P1;
		VOFile >> FR1;
		VOFile >> K1;
	} catch (std::string& Str){
		std::cerr << Str << std::endl;
	}

	// Ausgeben
	std::cout << P1 << std::endl;
	std::cout << FR1 << std::endl;
	std::cout << K1 << std::endl;

	// Map testen
	bool bExc = false;
	try {
		pTest = AktivesVO::ptObjekt("Rennrad");
	}
	catch (std::string& Str) {
		std::cerr << Str << std::endl;

		bExc = true;
	}
	if (!bExc)
		std::cout << "Gefunden: " << *pTest << std::endl;

	// Cleanup
	VOFile.close();
}

void vAufgabe_9b()
{
	std::cout << "--------------------------- Aufgabe 9b -------------------------------" << std::endl;

	// Locals
	std::ifstream VOFile;
	Welt NeueWelt;

	// Startup
	VOFile.open("Simu.dat", std::ifstream::in);
	if (!VOFile)
	{
	std:cerr << "Failed to Open File!" << std::endl;
		return;
	}

	// Einlesen
	try {
		NeueWelt.vEinlesen(VOFile);
	}
	catch (std::string& Str) {
		std::cerr << Str << std::endl;
	}

	// Simulieren
	for (int i = 0; i < 40; i++)
		NeueWelt.vSimulation(0.033);

	// Cleanup
	VOFile.close();
}

void vAufgabe_9c()
{
	std::cout << "--------------------------- Aufgabe 9c -------------------------------" << std::endl;

	// Locals
	std::ifstream VOFile;
	Welt NeueWelt;

	// Startup
	VOFile.open("SimuDisplay.dat", std::ifstream::in);
	if (!VOFile)
	{
	std:cerr << "Failed to Open File!" << std::endl;
		return;
	}

	// Einlesen
	try {
		NeueWelt.vEinlesenMitGrafik(VOFile);
	}
	catch (std::string& Str) {
		std::cerr << Str << std::endl;
	}

	// Simulieren
	for (int i = 0; i < 400; i++)
		NeueWelt.vSimulation(0.033);

	// Cleanup
	VOFile.close();
}