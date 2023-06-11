#include "../headers/Logger.h"
#include <string>
#include <iostream>
#include <fstream>
#include <format>
#include <ctime>
#include <iomanip>
#include <sstream>

using namespace std;

ofstream logFile;
string c_fileName;

Logger::Logger(string fileName)
{
	c_fileName = fileName;
	//logFile.open(fileName, ios_base::app);
}

void Logger::create_log_file(string dbFN, string sFN)
{
	logFile.open(c_fileName, ios_base::trunc);
	logFile << "Course Project for COMP 8042\n";
	logFile << format("Student Name: {}, Student Id: {}\n", "Siming & Abeer", "A01019984 & ENTER # Here");
	logFile << "Begin of GIS Program log:\n";
	logFile << format("dbFile:\t{}\n", dbFN);
	logFile << format("script:\t{}\n", sFN);
	logFile << format("log:\t{}\n", c_fileName);
	logFile << format("Start Time: {}\n", get_time());
	get_time();
	logFile.close();
}

string Logger::get_time()
{
	auto t = time(nullptr);
	auto tm = *localtime(&t);
	ostringstream oss;
	oss << put_time(&tm, "%a %b %d %T %Z %Y");
	auto str = oss.str();

	return str;
}

void Logger::log_command(string command, int& num)
{
	logFile.open(c_fileName, ios_base::app);
	if (command.find("world\t") != string::npos)
	{
		logFile << command + "\n";
	}
	else
	{
		logFile << format("COMMAND {}:\t{}\n", num, command);
		num++;
	}
	
	logFile.close();
}

void Logger::log_comment(string comment)
{
	logFile.open(c_fileName, ios_base::app);
	logFile << comment + "\n";
	logFile.close();
}