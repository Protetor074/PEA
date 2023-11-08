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
	int minVertex = (int)inifile.GetLongValue("SEKCJA1", "MinimalnaLiczbaWierzcholkow", 0);
	int maxVertex = (int)inifile.GetLongValue("SEKCJA1", "MaksymalnaLiczbaWierzcholkow", 0);
	const char* inputFile = inifile.GetValue("SEKCJA1", "PlikWejsciowy", "HeldKarpIn.txt");
	const char* outputFile = inifile.GetValue("SEKCJA1", "PlikWyjsciowy", "HeldKarpOut.txt");

	std::string inputStringTab[100];

	std::string inputFileString(inputFile);
	std::string outputFileString(outputFile);
	inputFileString = inputFileString + ".txt";
	outputFileString = outputFileString + ".txt";


	size_t pos = 0;
	std::string token;
	int inputFileNumber = 0;

	while ((pos = inputFileString.find(";")) != std::string::npos) {
		token = inputFileString.substr(0, pos);
		inputStringTab[inputFileNumber] = token + ".txt";
		inputFileString.erase(0, pos + 1);
		inputFileNumber++;
	}

	if (mode == -1) {//Testy
		KomivoyagerLocation kl;
		//kl.set(inputFileString);
		kl.generate(4, 5);
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
		std::cout << "Minimalna Liczba Wierzcholkow: " << minVertex << std::endl;
		std::cout << "Maksymalna Liczba Wierzcholkow: " << maxVertex << std::endl;
		std::cout << "Plik wyjsciowy: " << outputFileString << std::endl;

		Pomiar pom;
		pom.autoTest(outputFileString, testNumber, testRepeat,minVertex,maxVertex);
		
	}
	else if(mode == 1){
		std::cout << "Tryb: " << "Wyznaczania drogi z pliku" << std::endl;
		std::cout << "Pliki wejsciowe: " << std::endl;
		for (int i = 0; i < inputFileNumber; i++) {
			std::cout << inputStringTab[i] << std::endl;
		}
		std::cout << "Plik wyjsciowy: " << outputFileString << std::endl;

		KomivoyagerLocation kl;
		HeldKarpAlg hka;
		std::fstream plik;
		//czyszczenie
		plik.open(outputFileString, std::ios::out);
		plik.close();
		plik.open(outputFileString, std::ios::app);

		for (int i = 0; i < inputFileNumber; i++) {
			std::cout << "\n\n" << inputStringTab[i] << std::endl;
			kl.set(inputStringTab[i]);
			kl.printTab();

			hka.init(kl.tabLocation, kl.size);
			std::vector<std::string> result = hka.printResult();

			plik << "Plik wejściowy" << inputStringTab[i] << std::endl;
			plik << result[0] << std::endl;
			plik << result[1] << std::endl<<std::endl;
		}
		plik.close();
	}
	return 0;
}
