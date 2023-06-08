#include "../headers/Logger.h"
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

ofstream logFile;
string c_fileName;

Logger::Logger(string fileName)
{
	c_fileName = fileName;
	//logFile.open(fileName, ios_base::app);
}

void Logger::log_command(string command)
{
	logFile.open(c_fileName, ios_base::app);
	logFile << command + "\n";
	logFile.close();
}