#include <string>
#include <vector>

class GeneticAlgoritm
{
public:
	void init(int** tabLocation, int tabLocationSize, int populationSize, int startCrosNumber, double mutatePropabylyty);
	void startAlgoritm(bool croosMode, bool mutateMode, bool succesionMode, double succesionProcent, bool sellectionMode, int maxIterationWithoutBetterVall, int expectedPathCost, std::string fileName, bool descriptionAdd, bool movingPopulationSize, bool movingCrossNumber, bool movingMutationPropabylyty);
	void printPath(std::string description);
	int bestCost;
	std::string endType;

private:
	void createStartPath();
	int** tabLocation;
	int tabLocationSize;

	void printPath(std::string description, std::vector<int> cost, std::vector<std::vector<int>> path);

	void sort(std::vector<int>& cost, std::vector<std::vector<int>>& path);
	int calculatePathCost(std::vector<int> path);
	std::vector<int> generateRandomPath();

	void select(bool mode);
	void sukces(bool mode);

	void mutateGen(std::vector<int> orginal, bool mode);
	void crosGen(std::vector<int> parent1, std::vector<int> parent2, bool mode);
	void sukcession(bool mode,double procent);
	void selection(bool mode);

	std::vector<int> bestTrip;
	
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


	void extraDescription(std::string plik_name, std::string text);
	void file_clear(std::string plik_name, std::string initText);

};