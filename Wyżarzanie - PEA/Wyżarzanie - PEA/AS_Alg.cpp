#include "Wy¿arzanie - PEA.h"

// Funkcja obliczaj¹ca koszt dla danej œcie¿ki i macierzy s¹siedztwa
void AS_Alg::calculatePathCost() {
    curentCost = 0;
    for (size_t i = 0; i < tabLocationSize-1; ++i) {
        int city1 = currentPath[i];  // Indeksowanie od zera
        int city2 = currentPath[i + 1];

        curentCost += tabLocation[city1][city2];
    }

    // Dodaj koszt przejœcia z ostatniego do pierwszego miasta
    curentCost += tabLocation[currentPath.back()][currentPath.front()];
}


// Funkcja pomocnicza do wyœwietlania œcie¿ki
void AS_Alg::printPath(std::string description) {
    std::cout << description << std::endl;
    for (const auto& city : currentPath) {
        std::cout << city << " ";
    }
    std::cout << std::endl;
    std::cout << "Koszt = " << curentCost << std::endl;
    std::cout << "Temperatura poczatkowa = " << initialTemperature << std::endl;
    std::cout << "Temperatura koncowa = " << currentTemperature << std::endl << std::endl;

}

//initPathGeneratorMode == false - tryb losowy
//initPathGeneratorMode == true - tryb najbli¿szego nie odwiedzonego s¹siedztwa
void AS_Alg::init(int** tabLocation, int tabLocationSize,int minTripVal,int maxTripVal, bool initPathGeneratorMode, bool startTempMode, int avgTestVertx) {
    this->tabLocation = tabLocation;
    this->tabLocationSize = tabLocationSize;
    this->minTripVal = minTripVal;
    this->maxTripVal = maxTripVal;

    if (initPathGeneratorMode) {
        generateNearestNeighborPath();
    }
    else {
        generateRandomPath();
    }

    if (startTempMode) {
        generateInitialTemperatureFromAverage(avgTestVertx);
    }
    else {
        generateRandomInitialTemperature(minTripVal, maxTripVal);
    }
    currentTemperature = initialTemperature;

    calculatePathCost();
    //currentTemperature = initialTemperature;
    printPath("Sciezka poczatkowa:");
}

//Funkcja rozpoczyna pracê algorytmu w trybie ch³odzenia geometrycznego
void AS_Alg::startAlgoritmGeo(double alpha, bool selectVertexMode, double probability, int iterationNumber, int iterationSize) {
    currentTemperature = initialTemperature;

    srand(time(nullptr));
    int city1;
    int city2;

    for (int i = 0; i < iterationNumber; i++) {
        if (!selectVertexMode) {
            for (int j = 0; j < iterationSize; j++) {
                city1 = rand() % tabLocationSize;
                city2 = rand() % tabLocationSize;
                while (city1 == city2) {
                    city2 = rand() % tabLocationSize;
                }

                swapVerticesAndUpdateCost(city1, city2);

                if (acceptanceProbability(curentCost, newCost, currentTemperature, probability)) {
                    curentCost = newCost;
                    currentPath = newPath;
                }
            }
        }
        else {
            for (int j = 0; j < iterationSize; j++) {
                city1 = rand() % tabLocationSize;

                moveVertexLeft(city1);

                if (acceptanceProbability(curentCost, newCost, currentTemperature, probability)) {
                    curentCost = newCost;
                    currentPath = newPath;
                }
            }
        }
       
        currentTemperature = currentTemperature * alpha;
        if (currentTemperature <= 1) {
            break;
        }
    }
}

//Funkcja rozpoczyna pracê algorytmu w trybie ch³odzenia Boltzmana
void AS_Alg::startAlgoritmBoltzmann(bool selectVertexMode, double probability, int iterationNumber, int iterationSize) {
    currentTemperature = initialTemperature;

    srand(time(nullptr));
    int city1;
    int city2;

    for (int i = 0; i < iterationNumber; i++) {
        if (selectVertexMode) {
            for (int j = 0; j < iterationSize; j++) {
                city1 = rand() % tabLocationSize;
                city2 = rand() % tabLocationSize;
                if (city1 == city2) {
                    city2 = rand() % tabLocationSize;
                }

                swapVerticesAndUpdateCost(city1, city2);

                if (acceptanceProbability(curentCost, newCost, currentTemperature, probability)) {
                    curentCost = newCost;
                    currentPath = newPath;
                }
            }
        }
        else {
            for (int j = 0; j < iterationSize; j++) {
                city1 = rand() % tabLocationSize;

                moveVertexLeft(city1);

                if (acceptanceProbability(curentCost, newCost, currentTemperature, probability)) {
                    curentCost = newCost;
                    currentPath = newPath;
                }
            }
        }
        currentTemperature = currentTemperature / log(iterationNumber + 1);
        if (currentTemperature <= 1) {
            break;
        }
    }
}

