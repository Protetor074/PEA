#include <Windows.h>
#include <iostream>
#include <cstdlib>
#include <fstream>
 
#include "Held-Karp - PEA - Komivoyager.h"


void Pomiar::file_clear(std::string plik_name) {
	std::fstream plik;
	plik.open(plik_name, std::ios::out);
	plik << "Numer pomiaru ; Numer pomiaru instancji ; Próba badawcza ; Liczba wierzcho³ków ; Czas[ms] " << std::endl;
	plik.close();
}

void Pomiar::filewriter(int testNumber, int reapeatNumber, std::string description, int vertexNumber, double time, std::string plik_name ) {
	std::fstream plik;
	int liczba;

	plik.open(plik_name, std::ios::app);

	plik << testNumber << ";" << reapeatNumber << ";" << description << ";" << vertexNumber << ";" << time << std::endl;
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

void Pomiar::autoTest(std::string fileName, int numberInst, int numberRepeat, int minVertex, int maxVertex) {

	int vertexNumber = minVertex;
	KomivoyagerLocation kl;
	HeldKarpAlg hka;
	double timeStart = 0;
	double timeEnd = 0;

	file_clear(fileName);
	StartCounter();

	while (vertexNumber <= maxVertex) {

		for (int i = 0; i < numberInst; i++) {

			std::cout << "Pomiar dla liczby wierzcholkow = " << vertexNumber << " Dla instancji = " << i << std::endl;

			kl.generate(vertexNumber, 10);

			StartCounter();
			for (int j = 0; j < numberRepeat; j++) {
				timeStart = GetCounter();
				hka.init(kl.tabLocation, kl.size);
				timeEnd = GetCounter();

				filewriter(i + 1, j + 1, "1 do 10", vertexNumber, timeEnd - timeStart, fileName);
			}

			kl.generate(vertexNumber, 10000);

			StartCounter();
			for (int j = 0; j < numberRepeat; j++) {
				timeStart = GetCounter();
				hka.init(kl.tabLocation, kl.size);
				timeEnd = GetCounter();

				filewriter(i + 1, j + 1, "1 do 10 000", vertexNumber, timeEnd - timeStart, fileName);
			}

			kl.generate(vertexNumber, 10000000);

			StartCounter();
			for (int j = 0; j < numberRepeat; j++) {
				timeStart = GetCounter();
				hka.init(kl.tabLocation, kl.size);
				timeEnd = GetCounter();

				filewriter(i + 1, j + 1, "1 do 10 000 000", vertexNumber, timeEnd - timeStart, fileName);
			}
		}

		vertexNumber++;
	}
}