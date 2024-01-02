#include "Genetic algorithm - PEA.h"
#include <algorithm>
#include <unordered_set>


void GeneticAlgoritm::init(int** tabLocation, int tabLocationSize, int populationSize, int startCrosNumber, double mutatePropabylyty) {
    //liczba generacji
    //liczba mutacji na generacjê
    // Liczba krzy¿ówek na generacjiê
    //lpopulacji na generacjê

    this->startPopulationSize = populationSize;
    this->startCrosNumber = startCrosNumber;
    this->startMutatePropabylyty = mutatePropabylyty;

    this->tabLocation = tabLocation;
    this->tabLocationSize = tabLocationSize;

    createStartPath();
    sort(tabOfNextGenerationGenCost, tabOfNextGenerationGen);
    srand(time(NULL));
}

//Funkcja sortuj¹ca œcie¿ki po koszcie
void GeneticAlgoritm::sort(std::vector<int>& cost, std::vector<std::vector<int>>& path) {

    // Tworzenie wektora indeksów
    std::vector<size_t> indeksy(cost.size());
    for (size_t i = 0; i < indeksy.size(); ++i) {
        indeksy[i] = i;
    }

    // Sortowanie indeksów na podstawie kosztów
    std::sort(indeksy.begin(), indeksy.end(), [&cost](size_t i, size_t j) {
        return cost[i] < cost[j];
        });

    // Tworzenie posortowanych tablic
    std::vector<int> sortCost;
    std::vector<std::vector<int>> sortPath;

    for (size_t i : indeksy) {
        sortCost.push_back(cost[i]);
        sortPath.push_back(path[i]);
    }

    cost = sortCost;
    path = sortPath;
}

//Funkcja tworz¹ca pocz¹tkowy zestaw œcie¿ek
void GeneticAlgoritm::createStartPath() {
    tabOfNextGenerationGen.resize(startPopulationSize);
    tabOfNextGenerationGenCost.resize(startPopulationSize);

    for (int i = 0; i < startPopulationSize; i++) {
        tabOfNextGenerationGen[i] = generateRandomPath();
        tabOfNextGenerationGenCost[i] = calculatePathCost(tabOfNextGenerationGen[i]);
    }
}

// Funkcja wyznaczaj¹ca koszt œcie¿ki
int GeneticAlgoritm::calculatePathCost(std::vector<int> path) {
    int cost = 0;
    for (size_t i = 0; i < tabLocationSize - 1; ++i) {
        int city1 = path[i];  // Indeksowanie od zera
        int city2 = path[i + 1];

        cost += tabLocation[city1][city2];
    }

    // Dodaj koszt przejœcia z ostatniego do pierwszego miasta
    cost += tabLocation[path.back()][path.front()];
    return cost;
}

// Funkcja generuj¹ca losow¹ œcie¿kê
std::vector<int> GeneticAlgoritm::generateRandomPath() {
    std::vector<int> path;

    for (int i = 0; i < tabLocationSize; ++i) {
        path.push_back(i);
    }

    std::random_device rd;  // U¿yj generatora sprzêtowego do uzyskania ziarna
    std::mt19937 gen(rd()); // U¿yj algorytmu Mersenne Twister

    // Losowe przemieszanie œcie¿ki
    std::shuffle(path.begin() + 1, path.end(), gen);
    return path;
}

// Funkcja pomocnicza do wyœwietlania œcie¿ki
void GeneticAlgoritm::printPath(std::string description, std::vector<int> cost, std::vector<std::vector<int>> path) {
    std::cout << description << std::endl;
    for (int i = 0; i < path.size(); i++) {
        for (const auto& city : path[i]) {
            std::cout << city << " ";
        }
        std::cout << std::endl;
        std::cout << "Koszt = " << cost[i] << std::endl;
    }
    std::cout << std::endl;
}

void GeneticAlgoritm::startAlgoritm() {
    bool trueWhile = true;
    int itter = 0;
    printPath("Posortowana", tabOfNextGenerationGenCost, tabOfNextGenerationGen);

    mutateGen(tabOfNextGenerationGen[0], true);
    tabOfNextGenerationGenCost[0] = calculatePathCost(tabOfNextGenerationGen[0]);

    printPath("Zmutowane", tabOfNextGenerationGenCost, tabOfNextGenerationGen);
}

