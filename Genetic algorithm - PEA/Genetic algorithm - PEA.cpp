// Genetic algorithm - PEA.cpp: definiuje punkt wejścia dla aplikacji.
//

#include "Genetic algorithm - PEA.h"

using namespace std;

int main()
{
	Pomiar pomiar;
	pomiar.autoTest3();

	/*int expectedPathCost = 2720;
	KomivoyagerLocation kl;
	kl.set("Pliki Do testów/ATSP/rbg443.txt");
	GeneticAlgoritm genAlg;
	genAlg.init(kl.tabLocation, kl.size, 300, 100, 0.3);
	genAlg.printPath("Start");
	//(bool croosMode, bool mutateMode, bool succesionMode, double succesionProcent, bool sellectionMode, int maxIterationWithoutBetterVall, int expectedPathCost, std::string fileName, bool descriptionAdd);
	genAlg.startAlgoritm(true, true, true, 0.3, true, 500, expectedPathCost, "rbg443_out.txt",true);
	genAlg.printPath("End");*/
	return 0;
}
