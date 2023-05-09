#pragma once
#include <iostream>
using namespace std;

class GISRecord {
private:
	int day, month, year;
public:
	GISRecord(int month = 1, int day = 1, int year = 2019);
	void display();
};