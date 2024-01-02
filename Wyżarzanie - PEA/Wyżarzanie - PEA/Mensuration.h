#include <string>

#include<windows.h>
#include<stdio.h>   
#include<tchar.h>

#define DIV 1024
#define WIDTH 7

class Pomiar {

	double PCFreq = 0.0;
	__int64 CounterStart = 0;

public:
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

};