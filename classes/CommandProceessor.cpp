#include "../headers/CommandProcessor.h"
#include "../headers/NameIndex.h"
#include "../headers/CoordinateIndex.h"
#include "../headers/GISRecord.h"

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

int CommandProcessor::removeDecimal(double d)
{
	int multiplier = 1;
    double integerPart = static_cast<int>(d);
    double decimalPart = d - integerPart;

    while (decimalPart > 0.0001) {
        multiplier *= 10;
        d *= 10;
        integerPart = static_cast<int>(d);
        decimalPart = d - integerPart;
    }

    int result = static_cast<int>(d);
	return result;
}

void CommandProcessor:: cmd_import(vector<string> cmd, vector<double> bounds, NameIndex ni, CoordinateIndex ci) {
	cout << "inside cmd_import" << endl;
	ifstream file;
	vector<int> int_bounds = {};
	for(double d : bounds)
	{
		cout << "inside first for loop" << endl;
		int_bounds.push_back(removeDecimal(d)); //west east Lats  nort south longs
	}
	cout << "left first for loop" << endl;
	ci.westLimit = int_bounds[0];
	ci.eastLimit = int_bounds[1];
	ci.northLimit = int_bounds[2];
	ci.southLimit = int_bounds[3];
	cout << "coords limit set" << endl;
	vector<string> accepted;
	int counter = 0;
	file.open(cmd[1]);
	if (file)
	{
		cout << "Reading file" << endl;
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
					GISRecord rec = ci.processVector(data_container, counter);
					ci.add(&rec);
				}
			}
			counter++;
		}
		cout << "ended reading each line" << endl;
	}

	cout << "opening db file " << endl;
	db_file.open(db_fileName, ios_base::app);
	cout << "opened db file " << endl;
	for (string line : accepted)
	{
		db_file << line + "\n";
		cout << "for loop db file " << endl;
	}
	db_file.close();
	cout << "closed db file " << endl;
}

void CommandProcessor::create_db_file()
{
	db_file.open(db_fileName, ios_base::trunc);
	db_file << "";
	db_file.close();
}