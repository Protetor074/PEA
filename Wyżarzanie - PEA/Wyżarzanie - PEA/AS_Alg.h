#include <vector>
#include <string>
#include <random>


class AS_Alg {

public:
<<<<<<< HEAD
	void init(int** tabLocation, int tabLocationSize, bool initPathGeneratorMode, bool startTempMode, double avgTestVertx, double lCorectionVal, int eraLongMode);
    void startAlgoritmGeo(double alpha, bool selectVertexMode, double probability);
    void startAlgoritmBoltzmann(bool selectVertexMode, double probability);
    void printPath(std::string description);
    void clean();

    void setEraLong(int mode);

    int getCurentCost();
    std::string getCurentPath();
    int getNumberK();
    int getCurentTemp();

    void generateMaxInitialTemperature(int minTemperature, int maxTemperature);
    void generateInitialTemperatureFromAverage(int n);

    void generateRandomPath();
    void generateNearestNeighborPath();
    std::vector<int> getMinMaxCost();

    std::vector<int> initPath;
    std::vector<int> currentPath;
    double initialTemperature;
    double currentTemperature;

    int curentCost;
    int initCost;

    void refreshItterationSize(double val);

=======
	void init(int** tabLocation, int tabLocationSize, int minTripVal, int maxTripVal, bool initPathGeneratorMode, bool startTempMode, int avgTestVertx);
    void startAlgoritmGeo(double alpha, bool selectVertexMode, double probability, int iterationNumber, int iterationSize);
    void startAlgoritmBoltzmann(bool selectVertexMode, double probability, int iterationNumber, int iterationSize);
    void printPath(std::string description);
    void clean();
>>>>>>> 90e5141f80991f1b1268c09fab77eafdbfe6eea1
private:
    int** tabLocation;
    int tabLocationSize;
    int minTripVal;
    int maxTripVal;
<<<<<<< HEAD
    std::vector<int> min_maxCost;
   
    std::vector<int> newPath;
  
    int newCost;
    double lCorectionVal;
    int iterationSize;
    int k;
=======
    std::vector<int> currentPath;
    std::vector<int> newPath;
    int curentCost;
    int newCost;
>>>>>>> 90e5141f80991f1b1268c09fab77eafdbfe6eea1

    //int iterationNumber;//liczba stopni
    //int iterationSize;//liczba powtórzeñ na poszczególnych stopniach

    double probabilityVal;

    int maxINT = INT_MAX;
<<<<<<< HEAD

    void calculatePathCost();
    
=======
    double initialTemperature;
    double currentTemperature;

    void generateRandomPath();
    void generateNearestNeighborPath();
    void calculatePathCost();
    void generateRandomInitialTemperature(int minTemperature, int maxTemperature);
    void generateInitialTemperatureFromAverage(int n);
>>>>>>> 90e5141f80991f1b1268c09fab77eafdbfe6eea1

    void swapVerticesAndUpdateCost(int index1, int index2);
    void moveVertexLeft(int index);
    bool acceptanceProbability(double currentCost, double newCost, double temperature, double probability);

<<<<<<< HEAD
    void foundMinMaxTripCost();
    
    //void shuffle(std::vector<int>& currentPath);

=======
>>>>>>> 90e5141f80991f1b1268c09fab77eafdbfe6eea1
};