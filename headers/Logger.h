#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

class Logger
{
public:
	Logger(string fileName);
	void log_command(string command);

private:
};

#endif // !LOGGER_H
