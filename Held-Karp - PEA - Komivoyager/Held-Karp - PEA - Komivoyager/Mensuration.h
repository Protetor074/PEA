#include <string>
class Pomiar {

	double PCFreq = 0.0;
	__int64 CounterStart = 0;

public:
	void test();
private:
	void StartCounter();
	double GetCounter();
	void filewriter(double time_list, double time_matrix, std::string plik_name, std::string description, int density, int vertex_number);
	void file_clear(std::string file_name);
};