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
#include "headers/NameIndex.h"

using namespace std;

int global = 20;
SystemManager sysm;
CommandProcessor cmd_proc;
NameIndex ni;

void parse_commands(vector<string> command, Logger lg)
{
	if (command[0] == "world")
	{
		sysm.set_world(command);
		lg.log_world(sysm.get_bounds());
		cout << "DO WORLD" << endl;
	}
	else if (command[0] == "import")
	{
		cmd_proc.cmd_import(command, sysm.get_bounds(), ni);
		lg.log_import(ni);
		cout << "DO IMPORT" << endl;
	}
	else if (command[0] == "debug")
	{
		if (command[1] == "hash") {
			int x = 0;
		}
		cout << "DO DEBUG" << endl;
	}
	else if (command[0] == "quit")
	{
		cout << "DO QUIT" << endl;
		exit(1);
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

	// GISRecord db("dbfile.txt");
	// db.create_db_file();

	Logger log("logFile.txt");
	log.create_log_file(argv[1], argv[2]);
	int counter = 1;
	cmd_proc.db_fileName = "dbfile.txt";
	cmd_proc.create_db_file();
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
				parse_commands(command, log);
			}
			else
			{
				log.log_comment(output);
			}
		}
	}

	//ni.display();

	return 0;
}

