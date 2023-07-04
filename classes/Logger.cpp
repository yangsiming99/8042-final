#include "../headers/Logger.h"
#include "../headers/NameIndex.h"
#include "../headers/GisRecord.h"
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

void Logger::log_world(vector<double> bounds)
{
	log_comment("\t\t" + to_string( bounds[2]));
	log_comment(to_string(bounds[0]) + "\t\t" + to_string(bounds[1]));
	log_comment("\t\t" + to_string(bounds[3]));
}

void Logger::log_import(NameIndex ni)
{
	auto stats = ni.get_stats();
	log_comment("");
	log_comment("Current Table size is " + std::to_string(stats[1]));
	log_comment("Number of Elements in table is " + std::to_string(stats[0]));
	log_comment("");
	string* keys = ni.get_keys();
	GISRecord* recordList = ni.get_list();
	//ni.display();
	for (int i = 0; i < stats[1]; i++) // Use stats[0] instead of test[i] for loop condition
	{
		if (!keys[i].empty())
		{
			log_comment("\t" + to_string(i) + ": [" + keys[i] + ", " + recordList[i].getState_alpha() + "]");
		}
	}
}

void Logger::log_debug()
{

}

void Logger::log_comment(string comment)
{
	logFile.open(c_fileName, ios_base::app);
	logFile << comment + "\n";
	logFile.close();
}