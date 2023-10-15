#include "PEA - Komivoyager.h"

void Bruteforce::generateAllCombination(int n) {
    if (currentCombination.size() == n) {
        allCombinations.push_back(currentCombination);
        return;
    }

    for (int i = 1; i <= n; ++i) {
        // Sprawdzamy, czy liczba i nie jest ju¿ w bie¿¹cej kombinacji
        if (std::find(currentCombination.begin(), currentCombination.end(), i) == currentCombination.end()) {
            currentCombination.push_back(i);
            generateAllCombination(n);
            currentCombination.pop_back();
        }
    }

}

void Bruteforce::printCombination() {
    for (const auto& combination : allCombinations) {
        for (size_t i = 0; i < combination.size(); ++i) {
            std::cout << combination[i] << " ";
        }
        std::cout << std::endl;
    }
}

void Bruteforce::foundBestTrip(int n, int** tabLocation) {
    std::vector<int> curentTrip;
    int curentTripCost;
    generateAllCombination(n);
    bestTrip = allCombinations[0];
    tripCost = 0;

    /*for (int i = 0; i < bestTrip.size(); ++i) {
        std::cout << bestTrip[i] << " ";
    }
    std::cout << std::endl;*/
    //Kalkulacja startowa
    for (int i = 0; i < n - 1; i++) {
        tripCost += tabLocation[bestTrip[i]-1][bestTrip[i+1]-1];
        //std::cout << "Form " << bestTrip[i] << " to " << bestTrip[i+1] << " Cost = " << tabLocation[bestTrip[i]-1][bestTrip[i+1]-1] << std::endl;
    }
    tripCost += tabLocation[bestTrip.back()-1][bestTrip.front()-1];
    //std::cout << "Form " << bestTrip.back() << " to " << bestTrip.front() << " Cost = " << tabLocation[bestTrip.back()-1][bestTrip.front()-1] << std::endl;
    //std::cout << "Total cost = " << tripCost << std::endl << std::endl;

    for (int j = 1; j < allCombinations.size(); j++) {
        curentTrip = allCombinations[j];
        curentTripCost = 0;

        /*for (int i = 0; i < curentTrip.size(); ++i) {
            std::cout << curentTrip[i] << " ";
        }
        std::cout << std::endl;*/

        for (int i = 0; i < n - 1; i++) {
            curentTripCost += tabLocation[curentTrip[i] - 1][curentTrip[i + 1] - 1];
            //std::cout << "Form " << curentTrip[i] << " to " << curentTrip[i + 1] << " Cost = " << tabLocation[curentTrip[i] - 1][curentTrip[i + 1] - 1] << std::endl;
        }
        curentTripCost += tabLocation[curentTrip.back()-1][curentTrip.front()-1];
        //std::cout << "Form " << curentTrip.back() << " to " << curentTrip.front() << " Cost = " << tabLocation[curentTrip.back()-1][curentTrip.front()-1] << std::endl;
        //std::cout << "Curent cost = " << curentTripCost << std::endl;
        if (curentTripCost < tripCost) {
            tripCost = curentTripCost;
            bestTrip = curentTrip;
        }
        //std::cout << "Total cost = " << tripCost << std::endl << std::endl;
    }
    allCombinations.clear();
}

void Bruteforce::showResults() {
    for (int i = 0; i < bestTrip.size(); ++i) {
        std::cout << bestTrip[i] << " ";
    }
    std::cout << "Total cost = " << tripCost << std::endl;
}

void Bruteforce::filewriter(std::string fileName) {
    std::fstream plik;
    int liczba;

    plik.open(fileName, std::ios::out);

    plik << "Trip :";
    for (int i = 0; i < bestTrip.size(); ++i) {
       plik << bestTrip[i] << " ";
    }
    plik << bestTrip.back();
    plik << "\nTotal Cost = " << tripCost;
    plik.close();
}