#include "../headers/CommandProcessor.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

CommandProcessor::CommandProcessor(std::string file_name)
{
	this->file_name = file_name;
}

void CommandProcessor::check_file()
{
	ifstream file;
	file.open(file_name);
	if (file)
	{
		string output;
		ifstream MyReadFile(file_name);

		while (getline(MyReadFile, output))
		{
			if (output.length() != 0 && output.front() != ';')
			{
				parse_line(output);
			}
		}
	}
	else
	{
		return;
	}
}

void CommandProcessor::parse_line(string line)
{
	cout << line << endl;
	std::stringstream ss(line);
	string word;
	while (!ss.eof())
	{
		getline(ss, word, '\t');
		cout << word << endl;
	}
	cout << "=========" << endl;
}

void CommandProcessor::test()
{
	cout << file_name << endl;
}