#ifndef COMMANDPROCESSOR_H
#define COMMANDPROCESSOR_H

#include <string>
#include <vector>

using namespace std;

class CommandProcessor
{
public:
	CommandProcessor();
	vector<string> parse_line(string line);
	void parse_command(vector<string> command);

private:
	

	//void cmd_world();
	//void cmd_import();
	//void cmd_debug();
	//void cmd_quit();
	//void cmd_what_is_at();
	//void cmd_what_is_in();
};

#endif // !COMMANDPROCESSOR_H
