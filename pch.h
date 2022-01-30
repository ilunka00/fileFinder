#ifndef PCH_H
#define PCH_H

#include <Windows.h>
#include <iostream>
#include <string>
#include <thread>

class TestClass
{
private:
	bool found;
	std::string resultPath;
	int threads_started=0;
public:
	void fileFind(std::string& name, std::string& path);
	void testing();
};

#endif //PCH_H
