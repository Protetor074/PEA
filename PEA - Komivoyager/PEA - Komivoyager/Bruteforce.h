#include <vector>
#include <string>
class Bruteforce
{
public:
	
	void foundBestTrip(int n, int** tabLocation);
	void printCombination();
	void showResults();
	void filewriter(std::string fileName);

private:

	std::vector<int> bestTrip;
	int tripCost;
	std::vector<int> currentCombination;
	void generateAllCombination(int n);
	std::vector<std::vector<int>> allCombinations;


};
