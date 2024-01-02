#include <string>
<<<<<<< HEAD

#include<windows.h>
#include<stdio.h>   
#include<tchar.h>

#define DIV 1024
#define WIDTH 7

=======
>>>>>>> 90e5141f80991f1b1268c09fab77eafdbfe6eea1
class Pomiar {

	double PCFreq = 0.0;
	__int64 CounterStart = 0;

public:
<<<<<<< HEAD
	void autoTest();//ogólne
	void autoTest2();//czas pamiêæ
	void T0Test();
	void startPathTest();
	void coolingModeTest();
	void lengthEraTest();
	void neighbourhoodSolusionTest();
	void StartCounter();
	double GetCounter();

private:
	void filewriter(std::string plik_name, std::string text);
	void file_clear(std::string plik_name, std::string initText);
	long getMemory();
=======
	void autoTest(std::string fileName, int numberInst, int numberRepeat, int minVertex, int maxVertex);
private:
	void StartCounter();
	double GetCounter();
	void filewriter(int testNumber, int reapeatNumber, std::string description, int vertexNumber, double time, std::string plik_name);
	void file_clear(std::string file_name);
>>>>>>> 90e5141f80991f1b1268c09fab77eafdbfe6eea1

};