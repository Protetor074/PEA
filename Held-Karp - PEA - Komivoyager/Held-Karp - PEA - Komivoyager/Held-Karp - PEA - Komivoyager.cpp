// Held-Karp - PEA - Komivoyager.cpp: definiuje punkt wejścia dla aplikacji.
//

#include "Held-Karp - PEA - Komivoyager.h"

using namespace std;

int main()
{
	CSimpleIniA inifile;

	inifile.LoadFile("ustawienia.ini"); // wczytanie pliku
	//wczytanie wartości z pliku

	int mode = (int)inifile.GetLongValue("SEKCJA1", "Tryb", 0);
	int testNumber = (int)inifile.GetLongValue("SEKCJA1", "IloscPomiarow", 0);
	int testRepeat = (int)inifile.GetLongValue("SEKCJA1", "IloscPowtozenPomiaru", 0);
	const char* inputFile = inifile.GetValue("SEKCJA1", "PlikWejsciowy", "BruteForceData.txt");
	const char* outputFile = inifile.GetValue("SEKCJA1", "PlikWyjsciowy", "Bruteforce.txt");

	std::string inputFileString(inputFile);
	std::string outputFileString(outputFile);

	if (mode == -1) {//Testy
		KomivoyagerLocation kl;
		kl.set(inputFileString);
		//kl.generate(4, 100);
		kl.printTab();
		//std::cout << "\n\n\n"<<kl.tabLocation[2][1]<<"\n\n\n";

		HeldKarpAlg hka;

		hka.init(kl.tabLocation,kl.size);
		hka.printResult();

	}
	else if (mode == 0) {
		std::cout << "Tryb: " << "Pomiarow automatycznych\n";
		std::cout << "Liczba pomiarow: " << testNumber << std::endl;
		std::cout << "Liczba powtozen: " << testRepeat << std::endl;
		std::cout << "Plik wyjsciowy: " << outputFileString << std::endl;

		//Pomiar pom;
		//pom.test(outputFileString, testNumber, testRepeat);

	}
	else if(mode == 1){
		std::cout << "Tryb: " << "Wyznaczania drogi z pliku" << std::endl;
		std::cout << "Plik wejsciowy: " << inputFileString << std::endl;
		std::cout << "Plik wyjsciowy: " << outputFileString << std::endl;

		KomivoyagerLocation kl;
		kl.printTab();		
	}
	return 0;
}
