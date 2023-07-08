#ifndef COMMANDPROCESSOR_H
#define COMMANDPROCESSOR_H

#include "../headers/NameIndex.h"
#include "../headers/CoordinateIndex.h"
#include <string>
#include <vector>
#include <ostream>

using namespace std;

class CommandProcessor
{
public:
	CommandProcessor();
	vector<string> parse_line(string line);
	void cmd_import(vector<string> cmd, vector<double>, NameIndex ni, CoordinateIndex ci);
	void create_db_file();
	string db_fileName;
	//enum{all the commands};
	int removeDecimal(double d);
private:
	//void read_cmd(); //depending on arguments, call the specific command from this function. check GIS.CPP and the Parse Commands function
	//void cmd_world();
	//void cmd_import();
	//void cmd_debug();
	//void cmd_quit();
	//void cmd_what_is_at();
	//void cmd_what_is_in();
};

#endif // !COMMANDPROCESSOR_H
