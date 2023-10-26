#include <Windows.h>
#include <iostream>
#include <cstdlib>
#include <fstream>
 
#include "Held-Karp - PEA - Komivoyager.h"


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

void test() {

}