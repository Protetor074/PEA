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
<<<<<<< HEAD
	int random, random1, ranndom1extra, ranndom2extra;
=======
	int random, random1;
>>>>>>> 90e5141f80991f1b1268c09fab77eafdbfe6eea1
	create(size);
	srand(time(NULL));
	for (int i = 0; i < size; i++) {
		for (int j = i; j < size; j++) {
<<<<<<< HEAD

			ranndom1extra = rand();
			ranndom1extra <<= 15;
			ranndom1extra ^= rand();

			ranndom2extra = rand();
			ranndom2extra <<= 15;
			ranndom2extra ^= rand();

			random = (ranndom1extra % (maxValue - minValue)) + minValue;
			random1 = (ranndom2extra % (maxValue - minValue)) + minValue;
=======
			random = (rand() % (maxValue - minValue)) + minValue;
			random1 = (rand() % (maxValue - minValue)) + minValue;
>>>>>>> 90e5141f80991f1b1268c09fab77eafdbfe6eea1

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
<<<<<<< HEAD
	else {
		for (int i = 0; i < 5; i++) {
			std::cout << "!!!UWAGA!!! Bland Pliku :" << file_name << "!!!UWAGA!!!\n";
		}
	}
=======
>>>>>>> 90e5141f80991f1b1268c09fab77eafdbfe6eea1
}