#include "../headers/NameIndex.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <ostream>
#include <format>

using namespace std;

int arrsize = 5;
string* Name_Index = new string[arrsize];
int pos = 0;

NameIndex::NameIndex()
{
}

void NameIndex::up_size()
{
    arrsize = arrsize * 2;
    string* nName_index = new string[arrsize];
    for (int i = 0; i < pos; i++) {
        nName_index[i] = Name_Index[i];
    }
    delete[] Name_Index;
    Name_Index = nName_index;
}

void NameIndex::add_location(string feature_name, string state_abbr)
{
    double filled = static_cast<double>(pos) / arrsize;
    if (filled > 0.7) {
        up_size();
    }
    Name_Index[pos] = format("{}|{}", feature_name, state_abbr);
    pos++;
}

void NameIndex::display()
{
    for (int i = 0; i < pos; i++) 
    {
        stringstream ss(Name_Index[i]);
        string part;
        while (getline(ss, part, '|'))
        {
            cout << part << " ";
        }
        cout << endl;
    }
}