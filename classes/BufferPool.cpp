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

GISRecord BufferPool::processTxt(string rawText, int off)
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

void BufferPool::fillCache_db()
{
    //open db file
    fstream dbFile;
    dbFile.open(this.dbPath,ios::in); //input mode

    vector<GISRecord> record_cache; //helper vector which we convert to double link list later
    
    //go through each line until Line Feed (ASCII 10) is encountered
    if(dbFile.isopen())
    {
        dbFile.ignore(265); //the titles in the db columns altogether make 264 char. "\n" after makes 265
                            //in Windows, Carriage Return + Line Feed makes End-Of-Line, so might act weird
        string line;
        int length = 0;
        GISRecord new_record;
        while(getline(dbFile,line))
        {
            int length += line.length(); //offset keeps being added
            //process the string read to a GISRecord.
            new_record = processTxt(line,length);
            //insert to cache at the end
            record_cache.append(new_record);
            //if cache already 15, remove the first record, insert new_record to 15th position
            if(record_cache.size() == 15)
            {
                //go from index 1, move every record, negative one index 
                for(int index = 1; index < 15; ++index) //an O(15) operation
                {
                    record_cache[(index-1)] = record_cache[index];
                }
                //add the new (processed) record to last index
                record_cache[14] = new_record;
            }
        } //EOF reached
    }
    else
    {
        cout << "error opening DB File (BufferPoool::fillCache_db() method)" << endl;
    }
    dbFile.close(); //close the file stream
    
    //whatever vector of GISRecords we have now,
    //the last index is most recently processed

    //special cases for our double link list: empty record_cache
    //                                        just one GISRecord 
    if(record_cache.size() == 0)
    {
        cout << "DB file perhaps empty, or has no records at the moment" << endl;
    }
    else if(record_cache.size() == 1) //if just one Record
    {
        cacheNode new_node_temp;
        new_node_temp.prev_node = NULL;
        new_node_temp.next_node = NULL;
        new_node_temp.record = record_cache[0];

        cache.append(new_node_temp);
    }
    else
    {
        for(int x = 0; x < record_cache.size(); ++x)
        {
            cacheNode new_node_temp;
            new_node_temp.prev_node = NULL;
            new_node_temp.next_node = NULL;
            new_node_temp.record = record_cache[x];

            cache.append(new_node_temp); //most recent is last index 
        } //GISRecord objects have been added

        //our cache of Nodes has been pre filled with the most recent being the last
        for(int i = 0; i < ache.size(); ++i)
        {
            if(i == (cache.size()-1)) //if index is 14 or last GISRecord (most recently processed)
            {   
                //last index in record_cache is most recent
                //first element of cache is most recent = outcome i want
               
                cache[i].prev_node = NULL;
                cache[i].next_node = &cache[(i-1)]; 
                //new_node.record = record_cache[i]; //current record
            }
            else if(i == 0) //if least recently processed record. (make the index here more generic not hard coded)
            {
                //first index in record_cache is least recent
                //last element of cache is least recent
                //previous node is more recent in terms of LRU 
                //in terms of our record_cache vector, higher index is more recent
                cache[i].prev_node = &cache[(i+1)]; 
                cache[i].next_node = NULL;
                //new_node.record = record_cache[i]; //current record
            }
            else //i is not 0 or record_cache.size()
                 //i+1 is more recent, i-1 is less in terms of record_cache
                 //since LRU -> means, next node is less recent than previous (0 more recent than 14)
            {
                cache[i].prev_node = &cache[(i+1)];
                cache[i].next_node = &cache[(i-1)];
                //new_node.record = record_cache[i];
            }
        } //pointers have been adjusted in our double link list
    }
    

}

/*main function to test BufferPool functionality*/
int main (void)
{
    
}


