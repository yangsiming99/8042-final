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
#include "headers/BufferPool.h"

using namespace std;

int global = 20;
SystemManager sysm;
CommandProcessor cmd_proc;
NameIndex ni;


void parse_commands(vector<string> command, Logger lg, BufferPool* bp)
{
	if (command[0] == "world")
	{
		sysm.set_world(command);
		lg.log_world(sysm.get_bounds());
	}
	else if (command[0] == "import")
	{
		cmd_proc.cmd_import(command, sysm.get_bounds(), ni);
		lg.log_import(ni);
	}
	else if (command[0] == "debug")
	{
		if (command[1] == "world")
		{
			lg.log_debug_world(ni, sysm.get_bounds());
		}
		else if (command[1] == "hash") 
		{
			lg.log_debug_hash(ni);
		}
		else if (command[1] == "pool")
		{
			lg.log_debug_pool(bp);
		}
		else if (command[1] == "quad")
		{

		}
	}
	else if (command[0] == "quit")
	{
		exit(1);
	}
	else if (command[0] == "what_is_at")
	{
		cout << "DO WHAT_IS_AT" << endl;
	}
	else if (command[0] == "what_is")
	{
		string result = ni.what_is(command[1], command[2], bp);
		lg.log(result);
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

	string dbPath = "VA_Monterey.txt";
    BufferPool *pool = new BufferPool(dbPath);

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
				log.log("--------------------------------------------------------------------------");
				log.log_command(output, counter);
				vector<string> command = cmd_proc.parse_line(output);
				parse_commands(command, log, pool);
			}
			else
			{
				log.log(output);
			}
		}
	}

	//ni.display();

	return 0;
}

