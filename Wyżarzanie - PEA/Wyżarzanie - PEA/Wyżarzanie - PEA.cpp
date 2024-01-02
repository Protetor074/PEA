// Wyżarzanie - PEA.cpp: definiuje punkt wejścia dla aplikacji.
//

#include "Wyżarzanie - PEA.h"

using namespace std;

int main()
{
	CSimpleIniA inifile;

	inifile.LoadFile("ustawienia.ini"); // wczytanie pliku
	//wczytanie wartości z pliku
	int mode = (int)inifile.GetLongValue("SEKCJA1", "Tryb", 0);
<<<<<<< HEAD
	const char* inputFile = inifile.GetValue("SEKCJA1", "PlikWejsciowy", "HeldKarpIn.txt");
	const char* outputFile = inifile.GetValue("SEKCJA1", "PlikWyjsciowy", "HeldKarpOut.txt");

	bool startPathGeneratorMode = inifile.GetBoolValue("SEKCJA2", "TrybGenerowaniaSciezkiPoczatkowej", false);
	bool startTempGeneratorMode = inifile.GetBoolValue("SEKCJA2", "TrybGenerowaniaTemperaturyPoczatkowej", false);
	double startTempGenSamplesNumberCorectionVal = inifile.GetDoubleValue("SEKCJA2", "WspolczynikKorekcjiIlosciPrubekGeneracjiZeSredniej", 0.3);
	int eraLongMode = (int)inifile.GetLongValue("SEKCJA2", "TrybDlogosciEpoki", 6);
	double eraLongCorectionVal = inifile.GetDoubleValue("SEKCJA2", "WspolczynnikKorekcjiDlogosciEpoki", 0.3);
	int repeatNumber = (int)inifile.GetLongValue("SEKCJA2", "LiczbaPowtorzenPomiaru", 10);

=======
	int testNumber = (int)inifile.GetLongValue("SEKCJA1", "IloscPomiarow", 0);
	int testRepeat = (int)inifile.GetLongValue("SEKCJA1", "IloscPowtozenPomiaru", 0);
	int minVertex = (int)inifile.GetLongValue("SEKCJA1", "MinimalnaLiczbaWierzcholkow", 0);
	int maxVertex = (int)inifile.GetLongValue("SEKCJA1", "MaksymalnaLiczbaWierzcholkow", 0);
	const char* inputFile = inifile.GetValue("SEKCJA1", "PlikWejsciowy", "HeldKarpIn.txt");
	const char* outputFile = inifile.GetValue("SEKCJA1", "PlikWyjsciowy", "HeldKarpOut.txt");

	int minVertexDistance = (int)inifile.GetLongValue("SEKCJA2", "MinimalnaWartoscOdleglosci", 1);
	int maxVertexDistance = (int)inifile.GetLongValue("SEKCJA2", "MaxymalnaWartoscOdleglosci", 10);
	bool startPathGeneratorMode = inifile.GetBoolValue("SEKCJA2", "TrybGenerowaniaSciezkiPoczatkowej", false);
	bool startTempGeneratorMode = inifile.GetBoolValue("SEKCJA2", "TrybGenerowaniaTemperaturyPoczatkowej", false);
	int startTempGenSamplesNumber = (int)inifile.GetLongValue("SEKCJA2", "IloscPrubekGeneracjiZeSredniej", 10);
>>>>>>> 90e5141f80991f1b1268c09fab77eafdbfe6eea1

	bool coolingMode = inifile.GetBoolValue("SEKCJA3", "Tryb", false);
	double alfaVal = inifile.GetDoubleValue("SEKCJA3", "WspolczynikAlfa", 0.3);
	bool selectVertexMode = inifile.GetBoolValue("SEKCJA3", "TrybWyboruWierzcholkow", false);
	double propability = inifile.GetDoubleValue("SEKCJA3", "Prawdopodobienstwo", 0.9);
<<<<<<< HEAD
	
=======
	int kVal = (int)inifile.GetLongValue("SEKCJA3", "LiczbaStopni", 10);
	int lVal = (int)inifile.GetLongValue("SEKCJA3", "LiczbaPowtozenStopnia", 5);
>>>>>>> 90e5141f80991f1b1268c09fab77eafdbfe6eea1


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
<<<<<<< HEAD
		kl.generate(10, 1, 1000, false);
=======
		int tripCost[] = {minVertexDistance, maxVertexDistance};
		kl.generate(10, tripCost[0], tripCost[1], false);
>>>>>>> 90e5141f80991f1b1268c09fab77eafdbfe6eea1
		kl.printTab();
		//std::cout << "\n\n\n"<<kl.tabLocation[2][1]<<"\n\n\n";

		AS_Alg annealingAlg;
<<<<<<< HEAD
		annealingAlg.init(kl.tabLocation,kl.size, startPathGeneratorMode, startTempGeneratorMode, startTempGenSamplesNumberCorectionVal, startTempGenSamplesNumberCorectionVal, eraLongCorectionVal);
		//annealingAlg.init(kl.tabLocation, kl.size, 0, 10, true, false, 3, 0.6, tripCost[0], tripCost[1]);
		annealingAlg.startAlgoritmGeo(alfaVal, selectVertexMode, propability);
		annealingAlg.printPath("Chlodzenie geometryczne");

		//annealingAlg.clean();
		annealingAlg.startAlgoritmBoltzmann(selectVertexMode, propability);
		annealingAlg.printPath("Chlodzenie Boltzmana");

		//Pomiar pom;
		//pom.autoTest(outputFileString, testNumber, testRepeat, minVertex, maxVertex);
=======
		annealingAlg.init(kl.tabLocation,kl.size, tripCost[0], tripCost[1], startPathGeneratorMode, startTempGeneratorMode, startTempGenSamplesNumber);
		//annealingAlg.init(kl.tabLocation, kl.size, 0, 10, true, false, 3, 0.6, tripCost[0], tripCost[1]);
		annealingAlg.startAlgoritmGeo(alfaVal, selectVertexMode, propability, kVal, lVal);
		annealingAlg.printPath("Chlodzenie geometryczne");

		//annealingAlg.clean();
		annealingAlg.startAlgoritmBoltzmann(selectVertexMode, propability, kVal, lVal);
		annealingAlg.printPath("Chlodzenie Boltzmana");

>>>>>>> 90e5141f80991f1b1268c09fab77eafdbfe6eea1


	}
	else if (mode == 0) {
		std::cout << "Tryb: " << "Pomiarow automatycznych\n";
<<<<<<< HEAD
		

		Pomiar pom;
		pom.autoTest();

	}
	else if (mode == 1) {
		Pomiar pom;
		pom.autoTest2();

	}
	else if (mode == 2) {
=======
		std::cout << "Liczba pomiarow: " << testNumber << std::endl;
		std::cout << "Liczba powtozen: " << testRepeat << std::endl;
		std::cout << "Minimalna Liczba Wierzcholkow: " << minVertex << std::endl;
		std::cout << "Maksymalna Liczba Wierzcholkow: " << maxVertex << std::endl;
		std::cout << "Plik wyjsciowy: " << outputFileString << std::endl;

		//Pomiar pom;
		//pom.autoTest(outputFileString, testNumber, testRepeat, minVertex, maxVertex);

	}
	else if (mode == 1) {
>>>>>>> 90e5141f80991f1b1268c09fab77eafdbfe6eea1
		std::cout << "Tryb: " << "Wyznaczania drogi z pliku" << std::endl;
		std::cout << "Pliki wejsciowe: " << std::endl;
		for (int i = 0; i < inputFileNumber; i++) {
			std::cout << inputStringTab[i] << std::endl;
		}
		std::cout << "Plik wyjsciowy: " << outputFileString << std::endl;

<<<<<<< HEAD
		KomivoyagerLocation kl;
		AS_Alg annealingAlg;

=======
		//KomivoyagerLocation kl;
>>>>>>> 90e5141f80991f1b1268c09fab77eafdbfe6eea1

		std::fstream plik;
		//czyszczenie
		plik.open(outputFileString, std::ios::out);
		plik.close();
		plik.open(outputFileString, std::ios::app);

<<<<<<< HEAD
		


		for (int i = 0; i < inputFileNumber; i++) {
			std::cout << "\n\n" << inputStringTab[i] << std::endl;

			kl.set(inputStringTab[i]);

			std::vector<int> bestPath;
			int bestCost = INT_MAX;

			Pomiar pom;
			pom.StartCounter();
			double timeStart;
			double timeEnd;
			double time;

			annealingAlg.init(kl.tabLocation, kl.size, startPathGeneratorMode, startTempGeneratorMode, startTempGenSamplesNumberCorectionVal, eraLongCorectionVal, eraLongMode);
			
			timeStart = pom.GetCounter();
			for (int i = 0; i < repeatNumber; i++) {
				annealingAlg.currentTemperature = annealingAlg.initialTemperature;
				annealingAlg.curentCost = annealingAlg.initCost;
				annealingAlg.currentPath.assign(annealingAlg.initPath.begin(), annealingAlg.initPath.end());
				if (coolingMode) {
					annealingAlg.startAlgoritmBoltzmann(selectVertexMode, propability);
				}
				else {
					annealingAlg.startAlgoritmGeo(alfaVal, selectVertexMode, propability);
				}
				if (bestCost > annealingAlg.curentCost) {
					bestCost = annealingAlg.curentCost;
					bestPath.assign(annealingAlg.currentPath.begin(), annealingAlg.currentPath.end());
				}
			}
			timeEnd = pom.GetCounter();

			time = (timeEnd - timeStart) / repeatNumber;

			annealingAlg.currentPath.assign(bestPath.begin(), bestPath.end());
			annealingAlg.curentCost = bestCost;
		
			//kl.printTab();

			annealingAlg.getCurentCost();

			for (int i = 0; i < annealingAlg.currentPath.size(); i++) {
				annealingAlg.currentPath[i]++;
			}

			std::cout << "Sciezka = " << annealingAlg.getCurentPath() << "," << annealingAlg.currentPath[0] << std::endl;
			std::cout << "Koszt = " << annealingAlg.curentCost << std::endl;
			std::cout << "Czas pomiaru = " << time;

			plik << "Plik wejściowy = " << inputStringTab[i] << std::endl;
			plik << "Ścieżka = " << annealingAlg.getCurentPath() << "," << annealingAlg.currentPath[0] << std::endl;
			plik << "Koszt = " << annealingAlg.curentCost << std::endl;
			plik << "Czas pomiaru = " << time << "ms";
			plik << std::endl << std::endl;
=======
		for (int i = 0; i < inputFileNumber; i++) {
			std::cout << "\n\n" << inputStringTab[i] << std::endl;
			//kl.set(inputStringTab[i]);
			//kl.printTab();


			plik << "Plik wejściowy" << inputStringTab[i] << std::endl;
>>>>>>> 90e5141f80991f1b1268c09fab77eafdbfe6eea1

		}
		plik.close();
	}
	return 0;
}