//Funkcja akceptacji zmiany œcie¿ki
bool AS_Alg::acceptanceProbability(double currentCost, double newCost, double temperature,double probability) {
    if (newCost < currentCost) {
        // Jeœli nowe rozwi¹zanie jest lepsze, zaakceptuj je zawsze
        return true;
    }
    else {
        // W przeciwnym razie, zaakceptuj z pewnym prawdopodobieñstwem Boltzmanna
        probabilityVal = exp((currentCost - newCost) / temperature);

        /*std::cout << "currentCost: " << currentCost << std::endl;
        std::cout << "newCost: " << newCost << std::endl;
        std::cout << "(currentCost - newCost): " << (currentCost - newCost) << std::endl;
        std::cout << "temperature: " << temperature << std::endl;
        std::cout << "Probability Value: " << probabilityVal << std::endl;*/
        

        if (probabilityVal > probability) {
            //std::cout << "Swap: true" << std::endl << std::endl;
            return true;
        }
        else
        {
            //std::cout << "Swap: false" << std::endl << std::endl;
            return false;
        }
    }
}

/// <summary>
/// Funkcje odpowiedzialne za wybór rozwi¹zania w s¹siedztwie
/// </summary>


// Funkcja zamieniaj¹ca dwie pozycje w œcie¿ce i aktualizuj¹ca koszt
void AS_Alg::swapVerticesAndUpdateCost(int index1, int index2) {
    // Kopiuj obecn¹ œcie¿kê do newPath
    newPath = currentPath;

    // Zamieñ wierzcho³ki na wybranych pozycjach
    std::swap(newPath[index1], newPath[index2]);

    // Zaktualizuj koszt œcie¿ki (nie licz¹c odleg³oœci do pocz¹tku)
    newCost = 0;

    for (size_t i = 0; i < tabLocationSize - 1; ++i) {
        int city1 = newPath[i];  // Indeksowanie od zera
        int city2 = newPath[i + 1];

        newCost += tabLocation[city1][city2];
    }

    // Dodaj koszt przejœcia z ostatniego do pierwszego miasta
    newCost += tabLocation[newPath.back()][newPath.front()];

}

//Funkcja przesuwa wierzcholek w lewo w nowej œcie¿ce
void AS_Alg::moveVertexLeft(int index) {
    if (index != 0) {
        swapVerticesAndUpdateCost(index - 1, index);
    }
    else
    {
        swapVerticesAndUpdateCost(0, tabLocationSize-1);
    }

}

/// <summary>
/// Funkcje odpowiedzialne za generowanie pocz¹tkowej œcie¿ki
/// </summary>

void AS_Alg::generateNearestNeighborPath() {
    currentPath.reserve(tabLocationSize);

    srand(time(nullptr));

    // Wybierz losowe miasto jako pocz¹tkowe
    int currentCity = rand() % tabLocationSize;
    currentPath.push_back(currentCity);

    // Generuj œcie¿kê przez wybieranie najbli¿szego s¹siada
    for (int i = 1; i < tabLocationSize; ++i) {
        int nearestNeighbor = -1;
        int minDistance = maxINT;

        for (int j = 0; j < tabLocationSize; ++j) {
            if (std::find(currentPath.begin(), currentPath.end(), j) == currentPath.end()) {
                int distance = tabLocation[currentCity][j];
                if (distance < minDistance) {
                    minDistance = distance;
                    nearestNeighbor = j;
                }
            }
        }
        currentPath.push_back(nearestNeighbor);
        currentCity = nearestNeighbor;
    }
}

// Funkcja generuj¹ca losow¹ pocz¹tkow¹ œcie¿kê
void AS_Alg::generateRandomPath() {

    for (int i = 0; i < tabLocationSize; ++i) {
        currentPath.push_back(i);
    }

    std::random_device rd;  // U¿yj generatora sprzêtowego do uzyskania ziarna
    std::mt19937 gen(rd()); // U¿yj algorytmu Mersenne Twister

    // Losowe przemieszanie œcie¿ki
    std::shuffle(currentPath.begin(), currentPath.end(), gen);
}

/// <summary>
/// Funkcje odpowiedzialne za generowanie temperatury pocz¹tkowej
/// </summary>

// Funkcja generuj¹ca temperaturê pocz¹tkow¹ losowo z przedzia³u
void AS_Alg::generateRandomInitialTemperature(int minTemperature, int maxTemperature) {
    srand(time(nullptr));

    // Losowo generuj temperaturê w zakresie [minTemperature, maxTemperature]
    initialTemperature = (minTemperature + rand() % (maxTemperature - minTemperature));

}

// Funkcja generuj¹ca temperaturê pocz¹tkow¹ na podstawie œredniej z n punktów
void AS_Alg::generateInitialTemperatureFromAverage(int n) {
    // Inicjalizacja generatora liczb losowych
    srand(time(nullptr));

    double sumDistances = 0.0;
    for (int i = 0; i < n; ++i) {
        // Losowo wybierz dwa ró¿ne miasta
        int city1 = rand() % tabLocationSize;
        int city2 = rand() % tabLocationSize;
        while (city2 == city1) {
            city2 = rand() % tabLocationSize;
        }

        // Dodaj odleg³oœæ miêdzy miastami do sumy
        sumDistances += tabLocation[city1][city2];
    }

    // Oblicz œredni¹ odleg³oœæ
    initialTemperature = sumDistances / n;
}

void AS_Alg::clean() {
    for (int i = 0; i < tabLocationSize; ++i) {
        delete[] tabLocation[i];
    }
    delete[] tabLocation;

    // Czyszczenie wektorów
    currentPath.clear();
    newPath.clear();

    // Resetowanie reszty zmiennych
    tabLocation = nullptr;
    tabLocationSize = 0;
    minTripVal = 0;
    maxTripVal = 0;
    curentCost = 0;
    newCost = 0;
}






  