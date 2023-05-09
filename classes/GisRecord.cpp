// Literally here so I can make sure I know how file splitting works
#include "../headers/GISRecord.h"

GISRecord::GISRecord(int month, int day, int year) {
	this->day = day;
	this->month = month;
	this->year = year;
}

void GISRecord::display() {
	cout << month << "/" << day << "/" << year << endl;
}