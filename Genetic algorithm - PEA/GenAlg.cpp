#include "Genetic algorithm - PEA.h"
#include <algorithm>
#include <unordered_set>


void GeneticAlgoritm::init(int** tabLocation, int tabLocationSize, int populationSize, int startCrosNumber, double mutatePropabylyty) {
    //liczba generacji
    //liczba mutacji na generację
    // Liczba krzyżówek na generacjię
    //lpopulacji na generację

    this->startPopulationSize = populationSize;
    this->startCrosNumber = startCrosNumber;
    this->startMutatePropabylyty = mutatePropabylyty;

    this->tabLocation = tabLocation;
    this->tabLocationSize = tabLocationSize;

    createStartPath();
    sort(tabOfNextGenerationGenCost, tabOfNextGenerationGen);
    srand(time(NULL));
    bestCost = tabOfNextGenerationGenCost[0];
    bestTrip = tabOfNextGenerationGen[0];
}

//Funkcja sortująca ścieżki po koszcie
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

//Funkcja tworząca początkowy zestaw ścieżek
void GeneticAlgoritm::createStartPath() {
    tabOfNextGenerationGen.resize(startPopulationSize);
    tabOfNextGenerationGenCost.resize(startPopulationSize);

    for (int i = 0; i < startPopulationSize; i++) {
        tabOfNextGenerationGen[i] = generateRandomPath();
        tabOfNextGenerationGenCost[i] = calculatePathCost(tabOfNextGenerationGen[i]);
    }
}

// Funkcja wyznaczająca koszt ścieżki
int GeneticAlgoritm::calculatePathCost(std::vector<int> path) {
    int cost = 0;
    for (size_t i = 0; i < tabLocationSize - 1; ++i) {
        int city1 = path[i];  // Indeksowanie od zera
        int city2 = path[i + 1];

        cost += tabLocation[city1][city2];
    }

    // Dodaj koszt przejścia z ostatniego do pierwszego miasta
    cost += tabLocation[path.back()][path.front()];
    return cost;
}

// Funkcja generująca zachłannie ścieżkę
std::vector<int> GeneticAlgoritm::generateRandomPath() {
    std::vector<int> path;

    for (int i = 0; i < tabLocationSize; ++i) {
        path.push_back(i);
    }

    std::random_device rd;  // U�yj generatora sprz�towego do uzyskania ziarna
    std::mt19937 gen(rd()); // U�yj algorytmu Mersenne Twister   

    // Losowe przemieszanie �cie�ki
    std::shuffle(path.begin()+1, path.end(), gen);
    return path;
}

// Funkcja pomocnicza do wyświetlania ścieżki
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

