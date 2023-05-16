// GIS.cpp : Defines the entry point for the application.
//
#include <stdio.h>
#include <string.h>
#include <fstream>

#include "headers/GIS.h"
#include "headers/GISRecord.h"
#include "headers/CommandProcessor.h"

using namespace std;

void createDBFile(char fileName[])
{
	ifstream file;

	file.open(fileName);

	if (file) 
	{
		cout << "File Exists" << endl;
	}
	else 
	{
		cout << "File does not exist" << endl;
	}
}

void checkScriptFile() 
{

}

void checkLogFile() 
{

}

int main(int argc, char* argv[])
{
	//printf("You have enterd %d arguments: \n", argc);

	//createDBFile(argv[1]);

	//for (int i = 0; i < argc; i++) {
	//	printf("%s\n", argv[i]);
	//}

	CommandProcessor cmd_proc("script01.txt");
	cmd_proc.check_file();

	return 0;
}

