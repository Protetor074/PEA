#include <Windows.h>
#include <iostream>
#include <cstdlib>
#include <fstream>


#include <sys/stat.h>


#include "Genetic algorithm - PEA.h"


void Pomiar::file_clear(std::string plik_name, std::string initText) {
	std::fstream plik;
	plik.open(plik_name, std::ios::out);
	plik << initText << std::endl;
	plik.close();
}

void Pomiar::filewriter(std::string plik_name, std::string text) {
	std::fstream plik;
	int liczba;

	plik.open(plik_name, std::ios::app);

	plik << text << std::endl;
	plik.close();
}

void Pomiar::StartCounter()
{
	LARGE_INTEGER li;
	if (!QueryPerformanceFrequency(&li))
		std::cout << "QueryPerformanceFrequency failed!\n";

	PCFreq = double(li.QuadPart) / 1000.0;

	QueryPerformanceCounter(&li);
	CounterStart = li.QuadPart;
}

double Pomiar::GetCounter()
{
	LARGE_INTEGER li;
	QueryPerformanceCounter(&li);
	return double(li.QuadPart - CounterStart) / PCFreq;
}


long Pomiar::getMemory()
{
	MEMORYSTATUSEX statex;
	statex.dwLength = sizeof(statex);
	GlobalMemoryStatusEx(&statex);

	//_tprintf(TEXT("There is  %*ld percent of memory in use.\n"), WIDTH, statex.dwMemoryLoad);
	//_tprintf(TEXT("There are %*I64d total Mbytes of physical memory.\n"), WIDTH, statex.ullTotalPhys / DIV);
	//_tprintf(TEXT("There are %*I64d free Mbytes of physical memory.\n"), WIDTH, statex.ullAvailPhys / DIV);
	//_tprintf(TEXT("There are %*I64d total Mbytes of paging file.\n"), WIDTH, statex.ullTotalPageFile / DIV);
	//_tprintf(TEXT("There are %*I64d free Mbytes of paging file.\n"), WIDTH, statex.ullAvailPageFile / DIV);
	//_tprintf(TEXT("There are %*I64d total Mbytes of virtual memory.\n"), WIDTH, statex.ullTotalVirtual / DIV);
	//_tprintf(TEXT("There are %*I64d free Mbytes of virtual memory.\n"), WIDTH, statex.ullAvailVirtual / DIV);
	//_tprintf(TEXT("There are %*I64d free Mbytes of extended memory.\n"), WIDTH, statex.ullAvailExtendedVirtual / DIV);

	return (statex.ullTotalPhys / DIV) - (statex.ullAvailPhys / DIV);
}

