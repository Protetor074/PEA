#include "Wy¿arzanie - PEA.h"
<<<<<<< HEAD
#include <sstream>
#include <chrono>
=======
>>>>>>> 90e5141f80991f1b1268c09fab77eafdbfe6eea1

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

<<<<<<< HEAD
=======

>>>>>>> 90e5141f80991f1b1268c09fab77eafdbfe6eea1
// Funkcja pomocnicza do wyœwietlania œcie¿ki
void AS_Alg::printPath(std::string description) {
    std::cout << description << std::endl;
    for (const auto& city : currentPath) {
        std::cout << city << " ";
    }
    std::cout << std::endl;
<<<<<<< HEAD
    std::cout << "Koszt = " << getCurentCost() << std::endl;
=======
    std::cout << "Koszt = " << curentCost << std::endl;
>>>>>>> 90e5141f80991f1b1268c09fab77eafdbfe6eea1
    std::cout << "Temperatura poczatkowa = " << initialTemperature << std::endl;
    std::cout << "Temperatura koncowa = " << currentTemperature << std::endl << std::endl;

}

//initPathGeneratorMode == false - tryb losowy
//initPathGeneratorMode == true - tryb najbli¿szego nie odwiedzonego s¹siedztwa
<<<<<<< HEAD
void AS_Alg::init(int** tabLocation, int tabLocationSize, bool initPathGeneratorMode, bool startTempMode, double avgTestVertxCorectionVal, double lCorectionVal, int eraLongMode) {
    this->tabLocation = tabLocation;
    this->tabLocationSize = tabLocationSize;
    this->lCorectionVal = lCorectionVal;
    setEraLong(eraLongMode);
=======
void AS_Alg::init(int** tabLocation, int tabLocationSize,int minTripVal,int maxTripVal, bool initPathGeneratorMode, bool startTempMode, int avgTestVertx) {
    this->tabLocation = tabLocation;
    this->tabLocationSize = tabLocationSize;
    this->minTripVal = minTripVal;
    this->maxTripVal = maxTripVal;
>>>>>>> 90e5141f80991f1b1268c09fab77eafdbfe6eea1

    if (initPathGeneratorMode) {
        generateNearestNeighborPath();
    }
    else {
        generateRandomPath();
    }

    if (startTempMode) {
<<<<<<< HEAD
        generateInitialTemperatureFromAverage(tabLocationSize*tabLocationSize*avgTestVertxCorectionVal);
    }
    else {
        foundMinMaxTripCost();
        generateMaxInitialTemperature(minTripVal, maxTripVal);
    }

    initPath.assign(currentPath.begin(), currentPath.end());

    calculatePathCost();
    initCost = curentCost;
}

//Funkcja rozpoczyna pracê algorytmu w trybie ch³odzenia geometrycznego
void AS_Alg::startAlgoritmGeo(double alpha, bool selectVertexMode, double probability) {    
    /*std::cout << "\nAlg start - GEO" << std::endl;
    std::cout << "Sciezka = " << getCurentPath() << std::endl;
    std::cout << "Koszt = " << getCurentCost() << std::endl;*/
=======
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
>>>>>>> 90e5141f80991f1b1268c09fab77eafdbfe6eea1

    srand(time(nullptr));
    int city1;
    int city2;
<<<<<<< HEAD
    k = 1;

    while (currentTemperature>= 1){
=======

    for (int i = 0; i < iterationNumber; i++) {
>>>>>>> 90e5141f80991f1b1268c09fab77eafdbfe6eea1
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
<<<<<<< HEAD
        k++;
        currentTemperature = currentTemperature * alpha;
=======
       
        currentTemperature = currentTemperature * alpha;
        if (currentTemperature <= 1) {
            break;
        }
>>>>>>> 90e5141f80991f1b1268c09fab77eafdbfe6eea1
    }
}

//Funkcja rozpoczyna pracê algorytmu w trybie ch³odzenia Boltzmana
<<<<<<< HEAD
void AS_Alg::startAlgoritmBoltzmann(bool selectVertexMode, double probability) {

    /*std::cout << "\nAlg start - Boltz" << std::endl;
    std::cout << "Sciezka = " << getCurentPath() << std::endl;
    std::cout << "Koszt = " << getCurentCost() << std::endl;*/
=======
void AS_Alg::startAlgoritmBoltzmann(bool selectVertexMode, double probability, int iterationNumber, int iterationSize) {
    currentTemperature = initialTemperature;
>>>>>>> 90e5141f80991f1b1268c09fab77eafdbfe6eea1

    srand(time(nullptr));
    int city1;
    int city2;
<<<<<<< HEAD
    k = 1;

    while (currentTemperature >= 1) {
        if (!selectVertexMode) {
=======

    for (int i = 0; i < iterationNumber; i++) {
        if (selectVertexMode) {
>>>>>>> 90e5141f80991f1b1268c09fab77eafdbfe6eea1
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
<<<<<<< HEAD
        k++;
        currentTemperature = currentTemperature / log(k + 1);
    }
    k--;
=======
        currentTemperature = currentTemperature / log(iterationNumber + 1);
        if (currentTemperature <= 1) {
            break;
        }
    }
>>>>>>> 90e5141f80991f1b1268c09fab77eafdbfe6eea1
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
<<<<<<< HEAD
    currentPath.clear();
=======
>>>>>>> 90e5141f80991f1b1268c09fab77eafdbfe6eea1
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
<<<<<<< HEAD
    currentPath.clear();
=======
>>>>>>> 90e5141f80991f1b1268c09fab77eafdbfe6eea1

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
<<<<<<< HEAD
void AS_Alg::generateMaxInitialTemperature(int minTemperature, int maxTemperature) {
    // Losowo generuj temperaturê w zakresie [minTemperature, maxTemperature]
    initialTemperature = maxTemperature - minTemperature;
=======
void AS_Alg::generateRandomInitialTemperature(int minTemperature, int maxTemperature) {
    srand(time(nullptr));

    // Losowo generuj temperaturê w zakresie [minTemperature, maxTemperature]
    initialTemperature = (minTemperature + rand() % (maxTemperature - minTemperature));
>>>>>>> 90e5141f80991f1b1268c09fab77eafdbfe6eea1

}

// Funkcja generuj¹ca temperaturê pocz¹tkow¹ na podstawie œredniej z n punktów
void AS_Alg::generateInitialTemperatureFromAverage(int n) {
    // Inicjalizacja generatora liczb losowych
    srand(time(nullptr));
<<<<<<< HEAD
    std::random_device rd;
    std::mt19937 gen;

    double sumDistances = 0.0;
    for (int i = 0; i < n; ++i) {
        std::this_thread::sleep_for(std::chrono::nanoseconds(10));
        // Losowo wybierz dwa ró¿ne miasta
        int city1 = rand()*gen() % tabLocationSize;
        int city2 = rd() % tabLocationSize;
=======

    double sumDistances = 0.0;
    for (int i = 0; i < n; ++i) {
        // Losowo wybierz dwa ró¿ne miasta
        int city1 = rand() % tabLocationSize;
        int city2 = rand() % tabLocationSize;
>>>>>>> 90e5141f80991f1b1268c09fab77eafdbfe6eea1
        while (city2 == city1) {
            city2 = rand() % tabLocationSize;
        }

        // Dodaj odleg³oœæ miêdzy miastami do sumy
        sumDistances += tabLocation[city1][city2];
    }

    // Oblicz œredni¹ odleg³oœæ
    initialTemperature = sumDistances / n;
<<<<<<< HEAD
    //std::cout << initialTemperature << std::endl;
=======
>>>>>>> 90e5141f80991f1b1268c09fab77eafdbfe6eea1
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

<<<<<<< HEAD
void AS_Alg::foundMinMaxTripCost() {
    minTripVal = tabLocation[0][1];
    maxTripVal = tabLocation[0][1];

    // Przeszukiwanie tablicy
    for (int i = 0; i < tabLocationSize; ++i) {
        for (int j = 0; j < tabLocationSize; ++j) {
            if (i != j) {
                if (tabLocation[i][j] < minTripVal) {
                    minTripVal = tabLocation[i][j];
                }
                if (tabLocation[i][j] > maxTripVal) {
                    maxTripVal = tabLocation[i][j];
                }
            }
        }
    }
}

int AS_Alg::getCurentCost() {
    calculatePathCost();
    return curentCost;
}

std::string AS_Alg::getCurentPath() {
    // Tworzenie strumienia do konwersji int do string
    std::ostringstream oss;

    // Dodawanie elementów œcie¿ki do strumienia
    for (size_t i = 0; i < currentPath.size(); ++i) {
        oss << currentPath[i];

        // Dodanie separatora (np. przecinka) poza ostatnim elementem
        if (i < currentPath.size() - 1) {
            oss << ",";
        }
    }

    // Zwrócenie stringa utworzonego ze œcie¿ki
    return oss.str();
}

int AS_Alg::getNumberK() {
    return k;
}

std::vector<int> AS_Alg::getMinMaxCost() {
    min_maxCost = { minTripVal, maxTripVal};
    return min_maxCost;
}

int AS_Alg::getCurentTemp() {
    return currentTemperature;
}

void AS_Alg::refreshItterationSize(double val) {
    iterationSize = tabLocationSize * tabLocationSize * val;
}

void AS_Alg::setEraLong(int mode) {
    
    switch (mode)
    {
    case 1:
        this->iterationSize = tabLocationSize * tabLocationSize * lCorectionVal;
        break;
    case 2:
        this->iterationSize = tabLocationSize /2;
        break;
    case 3:
        this->iterationSize = tabLocationSize;
        break;
    case 4:
        this->iterationSize = tabLocationSize *log(tabLocationSize);
        break;
    case 5:
        this->iterationSize = tabLocationSize * tabLocationSize / 2;
        break;
    case 6:
        this->iterationSize = tabLocationSize * tabLocationSize;
        break;
    }
}

/*void AS_Alg::shuffle(std::vector<int>& currentPath) {
    for (int i = 0; i < currentPath.size(); i++) {
        int j = std::rand() % (currentPath.size() - i);
        int temp = currentPath[i];
        currentPath[i] = currentPath[j];
        currentPath[j] = temp;
    }
}*/
=======
>>>>>>> 90e5141f80991f1b1268c09fab77eafdbfe6eea1





  