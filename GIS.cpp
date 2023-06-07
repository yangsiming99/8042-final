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

using namespace std;

void parse_commands(vector<string> command, Logger log)
{
	if (command[0] == "world")
	{
		log.world_logger();
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
	//printf("You have enterd %d arguments: \n", argc);

	//createDBFile(argv[1]);

	//for (int i = 0; i < argc; i++) {
	//	printf("%s\n", argv[i]);
	//}

	CommandProcessor cmd_proc;
	string fileName = "script01.txt";
	Logger log;

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
				vector<string> command = cmd_proc.parse_line(output);
				parse_commands(command, log);
			}
		}
	}

	return 0;
}

