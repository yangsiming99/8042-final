#include "../headers/NameIndex.h"
#include "../headers/GISRecord.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <ostream>

using namespace std;

int arrsize = 1024;
string* keys = new string[arrsize];
GISRecord* Name_Index = new GISRecord[arrsize];
int counter = 0;
int max_probe = 0;
int character_count = 0;

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
    string poop = data_container[1];
    int index = hashFunction(data_container[1]);
    int attempt = 0;
    while (keys[index] != "")
    {
        attempt++;
        if (attempt > max_probe)
        {
            max_probe = attempt;
        }
        index = (index + attempt * attempt) % arrsize;
    }
    keys[index] = data_container[1];
    GISRecord entry(offset, data_container[0], data_container[1], data_container[2], data_container[3], data_container[4],
        data_container[5], data_container[6], data_container[7], data_container[8], data_container[9],
        data_container[10], data_container[11], data_container[12], data_container[13], data_container[14],
        data_container[15], data_container[16], data_container[17], data_container[18], data_container[19]
    );
    Name_Index[index] = entry;
    character_count += data_container[1].length();
    counter++;


    double fill_percent = static_cast<double>(counter) / arrsize;
    if(fill_percent >= 0.75)
    {
        resize_hash();
    }
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

string NameIndex::what_is(string loc, string abr, BufferPool* bp)
{
    int index = hashFunction(loc);
    int attempt = 0;
    string location;
    GISRecord record;
    while (attempt <= max_probe)
    {
        if (keys[index] == loc && Name_Index[index].getState_alpha() == abr)
        {
            location = keys[index];
            record = Name_Index[index];
            bp->insertRecord(&record);
            break;
        }
        else {
            attempt++;
            index = (index + attempt * attempt) % arrsize;
        }
    }


    if (location != loc) {
        return "No records match [" + loc + "] and [" + abr + "]";
    }

    string lati = record.getLat_DMS_prim();
    string longi = record.getLong_DMS_prim();

    std::stringstream latiStream;
    latiStream << lati.substr(0, 2) << "d " << lati.substr(2, 2) << "m " << lati.substr(4, 2) << "s " << lati.substr(6);
    std::string latiFormatted = latiStream.str();

    std::stringstream longiStream;
    longiStream << longi.substr(0, 3) << "d " << longi.substr(3, 2) << "m " << longi.substr(5, 2) << "s " << longi.substr(7);
    std::string longiFormatted = longiStream.str();

    std::stringstream resultStream;
    resultStream << index << ":\t" << record.getCountry_name() << " (" << latiFormatted << ", " << longiFormatted << ")";
    std::string result = resultStream.str();

    return result;
}

vector<int> NameIndex::get_stats()
{
    vector<int> stats;
    stats.push_back(counter);
    stats.push_back(arrsize);
    stats.push_back(max_probe);
    stats.push_back(character_count / counter);

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