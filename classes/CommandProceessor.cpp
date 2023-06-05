#include "../headers/CommandProcessor.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

CommandProcessor::CommandProcessor()
{
}

vector<string> CommandProcessor::parse_line(string line)
{
	vector <string> cmdContainer;
	cout << line << endl;
	std::stringstream ss(line);
	string word;
	while (!ss.eof())
	{
		getline(ss, word, '\t');
		//cout << word << endl;
		cmdContainer.push_back(word);
	}
	//cout << "=========" << endl;
	return cmdContainer;
}

void CommandProcessor::parse_command(vector<string> command)
{
	if (command[0] == "world") 
	{
		cout << "DO WORLD" << endl;
	}
	else if (command[0] == "import")
	{
		cout << "DO IMPORT" << endl;
	}
	else if (command[0] == "debug")
	{
		cout << "DO DEBUG" << endl;
	}
	else if (command[0] == "quit")
	{
		cout << "DO QUIT" << endl;
	}
	else if (command[0] == "what_is_at")
	{
		cout << "DO WHAT_IS_AT" << endl;
	}
	else if (command[0] == "what_is")
	{
		cout << "DO WHAT_IS" << endl;
	}
	else if (command[0] == "what_is_in")
	{
		cout << "DO WHAT_IS_IN" << endl;
	}
	else
	{
		cout << "HOW DID YOU GET HERE?" << endl;
	}
}