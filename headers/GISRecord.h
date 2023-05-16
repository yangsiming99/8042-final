#pragma once
#include <iostream>
#include <string.h>
using namespace std;

class GISRecord 
{
private:
	string fileName;
	void getFileContent();

public:
	GISRecord(std::string nfileName);
	void display();
};