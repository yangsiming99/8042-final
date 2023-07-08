#ifndef NAMEINDEX_H
#define NAMEINDEX_H

#include "../headers/GISRecord.h"
#include "BufferPool.h"
#include <string>
#include <vector>
#include <ostream>
#include <list>

using namespace std;

class NameIndex
{
public:
	NameIndex();
	void display();
	void insert_location(vector<string> data_container, int offset);
	GISRecord get_location(string loc);
	vector<int> get_stats();
	string* get_keys();
	GISRecord* get_list();
	string what_is(string loc, string abr, BufferPool* bp);

private:
	int hashFunction(string key);
	void resize_hash();
};

#endif // !NAMEINDEX_H