void GeneticAlgoritm::crosGen(std::vector<int> parent1, std::vector<int> parent2, bool mode) {
    if (mode) {//tryb true - œrodek
        // Okreœlenie punktu podzia³u (po³owy)
        int splitPoint = parent1.size() / 2;

        // Tworzenie potomka 1
        std::vector<int> child(parent1.begin(), parent1.begin() + splitPoint);

        // Dodawanie unikalnych elementów z parent2 do potomka 1
        std::unordered_set<int> uniqueElements(child.begin(), child.end());
        for (int element : parent2) {
            if (uniqueElements.find(element) == uniqueElements.end()) {
                child.push_back(element);
                uniqueElements.insert(element);
            }
        }

        // Tworzenie potomka 2
        std::vector<int> child2(parent1.begin() + splitPoint, parent1.end());

        // Dodawanie unikalnych elementów z parent2 do potomka 2
        std::unordered_set<int> uniqueElements2(child2.begin(), child2.end());
        for (int element : parent2) {
            if (uniqueElements2.find(element) == uniqueElements2.end()) {
                child2.push_back(element);
                uniqueElements2.insert(element);
            }
        }

        tabOfChildrenGen.push_back(child);
        tabOfChildrenGenCost.push_back(calculatePathCost(child));

        tabOfChildrenGen.push_back(child2);
        tabOfChildrenGenCost.push_back(calculatePathCost(child2));
    }
    else {//25% zamiany
        // Okreœlenie punktu podzia³u (25% pierwszego)
        int splitPoint = parent1.size() / 4;

        // Tworzenie potomka 1
        std::vector<int> child(parent1.begin(), parent1.begin() + splitPoint);

        // Dodawanie unikalnych elementów z parent2 do potomka 1
        std::unordered_set<int> uniqueElements(child.begin(), child.end());
        for (int element : parent2) {
            if (uniqueElements.find(element) == uniqueElements.end()) {
                child.push_back(element);
                uniqueElements.insert(element);
            }
        }

        // Tworzenie potomka 2
        std::vector<int> child2(parent1.begin() + splitPoint, parent1.end());

        // Dodawanie unikalnych elementów z parent2 do potomka 2
        std::unordered_set<int> uniqueElements2(child2.begin(), child2.end());
        for (int element : parent2) {
            if (uniqueElements2.find(element) == uniqueElements2.end()) {
                child2.push_back(element);
                uniqueElements2.insert(element);
            }
        }

        tabOfChildrenGen.push_back(child);
        tabOfChildrenGenCost.push_back(calculatePathCost(child));

        tabOfChildrenGen.push_back(child2);
        tabOfChildrenGenCost.push_back(calculatePathCost(child2));
    }

}

void GeneticAlgoritm::mutateGen(std::vector<int>& orginal, bool mode) {
    if (mode) {
        int rand1, rand2;
        do {
            rand1 = rand() % orginal.size();
        } while (rand1 < 1);

        do {
            rand2 = rand() % orginal.size();
        } while (!((rand2 > 1) && (rand2 != rand1)));

        // Zamiana miejscami elementów o indeksach rand1 i rand2
        std::swap(orginal[rand1], orginal[rand2]);
    }
    else {

        int swapSize, sourceLocation, newLocation;

        do {
            swapSize = rand() % orginal.size() * 0.9;  // Losowa d³ugoœæ fragmentu
        } while (!(swapSize > 1) && (swapSize < orginal.size() * 0.9));

        do {
            sourceLocation = rand() % orginal.size();
        } while (!((sourceLocation > 1) && (sourceLocation + swapSize <= orginal.size())));

        std::vector<int> movingCityVector(orginal.begin() + sourceLocation, orginal.begin() + sourceLocation + swapSize);

        std::vector<int> tempVectorCity;
        std::unordered_set<int> uniqueElements2(movingCityVector.begin(), movingCityVector.end());
        for (int element : orginal) {
            if (uniqueElements2.find(element) == uniqueElements2.end()) {
                tempVectorCity.push_back(element);
                uniqueElements2.insert(element);
            }
        }

        do {
            newLocation = rand() % tempVectorCity.size();
        } while (!(newLocation >= 1 && newLocation != sourceLocation));

        orginal.clear();
        for (int i = 0; i < newLocation; i++) {
            orginal.push_back(tempVectorCity[i]);
        }
        for (int i = 0; i < swapSize; i++) {
            orginal.push_back(movingCityVector[i]);
        }
        for (int i = newLocation; i < tempVectorCity.size(); i++) {
            orginal.push_back(tempVectorCity[i]);
        }
        std::cout << "swapSize = " << swapSize << std::endl;
        std::cout << "sourceLocation = " << sourceLocation << std::endl;
        std::cout << "newLocation = " << newLocation << std::endl;

    }
}