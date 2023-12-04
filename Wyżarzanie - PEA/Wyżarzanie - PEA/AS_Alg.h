#include <vector>
#include <string>
#include <random>


class AS_Alg {

public:
	void init(int** tabLocation, int tabLocationSize, int minTripVal, int maxTripVal, bool initPathGeneratorMode, bool startTempMode, int avgTestVertx);
    void startAlgoritmGeo(double alpha, bool selectVertexMode, double probability, int iterationNumber, int iterationSize);
    void startAlgoritmBoltzmann(bool selectVertexMode, double probability, int iterationNumber, int iterationSize);
    void printPath(std::string description);
    void clean();
private:
    int** tabLocation;
    int tabLocationSize;
    int minTripVal;
    int maxTripVal;
    std::vector<int> currentPath;
    std::vector<int> newPath;
    int curentCost;
    int newCost;

    //int iterationNumber;//liczba stopni
    //int iterationSize;//liczba powtórzeñ na poszczególnych stopniach

    double probabilityVal;

    int maxINT = INT_MAX;
    double initialTemperature;
    double currentTemperature;

    void generateRandomPath();
    void generateNearestNeighborPath();
    void calculatePathCost();
    void generateRandomInitialTemperature(int minTemperature, int maxTemperature);
    void generateInitialTemperatureFromAverage(int n);

    void swapVerticesAndUpdateCost(int index1, int index2);
    void moveVertexLeft(int index);
    bool acceptanceProbability(double currentCost, double newCost, double temperature, double probability);

};