#include <string>
#include <fstream>
#include <cstdlib>
#include "../headers/BufferPool.h"
#include "../headers/GISRecord.h"

using namespace std;

explicit BufferPool::BufferPool(string dbFilePath)
{
    this.dbPath = dbFilePath;
    this.cache = {}; //empty cache
}

GISRecord* BufferPool::processTxt(string rawText, int off)
{
    vector<string> parameters;
    for (char c : rawText) //for each character in rawText
    {
        string current = ""; //current parameter value
        if( c != '|') // if it is not a pipe character
        {
            current += c; //add c to current parameter
        }
        else if (c == "|") //if we encounter a pipe
        {
            parameters.append(current); //append whatever we have read to parameters
        }
    }
    GISRecord *new_record(off,parameters[0],parameters[1],parameters[2],parameters[3],
    parameters[4],parameters[5],parameters[6],parameters[7],
    parameters[8],parameters[9],parameters[10],parameters[11],
    parameters[12],parameters[13],parameters[14],parameters[15],
    parameters[16],parameters[17],parameters[18],parameters[19]);

    return new_record;

}

BufferPool::fillCache()
{
    //open db file
    fstream dbFile;
    dbFile.open(this.dbPath,ios::in); //input mode

    //go through each line until Line Feed (ASCII 10) is encountered
    if(dbFile.isopen())
    {
        string line;
        int length = 0;
        while(getline(dbFile,line,'\n'))
        {
            int length += line.length(); //offset keeps being added
            //process the string read to a GISRecord.
            GISRecord *new_record = processTxt(line,length);
            //insert to cache at the end
                //if cache already 15, remove the first record, insert new_record to 15th position
        }
    }
    else
    {
        cout << "error opening DB File (BufferPoool::fillCache() method)" << endl;
    }
    //process the string read to a GISRecord. insert to cache 
        //if cache already 15, remove the first record, insert this to 15th position
    //keep going till EOF
}

/*main function to test BufferPool functionality*/
int main (void)
{
    
}


