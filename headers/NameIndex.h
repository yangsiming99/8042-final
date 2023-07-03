#ifndef NAMEINDEX_H
#define NAMEINDEX_H

#include "../headers/GisRecord.h"
#include <string>
#include <vector>
#include <ostream>
#include <list>

using namespace std;

class NameIndex
{
public:
	NameIndex();
	void add_location(int line, vector<string> data_container);
	void display();
	void insert_location(vector<string> data_container, int offset);
	GISRecord get_location(string loc);

private:
	void up_size();
	int hashFunction(string key);
	void resize_hash();
};

#endif // !NAMEINDEX_H