#include <string>
class Pomiar {

	double PCFreq = 0.0;
	__int64 CounterStart = 0;

public:
	void autoTest(std::string fileName,int numberInst,int numberRepeat,int minVertex,int maxVertex);
private:
	void StartCounter();
	double GetCounter();
	void filewriter(int testNumber, int reapeatNumber, std::string description, int vertexNumber, double time, std::string plik_name);
	void file_clear(std::string file_name);
	
};