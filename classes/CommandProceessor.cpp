#include "../headers/CommandProcessor.h"
#include "../headers/NameIndex.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <ostream>

using namespace std;

ofstream db_file;
string db_fileName;

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

void CommandProcessor:: cmd_import(vector<string> cmd, vector<double> bounds, NameIndex ni) {
	ifstream file;
	vector<string> accepted;
	int counter = 0;
	file.open(cmd[1]);
	if (file)
	{
		string output;
		ifstream myReadFile(cmd[1]);
		while (getline(myReadFile, output))
		{
			if (counter > 0)
			{
				//cout << output << endl;
				bool acc = true;
				stringstream ss(output);
				string word;
				vector<string> data_container;
				while (!ss.eof())
				{
					getline(ss, word, '|');

					data_container.push_back(word);
				}
				double lati = stod(data_container[9]);
				double longi = stod(data_container[10]);
				int test = 0;
				if (lati > bounds[2] || lati < bounds[3])
				{
					acc = false;
				}
				if (longi < bounds[0] || longi > bounds[1])
				{
					acc = false;
				}
				if (acc)
				{
					//ni.add_location(counter, data_container);
					ni.insert_location(data_container, counter);
					//ni.display();
					accepted.push_back(output);
				}
			}
			counter++;
		}
	}
	db_file.open(db_fileName, ios_base::app);
	for (string line : accepted)
	{
		db_file << line + "\n";
	}
	db_file.close();
}

void CommandProcessor::create_db_file()
{
	db_file.open(db_fileName, ios_base::trunc);
	db_file << "";
	db_file.close();
}