/*void Pomiar::autoTest() {
	KomivoyagerLocation kl;
	double timeStart = 0;
	double timeEnd = 0;

	int startCost = 0;
	int boltzmanCost = 0;
	int geoCost = 0;
	int TempStart = 0;
	int kGeo = 0;
	int kBoltz = 0;
	int tabFileSize = 4;

	int liczbaPomiarow = 200;

	std::string text;

	StartCounter();

	std::string filePath = "C:/Users/alfag/OneDrive/Pulpit/Projekty/PEA/Data/ATSP_out/";
	std::string tabFile2[] = {//ATSP
		"Pliki Do testów/ATSP/br17.txt",
		"Pliki Do testów/ATSP/ftv44.txt",
		"Pliki Do testów/ATSP/ftv70.txt",
		"Pliki Do testów/ATSP/ftv170.txt",
		"Pliki Do testów/ATSP/rbg443.txt",
	};
	std::string tabFile[] = {//TSP
		"Pliki Do testów/TSP/berlin52.tsp",
		"Pliki Do testów/TSP/eil76.tsp",
		"Pliki Do testów/TSP/kroA100.tsp",
		"Pliki Do testów/TSP/brg180.tsp",
		"Pliki Do testów/TSP/a280.tsp",
	};

	bool testingModeOn[] = {
		false,//T0
		false,//StartPath
		false,//CoolingMode
		false,//EraTime
		false,//StartPathSelectVertex
		true//Poziom akceptacji
	};

	file_clear("TestStatus.txt", "Nazwa Pomiaru;Status");

	//Pomiary T0
	if (testingModeOn[0]) {
		std::cout << "Tryb pomiaru wyboru T0:\n";
		filewriter("TestStatus.txt", "Tryb pomiaru wyboru T0:\n");

		file_clear("TempTest.txt", "Plik;Tryb Temperatury;Index;TemperaturaPocz¹tkowa;Koszt pocz¹tkowy;Koszt Geo;Koszt Boltzmana;Liczba stopni Geo; Liczba stopni Boltzman;AVG");


		for (int fileIndex = 0; fileIndex < tabFileSize; fileIndex++) {

			kl.set(tabFile[fileIndex]);
			kl.set(filePath + tabFile[fileIndex]);

			AS_Alg annealingAlg;
			annealingAlg.init(kl.tabLocation, kl.size, false, false, 1, 0.5, 1);

			startCost = annealingAlg.getCurentCost();

			std::vector<int> min_maxCost = annealingAlg.getMinMaxCost();
			std::cout << "Test pliku:" << tabFile[fileIndex] << " E1 " << std::endl;
			filewriter("TestStatus.txt", "Test pliku: " + tabFile[fileIndex] + " E1");
			for (int i = 0; i < liczbaPomiarow; i++) {
				annealingAlg.generateMaxInitialTemperature(min_maxCost[0], min_maxCost[1]);

				annealingAlg.currentTemperature = annealingAlg.initialTemperature;
				annealingAlg.curentCost = annealingAlg.initCost;
				annealingAlg.currentPath.assign(annealingAlg.initPath.begin(), annealingAlg.initPath.end());

				TempStart = annealingAlg.getCurentTemp();
				annealingAlg.startAlgoritmGeo(0.3, false, 0.95);
				geoCost = annealingAlg.getCurentCost();
				kGeo = annealingAlg.getNumberK();

				annealingAlg.currentTemperature = annealingAlg.initialTemperature;
				annealingAlg.curentCost = annealingAlg.initCost;
				annealingAlg.currentPath.assign(annealingAlg.initPath.begin(), annealingAlg.initPath.end());

				annealingAlg.startAlgoritmBoltzmann(false, 0.95);
				boltzmanCost = annealingAlg.getCurentCost();
				kBoltz = annealingAlg.getNumberK();

				text = tabFile[fileIndex] + ";T0-Maksymalna ró¿nica;" + std::to_string(i + 1) + ";" + std::to_string(TempStart) + ";" + std::to_string(startCost) + ";" + std::to_string(geoCost) + ";" + std::to_string(boltzmanCost) + ";" + std::to_string(kGeo) + ";" + std::to_string(kBoltz) + ";0.0";
				filewriter("TempTest.txt", text);

			}

			std::string corectionVla;

			for (double i = 0.1; i <= 1; i = i + 0.1) {
				corectionVla = std::to_string(i);
				std::cout << "Test pliku:" << tabFile[fileIndex] << " E2 - " << i << std::endl;
				filewriter("TestStatus.txt", "Test pliku: " + tabFile[fileIndex] + " E2 - " + std::to_string(i));
				for (int j = 0; j < liczbaPomiarow; j++) {
					annealingAlg.generateInitialTemperatureFromAverage(kl.size * kl.size * i);

					annealingAlg.currentTemperature = annealingAlg.initialTemperature;
					annealingAlg.curentCost = annealingAlg.initCost;
					annealingAlg.currentPath.assign(annealingAlg.initPath.begin(), annealingAlg.initPath.end());

					TempStart = annealingAlg.getCurentTemp();
					annealingAlg.startAlgoritmGeo(0.3, false, 0.95);
					geoCost = annealingAlg.getCurentCost();
					kGeo = annealingAlg.getNumberK();

					annealingAlg.currentTemperature = annealingAlg.initialTemperature;
					annealingAlg.curentCost = annealingAlg.initCost;
					annealingAlg.currentPath.assign(annealingAlg.initPath.begin(), annealingAlg.initPath.end());

					annealingAlg.startAlgoritmBoltzmann(false, 0.95);
					boltzmanCost = annealingAlg.getCurentCost();
					kBoltz = annealingAlg.getNumberK();


					text = tabFile[fileIndex] + ";T0-AVG;" + std::to_string(j + 1) + ";" + std::to_string(TempStart) + ";" + std::to_string(startCost) + ";" + std::to_string(geoCost) + ";" + std::to_string(boltzmanCost) + ";" + std::to_string(kGeo) + ";" + std::to_string(kBoltz) + ";" + corectionVla;
					filewriter("TempTest.txt", text);
				}
			}
		}
		std::cout << "Koniec pomiaru";
		filewriter("TestStatus.txt", "Tryb pomiaru wyboru T0;Zakoñczono");
	}

	//startPath
	if (testingModeOn[1]) {
		std::cout << "Tryb pomiaru StartPath:\n";
		filewriter("TestStatus.txt", "Tryb pomiaru StartPath:\n");


		file_clear("StartPathTest.txt", "Plik;Tryb Œcie¿ki;Index;Koszt pocz¹tkowy;Koszt Geo;Koszt Boltzmana;Liczba stopni Geo; Liczba stopni Boltzman");

		int startCost;

		for (int fileIndex = 0; fileIndex < tabFileSize; fileIndex++) {

			kl.set(tabFile[fileIndex]);
			//kl.set(filePath + tabFile[fileIndex]);

			AS_Alg annealingAlg;
			annealingAlg.init(kl.tabLocation, kl.size, false, false, 1, 0.5, 1);

			std::vector<int> min_maxCost = annealingAlg.getMinMaxCost();
			std::cout << "Test pliku:" << tabFile[fileIndex] << " E1 " << std::endl;
			filewriter("TestStatus.txt", "Test pliku: " + tabFile[fileIndex] + " E1");
			for (int i = 0; i < liczbaPomiarow; i++) {
				annealingAlg.generateRandomPath();
				startCost = annealingAlg.getCurentCost();
				annealingAlg.currentTemperature = annealingAlg.initialTemperature;

				annealingAlg.startAlgoritmGeo(0.3, false, 0.95);
				geoCost = annealingAlg.getCurentCost();
				kGeo = annealingAlg.getNumberK();

				annealingAlg.currentTemperature = annealingAlg.initialTemperature;

				annealingAlg.startAlgoritmBoltzmann(false, 0.95);
				boltzmanCost = annealingAlg.getCurentCost();
				kBoltz = annealingAlg.getNumberK();

				text = tabFile[fileIndex] + ";Œcie¿ka Losowa;" + std::to_string(i + 1) + +";" + std::to_string(startCost) + ";" + std::to_string(geoCost) + ";" + std::to_string(boltzmanCost) + ";" + std::to_string(kGeo) + ";" + std::to_string(kBoltz) + ";0.0";
				filewriter("StartPathTest.txt", text);
			}

			std::string corectionVla;

			std::cout << "Test pliku:" << tabFile[fileIndex] << " E2 " << std::endl;
			filewriter("TestStatus.txt", "Test pliku: " + tabFile[fileIndex] + " E2");
			for (int j = 0; j < liczbaPomiarow; j++) {
				annealingAlg.generateRandomPath();
				startCost = annealingAlg.getCurentCost();

				annealingAlg.currentTemperature = annealingAlg.initialTemperature;

				annealingAlg.startAlgoritmGeo(0.3, false, 0.95);
				geoCost = annealingAlg.getCurentCost();
				kGeo = annealingAlg.getNumberK();

				annealingAlg.currentTemperature = annealingAlg.initialTemperature;

				annealingAlg.startAlgoritmBoltzmann(false, 0.95);
				boltzmanCost = annealingAlg.getCurentCost();
				kBoltz = annealingAlg.getNumberK();

				text = tabFile[fileIndex] + ";Zach³anna;" + std::to_string(j + 1) + ";" + std::to_string(startCost) + ";" + std::to_string(geoCost) + ";" + std::to_string(boltzmanCost) + ";" + std::to_string(kGeo) + ";" + std::to_string(kBoltz) + ";" + corectionVla;
				filewriter("StartPathTest.txt", text);
			}
		}
		std::cout << "Koniec pomiaru";
		filewriter("TestStatus.txt", "Tryb pomiaru StartPath;Zakoñczono");
	}

	//Boltzman VS Geo
	if (testingModeOn[2]) {
		std::cout << "Tryb pomiaru Trybu chlodzenia:\n";
		filewriter("TestStatus.txt", "Tryb pomiaru Trybu chlodzenia:\n");


		file_clear("ColingMode.txt", "Plik;Tryb Ch³odzenia;Index;Koszt pocz¹tkowy;Koszt Koñcowy;Liczba stopni;alfaVal");

		for (int fileIndex = 0; fileIndex < tabFileSize; fileIndex++) {

			kl.set(tabFile[fileIndex]);
			//kl.set(filePath + tabFile[fileIndex]);

			AS_Alg annealingAlg;
			annealingAlg.init(kl.tabLocation, kl.size, false, false, 1, 0.5, 1);

			startCost = annealingAlg.getCurentCost();

			std::string corectionVla;

			std::vector<int> min_maxCost = annealingAlg.getMinMaxCost();
			for (double j = 0.1; j <= 0.9; j = j + 0.1) {
				std::cout << "Test pliku:" << tabFile[fileIndex] << " E1 -  " << j << std::endl;
				filewriter("TestStatus.txt", "Test pliku: " + tabFile[fileIndex] + " E1 - " + std::to_string(j));
				corectionVla = std::to_string(j);
				for (int i = 0; i < liczbaPomiarow; i++) {

					annealingAlg.currentTemperature = annealingAlg.initialTemperature;
					annealingAlg.curentCost = annealingAlg.initCost;
					annealingAlg.currentPath.assign(annealingAlg.initPath.begin(), annealingAlg.initPath.end());

					annealingAlg.startAlgoritmGeo(j, false, 0.95);
					geoCost = annealingAlg.getCurentCost();
					kGeo = annealingAlg.getNumberK();


					text = tabFile[fileIndex] + ";Geo;" + std::to_string(i + 1) + +";" + std::to_string(startCost) + ";" + std::to_string(geoCost) + ";" + std::to_string(kGeo) + ";" + corectionVla;
					filewriter("ColingMode.txt", text);
				}
			}

			std::cout << "Test pliku:" << tabFile[fileIndex] << " E2 " << std::endl;
			filewriter("TestStatus.txt", "Test pliku: " + tabFile[fileIndex] + " E2");
			for (int j = 0; j < liczbaPomiarow; j++) {

				annealingAlg.currentTemperature = annealingAlg.initialTemperature;
				annealingAlg.curentCost = annealingAlg.initCost;
				annealingAlg.currentPath.assign(annealingAlg.initPath.begin(), annealingAlg.initPath.end());

				annealingAlg.startAlgoritmBoltzmann(false, 0.95);
				boltzmanCost = annealingAlg.getCurentCost();
				kBoltz = annealingAlg.getNumberK();

				text = tabFile[fileIndex] + ";Boltzman;" + std::to_string(j + 1) + ";" + std::to_string(startCost) + ";" + std::to_string(boltzmanCost) + ";" + std::to_string(kBoltz) + ";0.0";
				filewriter("ColingMode.txt", text);
			}
		}
		std::cout << "Koniec pomiaru";
		filewriter("TestStatus.txt", "Tryb pomiaru Trybu chlodzenia;Zakoñczono");
	}

	//Era Time
	if (testingModeOn[3]) {
		std::cout << "Tryb pomiaru D³ugoœci epoki:\n";
		filewriter("TestStatus.txt", "Tryb pomiaru D³ugoœci epoki:\n");

		file_clear("EraLong.txt", "Plik;D³ugoœæ Epoki;Index;Koszt pocz¹tkowy;Koszt Geo;Koszt Boltzmana;Liczba stopni Geo; Liczba stopni Boltzman");

		for (int fileIndex = 0; fileIndex < tabFileSize; fileIndex++) {

			kl.set(tabFile[fileIndex]);
			//kl.set(filePath + tabFile[fileIndex]);

			AS_Alg annealingAlg;
			annealingAlg.init(kl.tabLocation, kl.size, false, false, 1, 0.5, 1);

			startCost = annealingAlg.getCurentCost();


			std::vector<int> min_maxCost = annealingAlg.getMinMaxCost();

			std::cout << "Test pliku:" << tabFile[fileIndex] << " E1" << std::endl;
			filewriter("TestStatus.txt", "Test pliku: " + tabFile[fileIndex] + " E1");
			annealingAlg.setEraLong(2);//n/2
			for (int i = 0; i < liczbaPomiarow; i++) {

				annealingAlg.currentTemperature = annealingAlg.initialTemperature;
				annealingAlg.curentCost = annealingAlg.initCost;
				annealingAlg.currentPath.assign(annealingAlg.initPath.begin(), annealingAlg.initPath.end());

				annealingAlg.startAlgoritmGeo(0.3, false, 0.95);
				geoCost = annealingAlg.getCurentCost();
				kGeo = annealingAlg.getNumberK();

				annealingAlg.currentTemperature = annealingAlg.initialTemperature;
				annealingAlg.curentCost = annealingAlg.initCost;
				annealingAlg.currentPath.assign(annealingAlg.initPath.begin(), annealingAlg.initPath.end());

				annealingAlg.startAlgoritmBoltzmann(false, 0.95);
				boltzmanCost = annealingAlg.getCurentCost();
				kBoltz = annealingAlg.getNumberK();


				text = tabFile[fileIndex] + ";n/2;" + std::to_string(i + 1) + ";" + std::to_string(startCost) + ";" + std::to_string(geoCost) + ";" + std::to_string(boltzmanCost) + ";" + std::to_string(kGeo) + ";" + std::to_string(kBoltz);
				filewriter("EraLong.txt", text);
			}

			std::cout << "Test pliku:" << tabFile[fileIndex] << " E2" << std::endl;
			filewriter("TestStatus.txt", "Test pliku: " + tabFile[fileIndex] + " E2");
			annealingAlg.setEraLong(3);//n
			for (int i = 0; i < liczbaPomiarow; i++) {

				annealingAlg.currentTemperature = annealingAlg.initialTemperature;
				annealingAlg.curentCost = annealingAlg.initCost;
				annealingAlg.currentPath.assign(annealingAlg.initPath.begin(), annealingAlg.initPath.end());

				annealingAlg.startAlgoritmGeo(0.3, false, 0.95);
				geoCost = annealingAlg.getCurentCost();
				kGeo = annealingAlg.getNumberK();

				annealingAlg.currentTemperature = annealingAlg.initialTemperature;
				annealingAlg.curentCost = annealingAlg.initCost;
				annealingAlg.currentPath.assign(annealingAlg.initPath.begin(), annealingAlg.initPath.end());

				annealingAlg.startAlgoritmBoltzmann(false, 0.95);
				boltzmanCost = annealingAlg.getCurentCost();
				kBoltz = annealingAlg.getNumberK();


				text = tabFile[fileIndex] + ";n;" + std::to_string(i + 1) + ";" + std::to_string(startCost) + ";" + std::to_string(geoCost) + ";" + std::to_string(boltzmanCost) + ";" + std::to_string(kGeo) + ";" + std::to_string(kBoltz);
				filewriter("EraLong.txt", text);
			}

			std::cout << "Test pliku:" << tabFile[fileIndex] << " E3" << std::endl;
			filewriter("TestStatus.txt", "Test pliku: " + tabFile[fileIndex] + " E3");
			annealingAlg.setEraLong(4);//n*ln(n)
			for (int i = 0; i < liczbaPomiarow; i++) {

				annealingAlg.currentTemperature = annealingAlg.initialTemperature;
				annealingAlg.curentCost = annealingAlg.initCost;
				annealingAlg.currentPath.assign(annealingAlg.initPath.begin(), annealingAlg.initPath.end());

				annealingAlg.startAlgoritmGeo(0.3, false, 0.95);
				geoCost = annealingAlg.getCurentCost();
				kGeo = annealingAlg.getNumberK();

				annealingAlg.currentTemperature = annealingAlg.initialTemperature;
				annealingAlg.curentCost = annealingAlg.initCost;
				annealingAlg.currentPath.assign(annealingAlg.initPath.begin(), annealingAlg.initPath.end());

				annealingAlg.startAlgoritmBoltzmann(false, 0.95);
				boltzmanCost = annealingAlg.getCurentCost();
				kBoltz = annealingAlg.getNumberK();


				text = tabFile[fileIndex] + ";n*ln(n);" + std::to_string(i + 1) + ";" + std::to_string(startCost) + ";" + std::to_string(geoCost) + ";" + std::to_string(boltzmanCost) + ";" + std::to_string(kGeo) + ";" + std::to_string(kBoltz);
				filewriter("EraLong.txt", text);
			}

			std::cout << "Test pliku:" << tabFile[fileIndex] << " E4" << std::endl;
			filewriter("TestStatus.txt", "Test pliku: " + tabFile[fileIndex] + " E4");
			annealingAlg.setEraLong(5);//n*n/2
			for (int i = 0; i < liczbaPomiarow; i++) {

				annealingAlg.currentTemperature = annealingAlg.initialTemperature;
				annealingAlg.curentCost = annealingAlg.initCost;
				annealingAlg.currentPath.assign(annealingAlg.initPath.begin(), annealingAlg.initPath.end());

				annealingAlg.startAlgoritmGeo(0.3, false, 0.95);
				geoCost = annealingAlg.getCurentCost();
				kGeo = annealingAlg.getNumberK();

				annealingAlg.currentTemperature = annealingAlg.initialTemperature;
				annealingAlg.curentCost = annealingAlg.initCost;
				annealingAlg.currentPath.assign(annealingAlg.initPath.begin(), annealingAlg.initPath.end());

				annealingAlg.startAlgoritmBoltzmann(false, 0.95);
				boltzmanCost = annealingAlg.getCurentCost();
				kBoltz = annealingAlg.getNumberK();


				text = tabFile[fileIndex] + ";n*n/2;" + std::to_string(i + 1) + ";" + std::to_string(startCost) + ";" + std::to_string(geoCost) + ";" + std::to_string(boltzmanCost) + ";" + std::to_string(kGeo) + ";" + std::to_string(kBoltz);
				filewriter("EraLong.txt", text);
			}

			std::cout << "Test pliku:" << tabFile[fileIndex] << " E5" << std::endl;
			filewriter("TestStatus.txt", "Test pliku: " + tabFile[fileIndex] + " E5");
			annealingAlg.setEraLong(6);//n*n
			for (int i = 0; i < liczbaPomiarow; i++) {

				annealingAlg.currentTemperature = annealingAlg.initialTemperature;
				annealingAlg.curentCost = annealingAlg.initCost;
				annealingAlg.currentPath.assign(annealingAlg.initPath.begin(), annealingAlg.initPath.end());

				annealingAlg.startAlgoritmGeo(0.3, false, 0.95);
				geoCost = annealingAlg.getCurentCost();
				kGeo = annealingAlg.getNumberK();

				annealingAlg.currentTemperature = annealingAlg.initialTemperature;
				annealingAlg.curentCost = annealingAlg.initCost;
				annealingAlg.currentPath.assign(annealingAlg.initPath.begin(), annealingAlg.initPath.end());

				annealingAlg.startAlgoritmBoltzmann(false, 0.95);
				boltzmanCost = annealingAlg.getCurentCost();
				kBoltz = annealingAlg.getNumberK();


				text = tabFile[fileIndex] + ";n*n;" + std::to_string(i + 1) + ";" + std::to_string(startCost) + ";" + std::to_string(geoCost) + ";" + std::to_string(boltzmanCost) + ";" + std::to_string(kGeo) + ";" + std::to_string(kBoltz);
				filewriter("EraLong.txt", text);
			}



		}
		std::cout << "Koniec pomiaru";
		filewriter("TestStatus.txt", "Tryb pomiaru D³ugoœci epoki;Zakoñczono");
	}

	//startPath && selectVertex
	if (testingModeOn[4]) {
		std::cout << "Tryb pomiaru SelectVertex:\n";
		filewriter("TestStatus.txt", "Tryb pomiaru SelectVertex:");

		file_clear("SelectVertexMode.txt", "Plik;Tryb Wyboru wierzcho³ka;Tryb Generowania œcie¿ki;Index;Koszt pocz¹tkowy;Koszt Geo;Koszt Boltzmana;Liczba stopni Geo; Liczba stopni Boltzman");

		for (int fileIndex = 0; fileIndex < tabFileSize; fileIndex++) {

			kl.set(tabFile[fileIndex]);
			//kl.set(filePath + tabFile[fileIndex]);

			AS_Alg annealingAlg;
			annealingAlg.init(kl.tabLocation, kl.size, false, false, 1, 0.5, 1);



			std::vector<int> min_maxCost = annealingAlg.getMinMaxCost();
			std::cout << "Test pliku:" << tabFile[fileIndex] << " E1 " << std::endl;
			filewriter("TestStatus.txt", "Test pliku: " + tabFile[fileIndex] + " E1");
			for (int i = 0; i < liczbaPomiarow; i++) {
				annealingAlg.generateRandomPath();
				annealingAlg.currentTemperature = annealingAlg.initialTemperature;

				startCost = annealingAlg.getCurentCost();

				annealingAlg.startAlgoritmGeo(0.3, false, 0.95);
				geoCost = annealingAlg.getCurentCost();
				kGeo = annealingAlg.getNumberK();

				annealingAlg.currentTemperature = annealingAlg.initialTemperature;

				annealingAlg.startAlgoritmBoltzmann(false, 0.95);
				boltzmanCost = annealingAlg.getCurentCost();
				kBoltz = annealingAlg.getNumberK();

				text = tabFile[fileIndex] + ";Œcie¿ka Losowa;Losowo 2 wierzcho³ki;" + std::to_string(i + 1) + +";" + std::to_string(startCost) + ";" + std::to_string(geoCost) + ";" + std::to_string(boltzmanCost) + ";" + std::to_string(kGeo) + ";" + std::to_string(kBoltz);
				filewriter("SelectVertexMode.txt", text);
			}

			std::string corectionVla;

			std::cout << "Test pliku:" << tabFile[fileIndex] << " E2 " << std::endl;
			filewriter("TestStatus.txt", "Test pliku: " + tabFile[fileIndex] + " E2");
			for (int j = 0; j < liczbaPomiarow; j++) {
				annealingAlg.generateRandomPath();

				startCost = annealingAlg.getCurentCost();

				annealingAlg.currentTemperature = annealingAlg.initialTemperature;

				annealingAlg.startAlgoritmGeo(0.3, false, 0.95);
				geoCost = annealingAlg.getCurentCost();
				kGeo = annealingAlg.getNumberK();

				annealingAlg.currentTemperature = annealingAlg.initialTemperature;

				annealingAlg.startAlgoritmBoltzmann(false, 0.95);
				boltzmanCost = annealingAlg.getCurentCost();
				kBoltz = annealingAlg.getNumberK();

				text = tabFile[fileIndex] + ";Zach³anna;Losowo 2 wierzcho³ki;" + std::to_string(j + 1) + ";" + std::to_string(startCost) + ";" + std::to_string(geoCost) + ";" + std::to_string(boltzmanCost) + ";" + std::to_string(kGeo) + ";" + std::to_string(kBoltz);
				filewriter("SelectVertexMode.txt", text);
			}

		}

		//Na lewo
		for (int fileIndex = 0; fileIndex < tabFileSize; fileIndex++) {

			kl.set(tabFile[fileIndex]);
			//kl.set(filePath + tabFile[fileIndex]);

			AS_Alg annealingAlg;
			annealingAlg.init(kl.tabLocation, kl.size, false, false, 1, 0.5, 1);

			startCost = annealingAlg.getCurentCost();

			std::vector<int> min_maxCost = annealingAlg.getMinMaxCost();
			std::cout << "Test pliku - P2:" << tabFile[fileIndex] << " E1 " << std::endl;
			filewriter("TestStatus.txt", "Test pliku - P2: " + tabFile[fileIndex] + " E1");
			for (int i = 0; i < liczbaPomiarow; i++) {
				annealingAlg.generateRandomPath();

				startCost = annealingAlg.getCurentCost();

				annealingAlg.currentTemperature = annealingAlg.initialTemperature;

				annealingAlg.startAlgoritmGeo(0.3, true, 0.95);
				geoCost = annealingAlg.getCurentCost();
				kGeo = annealingAlg.getNumberK();

				annealingAlg.currentTemperature = annealingAlg.initialTemperature;

				annealingAlg.startAlgoritmBoltzmann(true, 0.95);
				boltzmanCost = annealingAlg.getCurentCost();
				kBoltz = annealingAlg.getNumberK();

				text = tabFile[fileIndex] + ";Œcie¿ka Losowa;Wymiana z lewym s¹siadem;" + std::to_string(i + 1) + +";" + std::to_string(startCost) + ";" + std::to_string(geoCost) + ";" + std::to_string(boltzmanCost) + ";" + std::to_string(kGeo) + ";" + std::to_string(kBoltz);
				filewriter("SelectVertexMode.txt", text);
			}

			std::cout << "Test pliku - P2:" << tabFile[fileIndex] << " E2" << std::endl;
			filewriter("TestStatus.txt", "Test pliku - P2: " + tabFile[fileIndex] + " E2");
			for (int j = 0; j < liczbaPomiarow; j++) {
				annealingAlg.generateRandomPath();

				startCost = annealingAlg.getCurentCost();

				annealingAlg.currentTemperature = annealingAlg.initialTemperature;

				annealingAlg.startAlgoritmGeo(0.3, true, 0.95);
				geoCost = annealingAlg.getCurentCost();
				kGeo = annealingAlg.getNumberK();

				annealingAlg.currentTemperature = annealingAlg.initialTemperature;

				annealingAlg.startAlgoritmBoltzmann(true, 0.95);
				boltzmanCost = annealingAlg.getCurentCost();
				kBoltz = annealingAlg.getNumberK();

				text = tabFile[fileIndex] + ";Zach³anna;Wymiana z lewym s¹siadem;" + std::to_string(j + 1) + ";" + std::to_string(startCost) + ";" + std::to_string(geoCost) + ";" + std::to_string(boltzmanCost) + ";" + std::to_string(kGeo) + ";" + std::to_string(kBoltz);
				filewriter("SelectVertexMode.txt", text);
			}
		}
		std::cout << "Koniec pomiaru";
		filewriter("TestStatus.txt", "Tryb pomiaru SelectVertex;Zakoñczono");
	}

	//propabylyty accept test
	if (testingModeOn[5]) {
		std::cout << "Tryb pomiaru Poziomu akceptacji:\n";
		filewriter("TestStatus.txt", "Tryb pomiaru poziomu akceptacji:\n");


		file_clear("AcceptLevelTest.txt", "Plik;Poziom Akceptacji;Index;Koszt Geo;Koszt Boltzmanna");

		for (int fileIndex = 0; fileIndex < tabFileSize; fileIndex++) {

			kl.set(tabFile[fileIndex]);
			//kl.set(filePath + tabFile[fileIndex]);

			AS_Alg annealingAlg;
			annealingAlg.init(kl.tabLocation, kl.size, false, false, 1, 0.5, 1);

			startCost = annealingAlg.getCurentCost();

			std::string corectionVla;

			std::vector<int> min_maxCost = annealingAlg.getMinMaxCost();
			double tab[] = { 0.9, 0.95, 0.99, 0.999 };
			int tabsize = 4;

			for (int j = 0; j < tabsize; j++) {
				std::cout << "Test pliku:" << tabFile[fileIndex] << " E1 -  " << j << std::endl;
				filewriter("TestStatus.txt", "Test pliku: " + tabFile[fileIndex] + " E1 - " + std::to_string(j));

				corectionVla = std::to_string(0.3);
				for (int i = 0; i < liczbaPomiarow; i++) {

					annealingAlg.currentTemperature = annealingAlg.initialTemperature;
					annealingAlg.curentCost = annealingAlg.initCost;
					annealingAlg.currentPath.assign(annealingAlg.initPath.begin(), annealingAlg.initPath.end());

					annealingAlg.startAlgoritmGeo(0.3, false, tab[j]);
					geoCost = annealingAlg.getCurentCost();

					annealingAlg.currentTemperature = annealingAlg.initialTemperature;
					annealingAlg.curentCost = annealingAlg.initCost;
					annealingAlg.currentPath.assign(annealingAlg.initPath.begin(), annealingAlg.initPath.end());

					annealingAlg.startAlgoritmBoltzmann(false, tab[j]);
					boltzmanCost = annealingAlg.getCurentCost();

					text = tabFile[fileIndex] + ";" + std::to_string(tab[j]) + ";" + std::to_string(i + 1) + ";" + std::to_string(geoCost) + ";" + std::to_string(boltzmanCost);
					filewriter("AcceptLevelTest.txt", text);
				}
			}
		}
		std::cout << "Koniec pomiaru";
		filewriter("TestStatus.txt", "Tryb pomiaru Trybu chlodzenia;Zakoñczono");
	}


}*/

