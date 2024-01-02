#include <string>
#include <vector>

class GeneticAlgoritm
{
public:
	void init(int** tabLocation, int tabLocationSize, int populationSize, int startCrosNumber, double mutatePropabylyty);
	void startAlgoritm();

	void printPath(std::string description, std::vector<int> cost, std::vector<std::vector<int>> path);

private:
	void createStartPath();
	int** tabLocation;
	int tabLocationSize;

	void sort(std::vector<int>& cost, std::vector<std::vector<int>>& path);
	int calculatePathCost(std::vector<int> path);
	std::vector<int> generateRandomPath();

	void select(bool mode);
	void sukces(bool mode);

	void mutateGen(std::vector<int>& orginal, bool mode);
	void crosGen(std::vector<int> parent1, std::vector<int> parent2, bool mode);

	std::vector<int> bestTrip;
	int bestCost;

	std::vector<std::vector<int>> tabOfParentGen;
	std::vector<int>  tabOfParentGenCost;

	std::vector<std::vector<int>> tabOfChildrenGen;
	std::vector<int>  tabOfChildrenGenCost;

	std::vector<std::vector<int>> tabOfNextGenerationGen;
	std::vector<int> tabOfNextGenerationGenCost;

	int startPopulationSize;
	int startCrosNumber;
	double startMutatePropabylyty;

	int curentPopulationSize;
	int curentCrosNumber;
	double curentMutatePropabylyty;

};