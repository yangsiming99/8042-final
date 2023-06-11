#pragma once
#include <iostream>
#include <string.h>

using namespace std;

class GISRecord 
{
private:
	string dbFileName;

public:
	GISRecord(string dbFile);
	void create_db_file();
};