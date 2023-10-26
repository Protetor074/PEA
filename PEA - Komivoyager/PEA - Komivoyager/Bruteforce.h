#include <vector>
#include <string>
class Bruteforce
{
public:
	
	void foundBestTrip(int n, int** tabLocation);
	void printCombination();
	void showResults();
	void filewriter(std::string fileName);
	void generateAllCombination(int n);

private:

	std::vector<int> bestTrip;
	int tripCost;
	std::vector<int> currentCombination;
	
	std::vector<std::vector<int>> allCombinations;


};
