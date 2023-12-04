#include <string>
class KomivoyagerLocation
{
public:
	int** tabLocation;
	int size;
	void printTab();
	void set(std::string fileName);
	void generate(int size, int minValue,int maxValue, bool symetric);
private:
	void create(int size);

};