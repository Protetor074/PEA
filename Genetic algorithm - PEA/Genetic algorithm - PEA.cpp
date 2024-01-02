// Genetic algorithm - PEA.cpp: definiuje punkt wejścia dla aplikacji.
//

#include "Genetic algorithm - PEA.h"

using namespace std;

int main()
{
	KomivoyagerLocation kl;
	kl.generate(10, 1, 10, false);
	GeneticAlgoritm genAlg;
	genAlg.init(kl.tabLocation, kl.size, 10, 3, 0.5);
	genAlg.startAlgoritm();
	return 0;
}