void GeneticAlgoritm::startAlgoritm(bool croosMode, bool mutateMode, bool succesionMode, double succesionProcent, bool sellectionMode, int maxIterationWithoutBetterVall, int expectedPathCost, std::string fileName, bool descriptionAdd, bool movingPopulationSize, bool movingCrossNumber, bool movingMutationPropabylyty) {
    bool trueWhile = true;
    int itter = 0;
    int generationNumber = 0;
    int curentMutatinNumber = 0;
    curentPopulationSize = startPopulationSize;
    curentCrosNumber = startCrosNumber;
    curentMutatePropabylyty = startMutatePropabylyty;
    int rand1, rand2;

    if (descriptionAdd) {
        file_clear(fileName, "NumerGeneracji;Wielkość Populacji;Liczba Krzyżowań;Liczba Mutacji;Prawdopodobieństwo Mutacji;Optymalna Ścieżka;Najlepsza Ścieżka;Najlepsza w danej Populacji");
    }

    do {
        //Czyszczenie
        tabOfChildrenGen.clear();
        tabOfChildrenGenCost.clear();
        tabOfParentGen.clear();
        tabOfParentGenCost.clear();
       

        //Kopiowanie nowej generacji do aktualnych rodziców
        for (const auto& element : tabOfNextGenerationGen) {
            tabOfParentGen.push_back(element);
        }

        //Kopiowanie kosztów nowej generacji do aktualnych rodziców
        for (const auto& element : tabOfNextGenerationGenCost) {
            tabOfParentGenCost.push_back(element);
        }
        tabOfNextGenerationGen.clear();
        tabOfNextGenerationGenCost.clear();

        //Tworzenie krzyżówek
        for (int i = 0; i < curentCrosNumber;i++) {
            rand1 = rand() % tabOfParentGen.size();
            do {
                rand2 = rand()% tabOfParentGen.size();
            } while (rand1 == rand2);

            crosGen(tabOfParentGen[rand1], tabOfParentGen[rand2], croosMode);
        }

        //Mutacja genu
        for (int i = 0; i < tabOfParentGen.size(); i++) {
            //Prawdopodobieństwo mutacji

            rand1 = rand() % 100;
            do {//W celu zapewnienia losowości i uniknięcia częstego losowania takiej samej liczby
                rand2 = rand() % 100;
            } while (rand1 == rand2);
            if (((rand1 + rand2) / 2) < curentMutatePropabylyty * 100) {
                rand1 = rand() % tabOfParentGen.size();
                do {//W celu zapewnienia losowości i uniknięcia częstego losowania takiej samej liczby
                    rand2 = rand() % tabOfParentGen.size();
                } while (rand1 == rand2);
                mutateGen(tabOfParentGen[rand1], mutateMode);
                tabOfParentGenCost[0] = calculatePathCost(tabOfParentGen[0]);
                curentMutatinNumber++;
            }
        }

        //Sukcesja
        sukcession(succesionMode, succesionProcent);

        //Selekcja
        selection(sellectionMode);

        if (bestCost > tabOfNextGenerationGenCost[0]) {
            bestCost = tabOfNextGenerationGenCost[0];
            bestTrip = tabOfNextGenerationGen[0];
            //Przywracanie wartości początkowej
            curentPopulationSize = startPopulationSize;
            curentCrosNumber = startCrosNumber;
            curentMutatePropabylyty = startMutatePropabylyty;
            itter = 0;
        }
        else {
            if (movingPopulationSize) {
                curentPopulationSize++;
            }
            if (movingCrossNumber) {
                curentCrosNumber++;
            }
            if (movingMutationPropabylyty) {
                if (curentMutatePropabylyty < 0.9) {
                    curentMutatePropabylyty += 0.0016;
                }
            }
            itter++;
        }

        //Przez ostatnie maxIterationWithoutBetterVall generacji nie zanotowano zmian zakończ
        if (itter == maxIterationWithoutBetterVall) {
            trueWhile = false;
            endType = "Maksymalna liczba iteracji Bez zmian";
        }

        //Oczekiwany wynik jest optymalny
        if (expectedPathCost == bestCost) {
            trueWhile = false;
            endType = "Znaleziono najlepszy wynok";
        }

        if (tabLocationSize > 100) {
            //Osiągnięto 25 000 generacji
            if (generationNumber == 25000) {
                trueWhile = false;
                endType = "Osiągnięto maksymalną liczbę generacji - 25000";
            }
        }
        else
        {
            //Osiągnięto 15 000 generacji
            if (generationNumber == 15000) {
                trueWhile = false;
                endType = "Osiągnięto maksymalną liczbę generacji - 15000";
            }
        }

        if (descriptionAdd) {
            extraDescription(fileName, std::to_string(generationNumber) + ";" + std::to_string(curentPopulationSize) + ";" + std::to_string(curentCrosNumber) + ";" + std::to_string(curentMutatinNumber) + ";" + std::to_string(curentMutatePropabylyty) + ";" + std::to_string(expectedPathCost) + ";" + std::to_string(bestCost) + ";" + std::to_string(tabOfNextGenerationGenCost[0]));
        }
        generationNumber++;
        curentMutatinNumber = 0;

    } while (trueWhile);
}

