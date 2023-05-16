// Literally here so I can make sure I know how file splitting works
#include "../headers/GISRecord.h"
#include <string.h>
#include <fstream>

using namespace std;

GISRecord::GISRecord(string nfileName) 
{
	this->fileName = nfileName;
}

void GISRecord::getFileContent() 
{
	ifstream file;
	file.open(fileName);
	if (file)
	{
		cout << "File Exists" << endl;
	}
	else
	{
		cout << "file does not exist" << endl;
	}
}

void GISRecord::display() 
{
	//cout << month << "/" << day << "/" << year << endl;
	cout << fileName;
	return;
}