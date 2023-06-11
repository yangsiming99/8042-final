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
	void log_command(string command, int& num);
	void log_comment(string comment);
	void create_log_file(string dbFN, string sFN);

private:
	string get_time();
};

#endif // !LOGGER_H
