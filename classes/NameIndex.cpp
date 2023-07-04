#include "../headers/NameIndex.h"
#include "../headers/GisRecord.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <ostream>
#include <format>

using namespace std;

int arrsize = 1024;
string* keys = new string[arrsize];
GISRecord* Name_Index = new GISRecord[arrsize];
int counter = 0;

NameIndex::NameIndex()
{
}

int NameIndex::hashFunction(string key)
{
    int hash = 0;
    for (char c : key)
    {
        hash += c;
    }
    return hash % arrsize;
}

void NameIndex::insert_location(vector<string> data_container, int offset)
{
    int index = hashFunction(data_container[1]);
    int att = 0;
    while (keys[index] != "")
    {
        att++;
        index = (index + att * att) % arrsize;
    }
    keys[index] = data_container[1];
    GISRecord entry(offset, data_container[0], data_container[1], data_container[2], data_container[3], data_container[4],
        data_container[5], data_container[6], data_container[7], data_container[8], data_container[9],
        data_container[10], data_container[11], data_container[12], data_container[13], data_container[14],
        data_container[15], data_container[16], data_container[17], data_container[18], data_container[19]
    );
    Name_Index[index] = entry;
    
    int filled = 0;
    for (int i = 0; i < arrsize; i++)
    {
        if (!keys[i].empty())
        {
            filled ++;
        }
    }

    double fill_percent = static_cast<double>(filled) / arrsize;
    if(fill_percent >= 0.75)
    {
        resize_hash();
    }
    counter++;
}

GISRecord NameIndex::get_location(string loc) {
    int index = hashFunction(loc);
    while (keys[index] != "")
    {
        string test = keys[index];
        if (keys[index] == loc)
        {
            return Name_Index[index];
        }
    }
    return GISRecord();
}

void NameIndex::resize_hash()
{
    int narrsize = arrsize * 2;
    string* nkeys = new string[narrsize];
    GISRecord* nName_Index = new GISRecord[narrsize];

    for (int i = 0; i < arrsize; i++)
    {
        if (!keys[i].empty()) {
            int nIndex = hashFunction(keys[i]) % narrsize;
            int att = 0;
            while (!nkeys[nIndex].empty())
            {
                att++;
                nIndex = (nIndex + att * att) % narrsize;
            }
            nkeys[nIndex] = keys[i];
            nName_Index[nIndex] = Name_Index[i];
        }
    }

    delete[] keys;
    delete[] Name_Index;
    keys = nkeys;
    Name_Index = nName_Index;
    arrsize = narrsize;
}

void NameIndex::display()
{
    int count = 0;
    for (int i = 0; i < arrsize; i++)
    {
        if (!keys[i].empty())
        {
            count++;
            cout << "Index: " << i << " Key: " << keys[i] << endl;
        }
    }
}

vector<int> NameIndex::get_stats()
{
    vector<int> stats;
    stats.push_back(counter);
    stats.push_back(arrsize);

    return stats;
}

string* NameIndex::get_keys()
{
    return keys;
}

GISRecord* NameIndex::get_list()
{
    return Name_Index;
}