/*void Pomiar::autoTest2() {
	double timeStartGeo = 0;
	double timeEndGeo = 0;
	double timeStartBoltz = 0;
	double timeEndBoltz = 0;

	double memoryStartGeo = 0;
	double memoryEndGeo = 0;
	double memoryStartBoltz = 0;
	double memoryEndBoltz = 0;

	std::string tabFile2[] = {//ATSP
		"Pliki Do testów/ATSP/br17.txt",
		"Pliki Do testów/ATSP/ftv44.txt",
		"Pliki Do testów/ATSP/ftv70.txt",
		"Pliki Do testów/ATSP/ftv170.txt",
		"Pliki Do testów/ATSP/rbg443.txt",
	};
	std::string tabFile[] = {//TSP
		"Pliki Do testów/TSP/berlin52.tsp",
		"Pliki Do testów/TSP/eil76.tsp",
		"Pliki Do testów/TSP/kroA100.tsp",
		"Pliki Do testów/TSP/brg180.tsp",
		"Pliki Do testów/TSP/a280.tsp",
	};




	GeneticAlgoritm genAlg;
	KomivoyagerLocation kl;
	StartCounter();

	int startSize = 3000;
	int wielkoscInstancji = 8000;
	int jump = 500;

	int liczbaInstancji = 1;
	int liczbaPowtorzenPomiaru = 1;

	int geoK;
	int boltzk;

	std::string text;

	file_clear("TimeTest.txt", "Wielkoœæ instancji;Numer Pomiaru;Zakres Wartoœci;Czas Geo;Czas Boltzman");
	file_clear("InitTimeTest.txt", "Wielkoœæ instancji;Numer Pomiaru;Zakres Wartoœci;Czas Geo;Czas Boltzman");

	for (int instantSize = startSize; instantSize <= wielkoscInstancji; instantSize = instantSize + jump) {
		for (int i = 0; i < liczbaInstancji; i++) {
			kl.generate(instantSize, 1, 10, false);
			std::cout << "Wielkosc Instancji = " << instantSize << " Powturzenie Instancji = " << i << " Zakres pomiaru = 1-10\n";

			double timeStartTest = GetCounter();
			annealingAlg.init(kl.tabLocation, kl.size, true, false, 0.1, 0.3, 6);
			double timeEndTest = GetCounter();

			text = std::to_string(instantSize) + ";" + std::to_string(i) + ";1-10;" + std::to_string(timeEndTest - timeStartTest);
			filewriter("InitTimeTest.txt", text);

			//std::cout << "Init Temp = " << annealingAlg.initialTemperature << std::endl;

			timeStartGeo = GetCounter();
			for (int j = 0; j < liczbaPowtorzenPomiaru; j++) {
				annealingAlg.currentTemperature = annealingAlg.initialTemperature;
				annealingAlg.startAlgoritmGeo(0.5, false, 0.95);
			}
			timeEndGeo = GetCounter();

			geoK = annealingAlg.getNumberK();

			timeStartBoltz = GetCounter();
			for (int j = 0; j < liczbaPowtorzenPomiaru; j++) {
				annealingAlg.currentTemperature = annealingAlg.initialTemperature;
				annealingAlg.startAlgoritmBoltzmann(false, 0.95);
			}
			timeEndBoltz = GetCounter();

			boltzk = annealingAlg.getNumberK();

			//std::cout << "Time Geo = " << timeEndGeo - timeStartGeo << " - Knumber = " << geoK << std::endl;
			//std::cout << "Time Boltz = " << timeEndBoltz - timeStartBoltz << " - Knumber = " << boltzk << std::endl;

			text = std::to_string(instantSize) + ";" + std::to_string(i) + ";1-10;" + std::to_string((timeEndGeo - timeStartGeo) / liczbaPowtorzenPomiaru) + ";" + std::to_string((timeEndBoltz - timeStartBoltz) / liczbaPowtorzenPomiaru);
			filewriter("TimeTest.txt", text);

			kl.generate(instantSize, 11, 10000, false);
			std::cout << "Wielkosc Instancji = " << instantSize << " Powturzenie Instancji = " << i << " Zakres pomiaru = 11-10 000\n";

			timeStartTest = GetCounter();
			annealingAlg.init(kl.tabLocation, kl.size, true, false, 0.1, 0.3, 6);
			timeEndTest = GetCounter();

			text = std::to_string(instantSize) + ";" + std::to_string(i) + ";11-10 000;" + std::to_string(timeEndTest - timeStartTest);
			filewriter("InitTimeTest.txt", text);

			//std::cout << "Init Temp = " << annealingAlg.initialTemperature << std::endl;

			timeStartGeo = GetCounter();
			for (int j = 0; j < liczbaPowtorzenPomiaru; j++) {
				annealingAlg.currentTemperature = annealingAlg.initialTemperature;
				annealingAlg.startAlgoritmGeo(0.5, false, 0.95);
			}
			timeEndGeo = GetCounter();

			geoK = annealingAlg.getNumberK();

			timeStartBoltz = GetCounter();
			for (int j = 0; j < liczbaPowtorzenPomiaru; j++) {
				annealingAlg.currentTemperature = annealingAlg.initialTemperature;
				annealingAlg.startAlgoritmBoltzmann(false, 0.95);
			}
			timeEndBoltz = GetCounter();

			boltzk = annealingAlg.getNumberK();

			//std::cout << "Time Geo = " << timeEndGeo - timeStartGeo << " - Knumber = " << geoK << std::endl;
			//std::cout << "Time Boltz = " << timeEndBoltz - timeStartBoltz << " - Knumber = " << boltzk << std::endl;

			text = std::to_string(instantSize) + ";" + std::to_string(i) + ";11-10 000;" + std::to_string((timeEndGeo - timeStartGeo) / liczbaPowtorzenPomiaru) + ";" + std::to_string((timeEndBoltz - timeStartBoltz) / liczbaPowtorzenPomiaru);
			filewriter("TimeTest.txt", text);

			kl.generate(instantSize, 10001, 10000000, false);
			std::cout << "Wielkosc Instancji = " << instantSize << " Powturzenie Instancji = " << i << " Zakres pomiaru = 10 001-10 000 000\n";

			timeStartTest = GetCounter();
			annealingAlg.init(kl.tabLocation, kl.size, true, false, 0.1, 0.3, 6);
			timeEndTest = GetCounter();

			text = std::to_string(instantSize) + ";" + std::to_string(i) + ";10 001-10 000 000;" + std::to_string(timeEndTest - timeStartTest);
			filewriter("InitTimeTest.txt", text);

			//std::cout << "Init Temp = " << annealingAlg.initialTemperature << std::endl;

			timeStartGeo = GetCounter();
			for (int j = 0; j < liczbaPowtorzenPomiaru; j++) {
				annealingAlg.currentTemperature = annealingAlg.initialTemperature;
				annealingAlg.startAlgoritmGeo(0.5, false, 0.95);
			}
			timeEndGeo = GetCounter();

			geoK = annealingAlg.getNumberK();

			timeStartBoltz = GetCounter();
			for (int j = 0; j < liczbaPowtorzenPomiaru; j++) {
				annealingAlg.currentTemperature = annealingAlg.initialTemperature;
				annealingAlg.startAlgoritmBoltzmann(false, 0.95);
			}
			timeEndBoltz = GetCounter();

			boltzk = annealingAlg.getNumberK();

			//std::cout << "Time Geo = " << timeEndGeo - timeStartGeo << " - Knumber = " << geoK << std::endl;
			//std::cout << "Time Boltz = " << timeEndBoltz - timeStartBoltz << " - Knumber = " << boltzk << std::endl;

			text = std::to_string(instantSize) + ";" + std::to_string(i) + ";10 001-10 000 000;" + std::to_string((timeEndGeo - timeStartGeo) / liczbaPowtorzenPomiaru) + ";" + std::to_string((timeEndBoltz - timeStartBoltz) / liczbaPowtorzenPomiaru);
			filewriter("TimeTest.txt", text);
		}

	}
}*/

