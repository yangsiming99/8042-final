// GIS.cpp : Defines the entry point for the application.
//

#include "headers/GIS.h"
#include "headers/GISRecord.h"

using namespace std;

int main()
{
	cout << "Hello CMake." << endl;
	GISRecord randomDate(2, 14, 2019);
	randomDate.display();
	return 0;
}
