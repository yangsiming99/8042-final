#ifndef NAMEINDEX_H
#define NAMEINDEX_H

#include <string>
#include <vector>
#include <ostream>
#include <list>

using namespace std;

class NameIndex
{
public:
	NameIndex();
	void add_location(string feature_name, string state_abbr);
	void display();

private:
	void up_size();
};

#endif // !NAMEINDEX_H