void Pomiar::autoTest3() {
	double timeStart = 0;
	double timeEnd = 0;

	std::string tabFileATSP[] = {//ATSP
		"Pliki Do testów/ATSP/br17.txt",
		"Pliki Do testów/ATSP/ftv44.txt",
		"Pliki Do testów/ATSP/ftv70.txt",
		"Pliki Do testów/ATSP/ftv170.txt",
		"Pliki Do testów/ATSP/rbg443.txt",
	};
	std::string tabOutFileATSP[] = {//ATSPout
		"Pliki Do testów/out/ATSP/br17",
		"Pliki Do testów/out/ATSP/ftv44",
		"Pliki Do testów/out/ATSP/ftv70",
		"Pliki Do testów/out/ATSP/ftv170",
		"Pliki Do testów/out/ATSP/rbg443",
	};
	int configATSPtab[][3] = {
	{12, 4, 39},
	{30, 10, 1613},
	{50, 15, 1950},
	{120, 40, 2755},
	{300, 100, 2720}
	};
	std::string tabFileTSP[] = {//TSP
		"Pliki Do testów/TSP/berlin52.tsp",
		"Pliki Do testów/TSP/eil76.tsp",
		"Pliki Do testów/TSP/kroA100.tsp",
		"Pliki Do testów/TSP/brg180.tsp",
		"Pliki Do testów/TSP/a280.tsp",
	};
	std::string tabOutFileTSP[] = {//TSPout
		"Pliki Do testów/out/TSP/berlin52",
		"Pliki Do testów/out/TSP/eil76",
		"Pliki Do testów/out/TSP/kroA100",
		"Pliki Do testów/out/TSP/brg180",
		"Pliki Do testów/out/TSP/a280",
	};
	int configTSPtab[][3] = {
	{35, 12, 7542},
	{50, 16, 538},
	{70, 22, 21282},
	{120, 40, 1950},
	{200, 60, 2579}
	};

	bool mode[]{
		false,//Zmienna wielkoœæ populacji
		true,//Wszystko off
		true,//Zmienna liczba krzy¿owañ
		true,//Zmienna liczba mutacji
		true,//Tryb selekcji Najlepsze
		true,//Tryb selekcji losowo
		true,//Tryb sukcesji 90/10
		true,//Tryb sukcesji 50/50
		true,//Tryb mutacji fragment
		true,//Tryb mutacji 2 zamiana
		true,//Tryb krzy¿owania 50/50
		true,//Tryb krzy¿owania 25/75
		true//Zmienna wartoœæ pocz¹tkowa mutacji
	};



	GeneticAlgoritm genAlg;
	KomivoyagerLocation kl;
	StartCounter();

	std::string text;

	int repeatNumber = 3;

	//file_clear("TestATSP.txt", "Tryb Testu;Nazwa Instancji; Numer Pomiaru; Czas Pomiaru; Koszt Uzyskany; Koszt Oczekiwany; Typ zakoñczenia");
	//file_clear("TestTSP.txt", "Tryb Testu;Nazwa Instancji;Numer Pomiaru;Czas Pomiaru;Koszt Uzyskany;Koszt Oczekiwany;Typ zakoñczenia");

	//Zmenna wielkoœæ populacji w³¹czona
	if (mode[0]) {
		std::cout << "Zmenna wielkoœæ populacji" << std::endl;

		for (int i = 0; i < tabFileATSP->size(); i++) {
			kl.set(tabFileATSP[i]);
			for (int j = 0; j < repeatNumber; j++) {
				std::cout << "Start Pomiaru " << tabFileATSP[i] << " - Numer Pomiaru - " << (j + 1) << std::endl;
				genAlg.init(kl.tabLocation, kl.size, configATSPtab[i][0], configATSPtab[i][1], 0.3);
				timeStart = GetCounter();
				genAlg.startAlgoritm(true, true, true, 0.3, true, 500, configATSPtab[i][2], tabOutFileATSP[i] + "-" + std::to_string(j) + "_Zmienna wielkoœæ populacji.txt", true, true, false, false);
				timeEnd = GetCounter();

				text = "Test Zmiennej wielkoœci populacji;" + tabFileATSP[i] + ";" + std::to_string(j) + ";" + std::to_string(timeEnd - timeStart) + ";" + std::to_string(genAlg.bestCost) + ";" + std::to_string(configATSPtab[i][2]) + ";" + genAlg.endType;
				filewriter("TestATSP.txt", text);
			}

			kl.set(tabFileTSP[i]);
			for (int j = 0; j < repeatNumber; j++) {
				std::cout << "Start Pomiaru " << tabFileTSP[i] << " - Numer Pomiaru - " << (j + 1) << std::endl;
				genAlg.init(kl.tabLocation, kl.size, configTSPtab[i][0], configTSPtab[i][1], 0.3);
				//(bool croosMode, bool mutateMode, bool succesionMode, double succesionProcent, bool sellectionMode, int maxIterationWithoutBetterVall, int expectedPathCost, std::string fileName, bool descriptionAdd);
				timeStart = GetCounter();
				genAlg.startAlgoritm(true, true, true, 0.3, true, 500, configTSPtab[i][2], tabOutFileTSP[i] + "-" + std::to_string(j) + "_Zmienna wielkoœæ populacji.txt", true, true, false, false);
				timeEnd = GetCounter();

				text = "Test Zmiennej wielkoœci populacji;" + tabFileTSP[i] + ";" + std::to_string(j) + ";" + std::to_string(timeEnd - timeStart) + ";" + std::to_string(genAlg.bestCost) + ";" + std::to_string(configTSPtab[i][2]) + ";" + genAlg.endType;
				filewriter("TestTSP.txt", text);
			}
		}
	}
	

	

	//Zmenna Wszystkie OFF
	if (mode[1]) {
		std::cout << "Wszystkie zmienne wy³¹czone" << std::endl;

		for (int i = 0; i < tabFileATSP->size(); i++) {
			kl.set(tabFileATSP[i]);
			for (int j = 0; j < repeatNumber; j++) {
				std::cout << "Start Pomiaru " << tabFileATSP[i] << " - Numer Pomiaru - " << (j + 1) << std::endl;
				genAlg.init(kl.tabLocation, kl.size, configATSPtab[i][0], configATSPtab[i][1], 0.3);
				timeStart = GetCounter();
				genAlg.startAlgoritm(true, true, true, 0.3, true, 500, configATSPtab[i][2], tabOutFileATSP[i] + "-" + std::to_string(j) + "_Test Wartoœci zmiennych OFF.txt", true, false, false, false);
				timeEnd = GetCounter();

				text = "Test Wartoœci zmiennych OFF;" + tabFileATSP[i] + ";" + std::to_string(j) + ";" + std::to_string(timeEnd - timeStart) + ";" + std::to_string(genAlg.bestCost) + ";" + std::to_string(configATSPtab[i][2]) + ";" + genAlg.endType;
				filewriter("TestATSP.txt", text);
			}

			kl.set(tabFileTSP[i]);
			for (int j = 0; j < repeatNumber; j++) {
				std::cout << "Start Pomiaru " << tabFileTSP[i] << " - Numer Pomiaru - " << (j + 1) << std::endl;
				genAlg.init(kl.tabLocation, kl.size, configTSPtab[i][0], configTSPtab[i][1], 0.3);
				//(bool croosMode, bool mutateMode, bool succesionMode, double succesionProcent, bool sellectionMode, int maxIterationWithoutBetterVall, int expectedPathCost, std::string fileName, bool descriptionAdd);
				timeStart = GetCounter();
				genAlg.startAlgoritm(true, true, true, 0.3, true, 500, configTSPtab[i][2], tabOutFileTSP[i] + "-" + std::to_string(j) + "_Test Wartoœci zmiennych OFF.txt", true, false, false, false);
				timeEnd = GetCounter();

				text = "Test Wartoœci zmiennych OFF;" + tabFileTSP[i] + ";" + std::to_string(j) + ";" + std::to_string(timeEnd - timeStart) + ";" + std::to_string(genAlg.bestCost) + ";" + std::to_string(configTSPtab[i][2]) + ";" + genAlg.endType;
				filewriter("TestTSP.txt", text);
			}
		}
	}

	//Zmienna liczba krzy¿owañ ON
	if (mode[2]) {

		std::cout << "Zmienna liczba krzy¿owañ" << std::endl;

		for (int i = 0; i < tabFileATSP->size(); i++) {
			kl.set(tabFileATSP[i]);
			for (int j = 0; j < repeatNumber; j++) {
				std::cout << "Start Pomiaru " << tabFileATSP[i] << " - Numer Pomiaru - " << (j + 1) << std::endl;
				genAlg.init(kl.tabLocation, kl.size, configATSPtab[i][0], configATSPtab[i][1], 0.3);
				timeStart = GetCounter();
				genAlg.startAlgoritm(true, true, true, 0.3, true, 500, configATSPtab[i][2], tabOutFileATSP[i] + "-" + std::to_string(j) + "_Zmienna liczba krzyrzowañ ON.txt", true, false, true, false);
				timeEnd = GetCounter();

				text = "Zmienna liczba krzyrzowañ ON;" + tabFileATSP[i] + ";" + std::to_string(j) + ";" + std::to_string(timeEnd - timeStart) + ";" + std::to_string(genAlg.bestCost) + ";" + std::to_string(configATSPtab[i][2]) + ";" + genAlg.endType;
				filewriter("TestATSP.txt", text);
			}

			kl.set(tabFileTSP[i]);
			for (int j = 0; j < repeatNumber; j++) {
				std::cout << "Start Pomiaru " << tabFileTSP[i] << " - Numer Pomiaru - " << (j + 1) << std::endl;
				genAlg.init(kl.tabLocation, kl.size, configTSPtab[i][0], configTSPtab[i][1], 0.3);
				//(bool croosMode, bool mutateMode, bool succesionMode, double succesionProcent, bool sellectionMode, int maxIterationWithoutBetterVall, int expectedPathCost, std::string fileName, bool descriptionAdd);
				timeStart = GetCounter();
				genAlg.startAlgoritm(true, true, true, 0.3, true, 500, configTSPtab[i][2], tabOutFileTSP[i] + "-" + std::to_string(j) + "_Zmienna liczba krzyrzowañ ON.txt", true, false, true, false);
				timeEnd = GetCounter();

				text = "Zmienna liczba krzyrzowañ ON;" + tabFileTSP[i] + ";" + std::to_string(j) + ";" + std::to_string(timeEnd - timeStart) + ";" + std::to_string(genAlg.bestCost) + ";" + std::to_string(configTSPtab[i][2]) + ";" + genAlg.endType;
				filewriter("TestTSP.txt", text);
			}
		}
	}

	//Zmienna liczba mutacji ON
	if (mode[3]) {
		std::cout << "Zmienna liczba mutacji" << std::endl;

		for (int i = 0; i < tabFileATSP->size(); i++) {
			kl.set(tabFileATSP[i]);
			for (int j = 0; j < repeatNumber; j++) {
				std::cout << "Start Pomiaru " << tabFileATSP[i] << " - Numer Pomiaru - " << (j + 1) << std::endl;
				genAlg.init(kl.tabLocation, kl.size, configATSPtab[i][0], configATSPtab[i][1], 0.3);
				timeStart = GetCounter();
				genAlg.startAlgoritm(true, true, true, 0.3, true, 500, configATSPtab[i][2], tabOutFileATSP[i] + "-" + std::to_string(j) + "_Zmienna liczba mutacji.txt", true, false, false, true);
				timeEnd = GetCounter();

				text = "Zmienna liczba mutacji;" + tabFileATSP[i] + ";" + std::to_string(j) + ";" + std::to_string(timeEnd - timeStart) + ";" + std::to_string(genAlg.bestCost) + ";" + std::to_string(configATSPtab[i][2]) + ";" + genAlg.endType;
				filewriter("TestATSP.txt", text);
			}

			kl.set(tabFileTSP[i]);
			for (int j = 0; j < repeatNumber; j++) {
				std::cout << "Start Pomiaru " << tabFileTSP[i] << " - Numer Pomiaru - " << (j + 1) << std::endl;
				genAlg.init(kl.tabLocation, kl.size, configTSPtab[i][0], configTSPtab[i][1], 0.3);
				//(bool croosMode, bool mutateMode, bool succesionMode, double succesionProcent, bool sellectionMode, int maxIterationWithoutBetterVall, int expectedPathCost, std::string fileName, bool descriptionAdd);
				timeStart = GetCounter();
				genAlg.startAlgoritm(true, true, true, 0.3, true, 500, configTSPtab[i][2], tabOutFileTSP[i] + "-" + std::to_string(j) + "_Zmienna liczba mutacji.txt", true, false, false, true);
				timeEnd = GetCounter();

				text = "Zmienna liczba mutacji;" + tabFileTSP[i] + ";" + std::to_string(j) + ";" + std::to_string(timeEnd - timeStart) + ";" + std::to_string(genAlg.bestCost) + ";" + std::to_string(configTSPtab[i][2]) + ";" + genAlg.endType;
				filewriter("TestTSP.txt", text);
			}
		}
	}

	

	//Tryby sukceji Najlepsze
	if (mode[4]) {
		std::cout << "Tryby sukceji Najlepsze" << std::endl;
		for (int i = 0; i < tabFileATSP->size(); i++) {
			kl.set(tabFileATSP[i]);
			for (int j = 0; j < repeatNumber; j++) {
				std::cout << "Start Pomiaru " << tabFileATSP[i] << " - Numer Pomiaru - " << (j + 1) << std::endl;
				genAlg.init(kl.tabLocation, kl.size, configATSPtab[i][0], configATSPtab[i][1], 0.3);
				timeStart = GetCounter();
				genAlg.startAlgoritm(true, true, true, 0.3, true, 500, configATSPtab[i][2], tabOutFileATSP[i] + "-" + std::to_string(j) + "_Sukcesja Najlepszych.txt", true, false, false, false);
				timeEnd = GetCounter();

				text = "Sukcesja Najlepszych;" + tabFileATSP[i] + ";" + std::to_string(j) + ";" + std::to_string(timeEnd - timeStart) + ";" + std::to_string(genAlg.bestCost) + ";" + std::to_string(configATSPtab[i][2]) + ";" + genAlg.endType;
				filewriter("TestATSP.txt", text);
			}

			kl.set(tabFileTSP[i]);
			for (int j = 0; j < repeatNumber; j++) {
				std::cout << "Start Pomiaru " << tabFileTSP[i] << " - Numer Pomiaru - " << (j + 1) << std::endl;
				genAlg.init(kl.tabLocation, kl.size, configTSPtab[i][0], configTSPtab[i][1], 0.3);
				//(bool croosMode, bool mutateMode, bool succesionMode, double succesionProcent, bool sellectionMode, int maxIterationWithoutBetterVall, int expectedPathCost, std::string fileName, bool descriptionAdd);
				timeStart = GetCounter();
				genAlg.startAlgoritm(true, true, true, 0.3, true, 500, configTSPtab[i][2], tabOutFileTSP[i] + "-" + std::to_string(j) + "_Sukcesja Najlepszych.txt", true, false, false, false);
				timeEnd = GetCounter();

				text = "Sukcesja Najlepszych;" + tabFileTSP[i] + ";" + std::to_string(j) + ";" + std::to_string(timeEnd - timeStart) + ";" + std::to_string(genAlg.bestCost) + ";" + std::to_string(configTSPtab[i][2]) + ";" + genAlg.endType;
				filewriter("TestTSP.txt", text);
			}
		}
	}


	//Tryby sukceji Losowych
	if (mode[5]) {
		std::cout << "Tryby sukceji Losowych" << std::endl;

		for (int i = 0; i < tabFileATSP->size(); i++) {
			kl.set(tabFileATSP[i]);
			for (int j = 0; j < repeatNumber; j++) {
				std::cout << "Start Pomiaru " << tabFileATSP[i] << " - Numer Pomiaru - " << (j + 1) << std::endl;
				genAlg.init(kl.tabLocation, kl.size, configATSPtab[i][0], configATSPtab[i][1], 0.3);
				timeStart = GetCounter();
				genAlg.startAlgoritm(true, true, false, 0.3, true, 500, configATSPtab[i][2], tabOutFileATSP[i] + "-" + std::to_string(j) + "_Sukcesja Losowych.txt", true, false, false, false);
				timeEnd = GetCounter();

				text = "Sukcesja Losowych;" + tabFileATSP[i] + ";" + std::to_string(j) + ";" + std::to_string(timeEnd - timeStart) + ";" + std::to_string(genAlg.bestCost) + ";" + std::to_string(configATSPtab[i][2]) + ";" + genAlg.endType;
				filewriter("TestATSP.txt", text);
			}

			kl.set(tabFileTSP[i]);
			for (int j = 0; j < repeatNumber; j++) {
				std::cout << "Start Pomiaru " << tabFileTSP[i] << " - Numer Pomiaru - " << (j + 1) << std::endl;
				genAlg.init(kl.tabLocation, kl.size, configTSPtab[i][0], configTSPtab[i][1], 0.3);
				//(bool croosMode, bool mutateMode, bool succesionMode, double succesionProcent, bool sellectionMode, int maxIterationWithoutBetterVall, int expectedPathCost, std::string fileName, bool descriptionAdd);
				timeStart = GetCounter();
				genAlg.startAlgoritm(true, true, false, 0.3, true, 500, configTSPtab[i][2], tabOutFileTSP[i] + "-" + std::to_string(j) + "_Sukcesja Losowych.txt", true, false, false, false);
				timeEnd = GetCounter();

				text = "Sukcesja Losowych;" + tabFileTSP[i] + ";" + std::to_string(j) + ";" + std::to_string(timeEnd - timeStart) + ";" + std::to_string(genAlg.bestCost) + ";" + std::to_string(configTSPtab[i][2]) + ";" + genAlg.endType;
				filewriter("TestTSP.txt", text);
			}
		}
	}

	//Tryby selekcji 10/90
	if (mode[6]) {
		std::cout << "Tryby selekcji 10/90" << std::endl;

		for (int i = 0; i < tabFileATSP->size(); i++) {
			kl.set(tabFileATSP[i]);
			for (int j = 0; j < repeatNumber; j++) {
				std::cout << "Start Pomiaru " << tabFileATSP[i] << " - Numer Pomiaru - " << (j + 1) << std::endl;
				genAlg.init(kl.tabLocation, kl.size, configATSPtab[i][0], configATSPtab[i][1], 0.3);
				timeStart = GetCounter();
				genAlg.startAlgoritm(true, true, true, 0.3, true, 500, configATSPtab[i][2], tabOutFileATSP[i] + "-" + std::to_string(j) + "_Tryb Selekcji 10/90.txt", true, false, false, false);
				timeEnd = GetCounter();

				text = "Tryb Selekcji 10/90;" + tabFileATSP[i] + ";" + std::to_string(j) + ";" + std::to_string(timeEnd - timeStart) + ";" + std::to_string(genAlg.bestCost) + ";" + std::to_string(configATSPtab[i][2]) + ";" + genAlg.endType;
				filewriter("TestATSP.txt", text);
			}

			kl.set(tabFileTSP[i]);
			for (int j = 0; j < repeatNumber; j++) {
				std::cout << "Start Pomiaru " << tabFileTSP[i] << " - Numer Pomiaru - " << (j + 1) << std::endl;
				genAlg.init(kl.tabLocation, kl.size, configTSPtab[i][0], configTSPtab[i][1], 0.3);
				//(bool croosMode, bool mutateMode, bool succesionMode, double succesionProcent, bool sellectionMode, int maxIterationWithoutBetterVall, int expectedPathCost, std::string fileName, bool descriptionAdd);
				timeStart = GetCounter();
				genAlg.startAlgoritm(true, true, true, 0.3, true, 500, configTSPtab[i][2], tabOutFileTSP[i] + "-" + std::to_string(j) + "_Tryb Selekcji 10/90.txt", true, false, false, false);
				timeEnd = GetCounter();

				text = "Tryb Selekcji 10/90;" + tabFileTSP[i] + ";" + std::to_string(j) + ";" + std::to_string(timeEnd - timeStart) + ";" + std::to_string(genAlg.bestCost) + ";" + std::to_string(configTSPtab[i][2]) + ";" + genAlg.endType;
				filewriter("TestTSP.txt", text);
			}
		}
	}

	
	//Tryby selekcji 50/50
	if (mode[7]) {
		std::cout << "Tryby selekcji 50/50" << std::endl;

		for (int i = 0; i < tabFileATSP->size(); i++) {
			kl.set(tabFileATSP[i]);
			for (int j = 0; j < repeatNumber; j++) {
				std::cout << "Start Pomiaru " << tabFileATSP[i] << " - Numer Pomiaru - " << (j + 1) << std::endl;
				genAlg.init(kl.tabLocation, kl.size, configATSPtab[i][0], configATSPtab[i][1], 0.3);
				timeStart = GetCounter();
				genAlg.startAlgoritm(true, true, true, 0.3, false, 500, configATSPtab[i][2], tabOutFileATSP[i] + "-" + std::to_string(j) + "_Tryb Selekcji 50/50.txt", true, false, false, false);
				timeEnd = GetCounter();

				text = "Tryb Selekcji 50/50;" + tabFileATSP[i] + ";" + std::to_string(j) + ";" + std::to_string(timeEnd - timeStart) + ";" + std::to_string(genAlg.bestCost) + ";" + std::to_string(configATSPtab[i][2]) + ";" + genAlg.endType;
				filewriter("TestATSP.txt", text);
			}

			kl.set(tabFileTSP[i]);
			for (int j = 0; j < repeatNumber; j++) {
				std::cout << "Start Pomiaru " << tabFileTSP[i] << " - Numer Pomiaru - " << (j + 1) << std::endl;
				genAlg.init(kl.tabLocation, kl.size, configTSPtab[i][0], configTSPtab[i][1], 0.3);
				//(bool croosMode, bool mutateMode, bool succesionMode, double succesionProcent, bool sellectionMode, int maxIterationWithoutBetterVall, int expectedPathCost, std::string fileName, bool descriptionAdd);
				timeStart = GetCounter();
				genAlg.startAlgoritm(true, true, true, 0.3, true, 500, configTSPtab[i][2], tabOutFileTSP[i] + "-" + std::to_string(j) + "_Tryb Selekcji 50/50.txt", true, false, false, false);
				timeEnd = GetCounter();

				text = "Tryb Selekcji 50/50;" + tabFileTSP[i] + ";" + std::to_string(j) + ";" + std::to_string(timeEnd - timeStart) + ";" + std::to_string(genAlg.bestCost) + ";" + std::to_string(configTSPtab[i][2]) + ";" + genAlg.endType;
				filewriter("TestTSP.txt", text);
			}
		}
	}

	//Tryby mutacji zamiana 2 wybranych wierzcho³ków
	if (mode[8]) {
		std::cout << "Tryby mutacji zamiana 2 wybranych wierzcho³ków" << std::endl;

		for (int i = 0; i < tabFileATSP->size(); i++) {
			kl.set(tabFileATSP[i]);
			for (int j = 0; j < repeatNumber; j++) {
				std::cout << "Start Pomiaru " << tabFileATSP[i] << " - Numer Pomiaru - " << (j + 1) << std::endl;
				genAlg.init(kl.tabLocation, kl.size, configATSPtab[i][0], configATSPtab[i][1], 0.3);
				timeStart = GetCounter();
				genAlg.startAlgoritm(true, true, true, 0.3, true, 500, configATSPtab[i][2], tabOutFileATSP[i] + "-" + std::to_string(j) + "_Tryb Mutacji 2 wierzcho³ków.txt", true, false, false, false);
				timeEnd = GetCounter();

				text = "Tryb Mutacji 2 wierzcho³ków;" + tabFileATSP[i] + ";" + std::to_string(j) + ";" + std::to_string(timeEnd - timeStart) + ";" + std::to_string(genAlg.bestCost) + ";" + std::to_string(configATSPtab[i][2]) + ";" + genAlg.endType;
				filewriter("TestATSP.txt", text);
			}

			kl.set(tabFileTSP[i]);
			for (int j = 0; j < repeatNumber; j++) {
				std::cout << "Start Pomiaru " << tabFileTSP[i] << " - Numer Pomiaru - " << (j + 1) << std::endl;
				genAlg.init(kl.tabLocation, kl.size, configTSPtab[i][0], configTSPtab[i][1], 0.3);
				//(bool croosMode, bool mutateMode, bool succesionMode, double succesionProcent, bool sellectionMode, int maxIterationWithoutBetterVall, int expectedPathCost, std::string fileName, bool descriptionAdd);
				timeStart = GetCounter();
				genAlg.startAlgoritm(true, true, true, 0.3, true, 500, configTSPtab[i][2], tabOutFileTSP[i] + "-" + std::to_string(j) + "_Tryb Mutacji 2 wierzcho³ków.txt", true, false, false, false);
				timeEnd = GetCounter();

				text = "Tryb Mutacji 2 wierzcho³ków;" + tabFileTSP[i] + ";" + std::to_string(j) + ";" + std::to_string(timeEnd - timeStart) + ";" + std::to_string(genAlg.bestCost) + ";" + std::to_string(configTSPtab[i][2]) + ";" + genAlg.endType;
				filewriter("TestTSP.txt", text);
			}
		}
	}
	
	
	//Tryby mutacji zamiana fragmentu
	if (mode[9]) {
		std::cout << "Tryby mutacji zamiana fragmentu" << std::endl;

		for (int i = 0; i < tabFileATSP->size(); i++) {
			kl.set(tabFileATSP[i]);
			for (int j = 0; j < repeatNumber; j++) {
				std::cout << "Start Pomiaru " << tabFileATSP[i] << " - Numer Pomiaru - " << (j + 1) << std::endl;
				genAlg.init(kl.tabLocation, kl.size, configATSPtab[i][0], configATSPtab[i][1], 0.3);
				timeStart = GetCounter();
				genAlg.startAlgoritm(true, false, true, 0.3, true, 500, configATSPtab[i][2], tabOutFileATSP[i] + "-" + std::to_string(j) + "_Tryb Mutacji zamiana fragmentu.txt", true, false, false, false);
				timeEnd = GetCounter();

				text = "Tryb Mutacji zamiana fragmentu;" + tabFileATSP[i] + ";" + std::to_string(j) + ";" + std::to_string(timeEnd - timeStart) + ";" + std::to_string(genAlg.bestCost) + ";" + std::to_string(configATSPtab[i][2]) + ";" + genAlg.endType;
				filewriter("TestATSP.txt", text);
			}

			kl.set(tabFileTSP[i]);
			for (int j = 0; j < repeatNumber; j++) {
				std::cout << "Start Pomiaru " << tabFileTSP[i] << " - Numer Pomiaru - " << (j + 1) << std::endl;
				genAlg.init(kl.tabLocation, kl.size, configTSPtab[i][0], configTSPtab[i][1], 0.3);
				//(bool croosMode, bool mutateMode, bool succesionMode, double succesionProcent, bool sellectionMode, int maxIterationWithoutBetterVall, int expectedPathCost, std::string fileName, bool descriptionAdd);
				timeStart = GetCounter();
				genAlg.startAlgoritm(true, false, true, 0.3, true, 500, configTSPtab[i][2], tabOutFileTSP[i] + "-" + std::to_string(j) + "_Tryb Mutacji zamiana fragmentu.txt", true, false, false, false);
				timeEnd = GetCounter();

				text = "Tryb Mutacji zamiana fragmentu;" + tabFileTSP[i] + ";" + std::to_string(j) + ";" + std::to_string(timeEnd - timeStart) + ";" + std::to_string(genAlg.bestCost) + ";" + std::to_string(configTSPtab[i][2]) + ";" + genAlg.endType;
				filewriter("TestTSP.txt", text);
			}
		}
	}

	

	//Tryby krzy¿owañ 50%/50%
	if (mode[10]) {
		std::cout << "Tryby krzy¿owañ 50%/50%" << std::endl;

		for (int i = 0; i < tabFileATSP->size(); i++) {
			kl.set(tabFileATSP[i]);
			for (int j = 0; j < repeatNumber; j++) {
				std::cout << "Start Pomiaru " << tabFileATSP[i] << " - Numer Pomiaru - " << (j + 1) << std::endl;
				genAlg.init(kl.tabLocation, kl.size, configATSPtab[i][0], configATSPtab[i][1], 0.3);
				timeStart = GetCounter();
				genAlg.startAlgoritm(true, true, true, 0.3, true, 500, configATSPtab[i][2], tabOutFileATSP[i] + "-" + std::to_string(j) + "_Tryb krzy¿owania 50/50.txt", true, false, false, false);
				timeEnd = GetCounter();

				text = "Tryb krzy¿owania 50/50;" + tabFileATSP[i] + ";" + std::to_string(j) + ";" + std::to_string(timeEnd - timeStart) + ";" + std::to_string(genAlg.bestCost) + ";" + std::to_string(configATSPtab[i][2]) + ";" + genAlg.endType;
				filewriter("TestATSP.txt", text);
			}

			kl.set(tabFileTSP[i]);
			for (int j = 0; j < repeatNumber; j++) {
				std::cout << "Start Pomiaru " << tabFileTSP[i] << " - Numer Pomiaru - " << (j + 1) << std::endl;
				genAlg.init(kl.tabLocation, kl.size, configTSPtab[i][0], configTSPtab[i][1], 0.3);
				//(bool croosMode, bool mutateMode, bool succesionMode, double succesionProcent, bool sellectionMode, int maxIterationWithoutBetterVall, int expectedPathCost, std::string fileName, bool descriptionAdd);
				timeStart = GetCounter();
				genAlg.startAlgoritm(true, true, true, 0.3, true, 500, configTSPtab[i][2], tabOutFileTSP[i] + "-" + std::to_string(j) + "_Tryb krzy¿owania 50/50.txt", true, false, false, false);
				timeEnd = GetCounter();

				text = "Tryb krzy¿owania 50/50;" + tabFileTSP[i] + ";" + std::to_string(j) + ";" + std::to_string(timeEnd - timeStart) + ";" + std::to_string(genAlg.bestCost) + ";" + std::to_string(configTSPtab[i][2]) + ";" + genAlg.endType;
				filewriter("TestTSP.txt", text);
			}
		}
	}

	
	//Tryby krzy¿owañ 25%/75%
	if (mode[11]) {
		std::cout << "Tryby krzy¿owañ 25%/75%" << std::endl;

		for (int i = 0; i < tabFileATSP->size(); i++) {
			kl.set(tabFileATSP[i]);
			for (int j = 0; j < repeatNumber; j++) {
				std::cout << "Start Pomiaru " << tabFileATSP[i] << " - Numer Pomiaru - " << (j + 1) << std::endl;
				genAlg.init(kl.tabLocation, kl.size, configATSPtab[i][0], configATSPtab[i][1], 0.3);
				timeStart = GetCounter();
				genAlg.startAlgoritm(false, true, true, 0.3, true, 500, configATSPtab[i][2], tabOutFileATSP[i] + "-" + std::to_string(j) + "_Tryb krzy¿owania 25/75.txt", true, false, false, false);
				timeEnd = GetCounter();

				text = "Tryb krzy¿owania 25/75;" + tabFileATSP[i] + ";" + std::to_string(j) + ";" + std::to_string(timeEnd - timeStart) + ";" + std::to_string(genAlg.bestCost) + ";" + std::to_string(configATSPtab[i][2]) + ";" + genAlg.endType;
				filewriter("TestATSP.txt", text);
			}

			kl.set(tabFileTSP[i]);
			for (int j = 0; j < repeatNumber; j++) {
				std::cout << "Start Pomiaru " << tabFileTSP[i] << " - Numer Pomiaru - " << (j + 1) << std::endl;
				genAlg.init(kl.tabLocation, kl.size, configTSPtab[i][0], configTSPtab[i][1], 0.3);
				//(bool croosMode, bool mutateMode, bool succesionMode, double succesionProcent, bool sellectionMode, int maxIterationWithoutBetterVall, int expectedPathCost, std::string fileName, bool descriptionAdd);
				timeStart = GetCounter();
				genAlg.startAlgoritm(false, true, true, 0.3, true, 500, configTSPtab[i][2], tabOutFileTSP[i] + "-" + std::to_string(j) + "_Tryb krzy¿owania 25/75.txt", true, false, false, false);
				timeEnd = GetCounter();

				text = "Tryb krzy¿owania 25/75;" + tabFileTSP[i] + ";" + std::to_string(j) + ";" + std::to_string(timeEnd - timeStart) + ";" + std::to_string(genAlg.bestCost) + ";" + std::to_string(configTSPtab[i][2]) + ";" + genAlg.endType;
				filewriter("TestTSP.txt", text);
			}
		}
	}

	

	//Pocz¹tkowa wartoœæ mutacji

	double mutateValue[]{
		0.05,
		0.3,
		0.5
	};

	if (mode[12]) {
		std::cout << "Pocz¹tkowa wartoœæ mutacji" << std::endl;

		for (int k = 0; k < 3; k++) {
			for (int i = 0; i < tabFileATSP->size(); i++) {
				kl.set(tabFileATSP[i]);
				for (int j = 0; j < repeatNumber; j++) {
					std::cout << "Start Pomiaru " << tabFileATSP[i] << " - Numer Pomiaru - " << (j + 1) << std::endl;
					genAlg.init(kl.tabLocation, kl.size, configATSPtab[i][0], configATSPtab[i][1], mutateValue[k]);
					timeStart = GetCounter();
					genAlg.startAlgoritm(true, true, true, 0.3, true, 500, configATSPtab[i][2], tabOutFileATSP[i] + "-" + std::to_string(j) + "_Zmienna wartoœæ pocz¹tkowa mutacji" + std::to_string(k) + ".txt", true, false, false, false);
					timeEnd = GetCounter();

					text = "Zmienna wartoœæ pocz¹tkowa mutacji : " + std::to_string(k) + ";" + tabFileATSP[i] + ";" + std::to_string(j) + ";" + std::to_string(timeEnd - timeStart) + ";" + std::to_string(genAlg.bestCost) + ";" + std::to_string(configATSPtab[i][2]) + ";" + genAlg.endType;
					filewriter("TestATSP.txt", text);
				}

				kl.set(tabFileTSP[i]);
				for (int j = 0; j < repeatNumber; j++) {
					std::cout << "Start Pomiaru " << tabFileTSP[i] << " - Numer Pomiaru - " << (j + 1) << std::endl;
					genAlg.init(kl.tabLocation, kl.size, configTSPtab[i][0], configTSPtab[i][1], mutateValue[k]);
					//(bool croosMode, bool mutateMode, bool succesionMode, double succesionProcent, bool sellectionMode, int maxIterationWithoutBetterVall, int expectedPathCost, std::string fileName, bool descriptionAdd);
					timeStart = GetCounter();
					genAlg.startAlgoritm(true, true, true, 0.3, true, 500, configTSPtab[i][2], tabOutFileTSP[i] + "-" + std::to_string(j) + "_Zmienna wartoœæ pocz¹tkowa mutacji" + std::to_string(k) + ".txt", true, false, false, false);
					timeEnd = GetCounter();

					text = "Zmienna wartoœæ pocz¹tkowa mutacji : " + std::to_string(k) + "; " + tabFileTSP[i] + ";" + std::to_string(j) + ";" + std::to_string(timeEnd - timeStart) + ";" + std::to_string(genAlg.bestCost) + ";" + std::to_string(configTSPtab[i][2]) + ";" + genAlg.endType;
					filewriter("TestTSP.txt", text);
				}
			}
		}
	}
}

