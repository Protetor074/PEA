#include "Held-Karp - PEA - Komivoyager.h"
int HeldKarpAlg::calculate(int** graph, int mask, int pos) {
    // Jeœli odwiedzono wszystkie miasta, wróæ do miasta pocz¹tkowego
    if (mask == (1 << n) - 1) {
        return graph[pos][0];
    }

    // Jeœli wynik zosta³ ju¿ obliczony, zwróæ go
    if (dp[mask][pos] != -1) {
        return dp[mask][pos];
    }

    int ans = INF;
    int next = -1;
    // PrzejdŸ przez wszystkie miasta
    for (int i = 0; i < n; ++i) {
        // Jeœli miasto i nie zosta³o odwiedzone, odwiedŸ je
        if ((mask & (1 << i)) == 0) {
            int newMask = mask | (1 << i);
            //Wywo³anie
            std::cout << mask <<" - " << newMask << std::endl;
            int cost = graph[pos][i] + calculate(graph,newMask, i);
            if (cost < ans) {
                ans = cost;
                next = i;
            }
        }
    }

    // Zapamiêtaj œcie¿kê
    path[mask][pos] = next;

    // Zapamiêtaj wynik dla danej maski i pozycji
    dp[mask][pos] = ans;
    return ans;
}

void HeldKarpAlg::init(int** graph,int n) {
    // Inicjalizuj tablice wyników poœrednich i œcie¿ek
    std::string* result = new std::string[2];
    INF = INT_MAX;
    this->n = n;
    dp.clear();
    path.clear();
    dp.resize(1 << n, std::vector<int>(n, -1));
    path.resize(1 << n, std::vector<int>(n, -1));
    bestTrip = new int[n + 1];
    mask = 1; // Maska reprezentuj¹ca odwiedzone miasta (miasto pocz¹tkowe jest ju¿ odwiedzone)
    minCost = calculate(graph, mask, 0);
    //std::cout << minCost<<std::endl;
}

void HeldKarpAlg::getPath(int mask, int pos,int itter) {
    if (mask == (1 << n) - 1) {
        //std::cout << pos+1 << " -> " << 1 << std::endl;
        bestTrip[itter] = pos + 1;
        bestTrip[itter+1] = 1;
        return;
    }
    int next = path[mask][pos];
    //std::cout << pos+1 << " -> " << next+1 << std::endl;
    bestTrip[itter] = pos + 1;
    getPath(mask | (1 << next), next,itter+1);
}

std::vector<std::string> HeldKarpAlg::printResult() {
    getPath(mask, 0, 0);
    std::vector<std::string> result(2);
    std::cout << "\nMinimalny koszt cyklu komiwojazera: " << minCost << std::endl;
    result[0] = "Minimalny koszt cyklu komiwojazera : " + std::to_string(minCost);
    std::cout << "Kolejnosc odwiedzanych miast: ";
    result[1] = "Kolejnosc odwiedzanych miast: " + showPath();
    return result;
}

std::string HeldKarpAlg::showPath() {
    std::string path;
    for (int i = 0; i <= n; i++) {
        std::cout << bestTrip[i] << " ";
        path = path + std::to_string(bestTrip[i]) + " ";
    }
    std::cout << std::endl;
    return path;
}

