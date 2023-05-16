#ifndef COMMANDPROCESSOR_H
#define COMMANDPROCESSOR_H

#include <string>


class CommandProcessor
{
public:
	CommandProcessor(std::string file_name);
	void test();
	void check_file();

private:
	std::string file_name;
	void parse_line(std::string line);

	//void cmd_world();
	//void cmd_import();
	//void cmd_debug();
	//void cmd_quit();
	//void cmd_what_is_at();
	//void cmd_what_is_in();
};

#endif // !COMMANDPROCESSOR_H
