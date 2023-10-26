#include <vector>
class HeldKarpAlg{
public:
	void init(int** graph, int n);
	void printResult();
	int* bestTrip;
	int minCost;
private:
	int calculate(int** graph, int mask, int pos);
	std::vector<std::vector<int>> dp; // tablica dynamiczna przechowuj�ca wyniki po�rednie
	std::vector<std::vector<int>> path; // tablica przechowuj�ca �cie�ki
	void getPath(int mask, int pos,int itter);
	void showPath();
	int mask;
	int n;//Liczba miast;
	int INF;

};