void GeneticAlgoritm::crosGen(std::vector<int> parent1, std::vector<int> parent2, bool mode) {
    if (mode) {//tryb true - środek
        // Określenie punktu podziału (połowy)
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
        // Określenie punktu podziału (25% pierwszego)
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

void GeneticAlgoritm::mutateGen(std::vector<int> orginal, bool mode) {
    //std::cout << "\nOrginalCostStart = " << calculatePathCost(orginal);
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

        tabOfChildrenGen.push_back(orginal);
        tabOfChildrenGenCost.push_back(calculatePathCost(orginal));
        //std::cout << "\nOrginalCostStart = " << calculatePathCost(orginal);
    }
    else {

        int swapSize, sourceLocation, newLocation;

        do {
            swapSize = rand() % orginal.size() * 0.9;  // Losowa długość fragmentu
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

        tabOfChildrenGen.push_back(orginal);
        tabOfChildrenGenCost.push_back(calculatePathCost(orginal));
        /*std::cout << "swapSize = " << swapSize << std::endl;
        std::cout << "sourceLocation = " << sourceLocation << std::endl;
        std::cout << "newLocation = " << newLocation << std::endl;*/

    }
}

void GeneticAlgoritm::sukcession(bool mode, double procent) {
    if (mode) {//Najlepsze
        sort(tabOfParentGenCost, tabOfParentGen);
        for (int i = 0; i < (tabOfParentGen.size() * procent); ++i) {
            tabOfNextGenerationGen.push_back(tabOfParentGen[i]);
            tabOfNextGenerationGenCost.push_back(tabOfParentGenCost[i]);
        }
    }
    else {//Losowe
        // Generowanie unikalnych liczb losowych
        std::vector<int> randomNumbers;
        for (int i = 0; i < (tabOfParentGen.size() * procent); ++i) {
            int liczbaLosowa;
            bool unique;

            do {
                liczbaLosowa = std::rand() % tabOfParentGen.size();

                // Sprawdź czy liczba jest unikalna
                unique = true;
                for (const auto& liczba : randomNumbers) {
                    if (liczba == liczbaLosowa) {
                        unique = false;
                        break;
                    }
                }
            } while (!unique);

            // Dodaj unikalną liczbę do wektora
            randomNumbers.push_back(liczbaLosowa);
        }

        //Zachowanie najlepszego osobnika w populacji
        tabOfNextGenerationGen.push_back(tabOfParentGen[randomNumbers[0]]);
        tabOfNextGenerationGenCost.push_back(tabOfParentGenCost[randomNumbers[0]]);

        for (int i = 1; i < randomNumbers.size()-1; i++) {
            tabOfNextGenerationGen.push_back(tabOfParentGen[randomNumbers[i]]);
            tabOfNextGenerationGenCost.push_back(tabOfParentGenCost[randomNumbers[i]]);
        }
    }
}

void GeneticAlgoritm::selection(bool mode) {
    if (mode) {//stare 10%/ nowe 90%
        sort(tabOfNextGenerationGenCost, tabOfNextGenerationGen);

        int toRemove = tabOfNextGenerationGenCost.size() - (curentPopulationSize * 0.1);

        //Pozbywamy się starego do 10% populacji najlepszych rodziców
        for (int i = 0; i < toRemove; i++) {
            tabOfNextGenerationGen.erase(tabOfNextGenerationGen.end()-1);
            tabOfNextGenerationGenCost.erase(tabOfNextGenerationGenCost.end()-1);
        }
       
        sort(tabOfChildrenGenCost, tabOfChildrenGen);

        //Kopiujemy do 100% populacji
        for (int i = 0; i < tabOfChildrenGen.size(); i++) {
            tabOfNextGenerationGen.push_back(tabOfChildrenGen[i]);
            tabOfNextGenerationGenCost.push_back(tabOfChildrenGenCost[i]);
        }
    }
    else {//stare50%/ nowe 50%
        sort(tabOfNextGenerationGenCost, tabOfNextGenerationGen);

        int toRemove = tabOfNextGenerationGenCost.size() - (curentPopulationSize * 0.5);

        //Pozbywamy się starego do 50% populacji najlepszych rodziców
        for (int i = 0; i < toRemove; i++) {
            tabOfNextGenerationGen.erase(tabOfNextGenerationGen.end()-1);
            tabOfNextGenerationGenCost.erase(tabOfNextGenerationGenCost.end()-1);
        }
       
        sort(tabOfChildrenGenCost, tabOfChildrenGen);

        //Kopiujemy do 100% populacji
        for (int i = 0; i < tabOfChildrenGen.size(); i++) {
            tabOfNextGenerationGen.push_back(tabOfChildrenGen[i]);
            tabOfNextGenerationGenCost.push_back(tabOfChildrenGenCost[i]);
        }
    }
    sort(tabOfNextGenerationGenCost, tabOfNextGenerationGen);

}

void GeneticAlgoritm::printPath(std::string description) {
    std::cout << description << std::endl;
    for (const auto& city : tabOfNextGenerationGen[0]) {
        std::cout << city << " ";
    }
    std::cout << std::endl;
    std::cout << "Koszt = " << tabOfNextGenerationGenCost[0] << std::endl;
}

void GeneticAlgoritm::extraDescription(std::string plik_name, std::string text) {
    std::fstream plik;
    plik.open(plik_name, std::ios::app);
    plik << text << std::endl;
    plik.close();
}

void GeneticAlgoritm::file_clear(std::string plik_name, std::string initText) {
    std::fstream plik;
    plik.open(plik_name, std::ios::out);
    plik << initText << std::endl;
    plik.close();
}