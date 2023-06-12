#include "../headers/GISRecord.h"
#include <string.h>
#include <fstream>
#include <iostream>

using namespace std;

//idk, use this for database stuff I guess

ofstream db_File;
string dbFileName;

GISRecord::GISRecord(string ndbFile) 
{
	dbFileName = ndbFile;
}

void GISRecord::create_db_file()
{
	cout << "hi there" << endl;
	db_File.open(dbFileName, ios_base::trunc);
	db_File << "THIS IS THE DB FILE SDKLFJSLK \n";
	db_File.close();
}