#include "Wy¿arzanie - PEA.h"

void KomivoyagerLocation::create(int size) {
	tabLocation = new int* [size];
	this->size = size;
	for (int i = 0; i < size; i++) {
		tabLocation[i] = new int[size];
	}

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			tabLocation[i][j] = 0;
		}
	}
}

void KomivoyagerLocation::generate(int size, int minValue, int maxValue, bool symetric){
	int random, random1;
	create(size);
	srand(time(NULL));
	for (int i = 0; i < size; i++) {
		for (int j = i; j < size; j++) {
			random = (rand() % (maxValue - minValue)) + minValue;
			random1 = (rand() % (maxValue - minValue)) + minValue;

			if (random == 0) {
				random = maxValue / 2;
			}
			else if (random < 0) {
				random = random * (-1);
			}
			if (random1 == 0) {
				random1 = maxValue / 2;
			}
			else if (random1 < 0) {
				random1 = random1 * (-1);
			}

			if (symetric) {
				tabLocation[i][j] = random;
				tabLocation[j][i] = random;
			}
			else {
				tabLocation[i][j] = random;
				tabLocation[j][i] = random1;
			}

		}
		tabLocation[i][i] = -1;
	}
}

void KomivoyagerLocation::printTab() {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (tabLocation[i][j] == -1) {
				std::cout << tabLocation[i][j] << " ";
			}
			else {
				std::cout << tabLocation[i][j] << "  ";
			}
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void KomivoyagerLocation::set(std::string file_name) {
	std::fstream plik;

	plik.open(file_name, std::ios::in);

	if (plik.good()) {
		plik >> size;
		create(size);

		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				plik >> tabLocation[i][j];
				//std::cout << tabLocation[i][j] << " ";
			}
			//std::cout << std::endl;
		}
		plik.close();
	}
}