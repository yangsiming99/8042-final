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
	//cout << line << endl;
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
