// GIS.cpp : Defines the entry point for the application.
//
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <vector>
#include <iostream>
#include "headers/GIS.h"
#include "headers/GISRecord.h"
#include "headers/CommandProcessor.h"
#include "headers/Logger.h"
#include "headers/SystemManager.h"

using namespace std;

int global = 20;
SystemManager sysm;

void parse_commands(vector<string> command)
{
	if (command[0] == "world")
	{
		sysm.set_world(command);
		cout << "DO WORLD" << endl;
	}
	else if (command[0] == "import")
	{
		cout << "DO IMPORT" << endl;
	}
	else if (command[0] == "debug")
	{
		cout << "DO DEBUG" << endl;
	}
	else if (command[0] == "quit")
	{
		cout << "DO QUIT" << endl;
	}
	else if (command[0] == "what_is_at")
	{
		cout << "DO WHAT_IS_AT" << endl;
	}
	else if (command[0] == "what_is")
	{
		cout << "DO WHAT_IS" << endl;
	}
	else if (command[0] == "what_is_in")
	{
		cout << "DO WHAT_IS_IN" << endl;
	}
	else
	{
		cout << "HOW DID YOU GET HERE?" << endl;
	}
}

int main(int argc, char* argv[])
{
	printf("You have enterd %d arguments: \n", argc);

	//argv[1] - database
	//argv[2] - commandscript
	//argv[3] - logfile.txt

	CommandProcessor cmd_proc;
	// GISRecord db("dbfile.txt");
	// db.create_db_file();
	
	Logger log("logFile.txt");
	log.create_log_file(argv[1], argv[2]);
	int counter = 1;

	string fileName = "script01.txt";

	ifstream file;
	file.open(fileName);
	if (file)
	{
		string output;
		ifstream myReadFile(fileName);
		while (getline(myReadFile, output))
		{
			if (output.length() != 0 && output.front() != ';')
			{
				log.log_command(output, counter);
				vector<string> command = cmd_proc.parse_line(output);
				parse_commands(command);
			}
			else
			{
				log.log_comment(output);
			}
		}
	}

	return 0;
}

