// GIS.cpp : Defines the entry point for the application.
//
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <vector>
#include "headers/GIS.h"
#include "headers/GISRecord.h"
#include "headers/CommandProcessor.h"
#include "headers/Logger.h"

using namespace std;

int main(int argc, char* argv[])
{
	//printf("You have enterd %d arguments: \n", argc);

	//createDBFile(argv[1]);

	//for (int i = 0; i < argc; i++) {
	//	printf("%s\n", argv[i]);
	//}

	CommandProcessor cmd_proc;
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
				vector<string> command = cmd_proc.parse_line(output);
				cmd_proc.parse_command(command);
			}
		}
	}

	return 0;
}

