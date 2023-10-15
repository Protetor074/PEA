#include <Windows.h>
#include <iostream>
#include <cstdlib>
#include <fstream>


#include "PEA - Komivoyager.h"

void Pomiar::main_menu() {
	int x;
	std::cout << "Podaj wielkosc grupy:";
	std::cin >> x;
	file_clear("algoritm_time.txt");

	all(x);

	//all(15);
	

	std::cout << "Pomiar zakonczono powodzeniem\n";
	system("pause");
}

void Pomiar::file_clear(std::string plik_name) {
	std::fstream plik;
	plik.open(plik_name, std::ios::out);
	plik << "Numer pomiaru ; Próba badawcza ; Numer pomiaru instancji ; Czas[ms] ; Liczba wierzcho³ków" << std::endl;
	plik.close();
}

void Pomiar::filewriter(double time_list, double time_matrix, std::string plik_name, std::string description, int density, int vertex_number) {
	std::fstream plik;
	int liczba;

	plik.open(plik_name, std::ios::app);

	plik << density << ";" << description << ";" << time_list << ";" << time_matrix << ";" << vertex_number << std::endl;
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


void Pomiar::all(int size_test_group) {

	double time_start, time_end;
	StartCounter();
	Bruteforce bf;
	KomivoyagerLocation kv;
	//problem type, size , dentisity

//Bruteforce

	std::cout << "Bruteforce - Komivoyager" << std::endl;

	//Pomiar 1 - Dane Jaroslaw Mierzwa

	std::cout << "Pomiar 1 - Dane Jaroslaw Mierzwa dla " << 10 << std::endl;
	std::cout << "Bruteforce - Data Read" << std::endl;
	kv.set("BruteForceData.txt");
	std::cout << "Bruteforce - Pomiar" << std::endl;
	time_start = GetCounter();
	bf.foundBestTrip(kv.size, kv.tabLocation);
	time_end = GetCounter();

	filewriter(time_end - time_start, 0 - 0, "Bruteforce.txt", "P1 - JaroslawMierzwa", 1, kv.size);


	//Pomiar 2 - Dane generowane - 1-10 dla grupy 10

	std::cout << "Pomiar 2 - 1-10 dla " << kv.size << std::endl;
	std::cout << "Bruteforce - Data Generate" << std::endl;
	kv.generate(kv.size, 10);
	std::cout << "Bruteforce - Pomiar" << std::endl;
	time_start = GetCounter();
	bf.foundBestTrip(kv.size, kv.tabLocation);
	time_end = GetCounter();

	filewriter(time_end - time_start, 0 - 0, "Bruteforce.txt", "P2 - 1-10", 1, kv.size);


	//Pomiar 3 - Dane generowane - 1-1000 dla grupy 10

	std::cout << "Pomiar 3 - 1-1000 dla " << kv.size << std::endl;
	std::cout << "Bruteforce - Data Generate" << std::endl;
	kv.generate(kv.size, 1000);
	std::cout << "Bruteforce - Pomiar" << std::endl;
	time_start = GetCounter();
	bf.foundBestTrip(kv.size, kv.tabLocation);
	time_end = GetCounter();

	filewriter(time_end - time_start, 0 - 0, "Bruteforce.txt", "P3 - 1-1000", 1, kv.size);


	//Pomiar 4 - Dane generowane - 1-10 dla grupy 14

	std::cout << "Pomiar 4 - 1-10 dla " << size_test_group << std::endl;
	std::cout << "Bruteforce - Data Generate" << std::endl;
	kv.generate(size_test_group, 10);
	std::cout << "Bruteforce - Pomiar" << std::endl;
	time_start = GetCounter();
	bf.foundBestTrip(kv.size, kv.tabLocation);
	time_end = GetCounter();

	filewriter(time_end - time_start, 0 - 0, "Bruteforce.txt", "P4 - 1-10", 1, size_test_group);


	//Pomiar 5 - Dane generowanie - 1-1000 dla grupy 14

	std::cout << "Pomiar 5 - 1-1000 dla " << size_test_group << std::endl;
	std::cout << "Bruteforce - Data Generate" << std::endl;
	kv.generate(size_test_group, 1000);
	std::cout << "Bruteforce - Pomiar" << std::endl;
	time_start = GetCounter();
	bf.foundBestTrip(kv.size, kv.tabLocation);
	time_end = GetCounter();

	filewriter(time_end - time_start, 0 - 0, "Bruteforce.txt", "P5 - 1-1000", 1, size_test_group);
}
void Pomiar::test(std::string outputFile, int testNumber, int testRepeat) {
	int instantionMultiplicationTest = testRepeat;

	file_clear(outputFile);

	double time_start, time_end;
	StartCounter();
	Bruteforce bf;
	KomivoyagerLocation kv;

	for (int j = 3; j <= 11; j++) {
		for (int i = 1; i <= testNumber; i++) {
			std::cout << "Pomiar " << i << " - 1-10 dla " << j << std::endl;
			std::cout << "Bruteforce - Data Generate" << std::endl;
			kv.generate(j, 10);
			for (int z = 1; z <= instantionMultiplicationTest; z++) {
				std::cout << "Bruteforce - Pomiar " << i << " powtozenie instancji " << z << std::endl;
				time_start = GetCounter();
				bf.foundBestTrip(kv.size, kv.tabLocation);
				time_end = GetCounter();

				filewriter(z, time_end - time_start, "Bruteforce.txt", "1-10", i, kv.size);
			}
			

			

			std::cout << "Pomiar " << i << " - 1-1000 dla " << j << std::endl;
			std::cout << "Bruteforce - Data Generate" << std::endl;
			kv.generate(j, 1000);
			for (int z = 1; z <= instantionMultiplicationTest; z++) {
				std::cout << "Bruteforce - Pomiar " << i << " powtozenie instancji " << z << std::endl;
				time_start = GetCounter();
				bf.foundBestTrip(kv.size, kv.tabLocation);
				time_end = GetCounter();

				filewriter(z, time_end - time_start, "Bruteforce.txt", "1-1000", i, kv.size);
			}

			std::cout << "Pomiar " << i << " - 1-1000000 dla " << j << std::endl;
			std::cout << "Bruteforce - Data Generate" << std::endl;
			kv.generate(j, 1000000);
			for (int z = 1; z <= instantionMultiplicationTest; z++) {
				std::cout << "Bruteforce - Pomiar " << i << " powtozenie instancji " << z << std::endl;
				time_start = GetCounter();
				bf.foundBestTrip(kv.size, kv.tabLocation);
				time_end = GetCounter();

				filewriter(z, time_end - time_start, "Bruteforce.txt", "1-1000000", i, kv.size);
			}
		}
	}
}

