#include <string>
#include <iostream> 
#include <fstream>
#include <cstdlib>
#include <iterator>
#include <vector>
#include <map>
#include "../headers/BufferPool.h"
#include "../headers/GISRecord.h"

using namespace std;

//constructors
BufferPool::BufferPool()
{
    this->dbPath = "";
    // this->cache = {}; //empty cache
    this->recordCache = {};
    //this->cacheMap; //<int,GISRecord *>
}

BufferPool::BufferPool(string dbFilePath)
{
    this->dbPath = dbFilePath;
    // this->cache = {}; //empty cache
    this->recordCache = {};
    //this->cacheMap; //<int,GISRecord *>
}



GISRecord BufferPool::processTxt(string rawText, int off)
{
    vector<string> parameters = {};
    string current = ""; //current parameter value
    for (char c : rawText) //for each character in rawText
    {
        if( c != '|') // if it is not a pipe character
        {
            current += c; //add c to current parameter
        }
        else if (c == '|') //if we encounter a pipe
        {
            parameters.push_back(current); //append whatever we have read to parameters
            current = ""; //reset the string
        }
    }
    GISRecord new_record = GISRecord{off,parameters[0],parameters[1],parameters[2],parameters[3],
    parameters[4],parameters[5],parameters[6],parameters[7],
    parameters[8],parameters[9],parameters[10],parameters[11],
    parameters[12],parameters[13],parameters[14],parameters[15],
    parameters[16],parameters[17],parameters[18],parameters[19]};

    return new_record;

}

void BufferPool::fillCache_db()
{
    //open db file
    fstream dbFile;
    dbFile.open(this->dbPath,ios::in); //input mode

    vector<GISRecord> record_cache = {}; //helper vector which we convert to double link list later
    
    //go through each line until Line Feed (ASCII 10) is encountered
    if(dbFile.is_open())
    {
        dbFile.ignore(265); //the titles in the db columns altogether make 264 char. "\n" after makes 265
                            //in Windows, Carriage Return + Line Feed makes End-Of-Line, so might act weird
        string line;
        int length = 265;
        int mapIndex = 0; 
        //GISRecord new_record = GISRecord();
        while(getline(dbFile,line))
        {
            //process the string read to a GISRecord.
            GISRecord new_record = processTxt(line,length); //first record, has offset of 265
            length += line.length(); //offset keeps being added. we count \n in offset
            //insert to cache at beginning
            this->recordCache.push_front(new_record);
            //if cache already 15, remove the last record. Last record is least recently used
            if(this->recordCache.size() > 15)
            {
                // //go from index 1, move every record, negative one index 
                // for(int index = 1; index < 15; ++index) //an O(15) operation
                // {
                //     record_cache[(index-1)] = record_cache[index];
                // }
                // //add the new (processed) record to last index
                // record_cache[14] = new_record;
                // record_cache.resize(15);
                this->recordCache.pop_back();

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
    // if(this.recordCache.size() == 0)
    // {
    //     cout << "DB file perhaps empty, or has no records at the moment" << endl;
    // }
    // else if(this.recordCache.size() == 1) //if just one Record
    // {
    //     cacheNode new_node_temp;
    //     new_node_temp.prev_node = NULL;
    //     new_node_temp.next_node = NULL;
    //     new_node_temp.record = &record_cache[0];

    //     cache.push_back(new_node_temp);
    // }
    // else
    // {
    //     for(int x = 0; x < record_cache.size(); ++x)
    //     {
    //         cacheNode new_node_temp;
    //         new_node_temp.prev_node = NULL;
    //         new_node_temp.next_node = NULL;
    //         new_node_temp.record = &record_cache[x];

    //         cache.push_back(new_node_temp); //most recent is last index 
    //     } //GISRecord objects have been added

    //     //our cache of Nodes has been pre filled with the most recent being the last
    //     for(int i = 0; i < cache.size(); ++i)
    //     {
    //         if(i == (cache.size()-1)) //if index is 14 or last GISRecord (most recently processed)
    //         {   
    //             //last index in record_cache is most recent
    //             //first element of cache is most recent = outcome i want
               
    //             cache[i].prev_node = NULL;
    //             cache[i].next_node = &cache[(i-1)]; 
    //             //new_node.record = record_cache[i]; //current record
    //         }
    //         else if(i == 0) //if least recently processed record. (make the index here more generic not hard coded)
    //         {
    //             //first index in record_cache is least recent
    //             //last element of cache is least recent
    //             //previous node is more recent in terms of LRU 
    //             //in terms of our record_cache vector, higher index is more recent
    //             cache[i].prev_node = &cache[(i+1)]; 
    //             cache[i].next_node = NULL;
    //             //new_node.record = record_cache[i]; //current record
    //         }
    //         else //i is not 0 or record_cache.size()
    //              //i+1 is more recent, i-1 is less in terms of record_cache
    //              //since LRU -> means, next node is less recent than previous (0 more recent than 14)
    //         {
    //             cache[i].prev_node = &cache[(i+1)];
    //             cache[i].next_node = &cache[(i-1)];
    //             //new_node.record = record_cache[i];
    //         }
    //     } //pointers have been adjusted in our double link list
    // }

}


//if time, implement operators for GISRecord
GISRecord* BufferPool::getRecord(GISRecord* rec)
{
    int searchRes = lookFor(rec);
     
    if (searchRes == -1)
    {
        return nullptr;
    }
    else
    {
        list<GISRecord>::iterator cache_it = this->recordCache.begin(); 
        advance(cache_it,(searchRes)); //advance iterator. 
        GISRecord new_rec = *cache_it;
        this->recordCache.erase(cache_it); //erase the record found AT iterator position
        this->recordCache.push_front(new_rec);

        cache_it = this->recordCache.begin(); //readjust the iterator
        return &(*cache_it); //return pointer to the first record in cache
    }

}

//helper function. private access
int BufferPool::lookFor(GISRecord* target)
{
    int result = -1;
    int index = 0;
    for(GISRecord r : this->recordCache)
    {   
        //counting feature id and state alphabet for now
        if(target->getFeat_name() == r.getFeat_name() 
            &&  target->getState_alpha() == r.getState_alpha())
        {
            result = index;
        }
        index ++;
    }
    return result;
}

/*remove a record from cache*/
    //when not in cache, are we removing from DB?
void BufferPool::deleteRecord(GISRecord* rec)
{
    int searchRes = lookFor(rec);
     
    if (searchRes == -1)
    {
        cout << "record not found in cache " << endl;
    }
    else
    {
        list<GISRecord>::iterator cache_it = this->recordCache.begin(); 
        advance(cache_it,(searchRes)); //advance iterator.
        this->recordCache.erase(cache_it); //erase the record found AT iterator position
    }
}

/*insert this record into the cache*/
    //remove Least recently used if cache full
void BufferPool::insertRecord(GISRecord* rec)
{
    
    int searchRes = lookFor(rec);
     
    if (searchRes == -1) //if not exist
    {
        //push to front
        this->recordCache.push_front(*rec);
        
        //readjust if size is > 15 after push
        while(this->recordCache.size() > 15)
        {   
            //remove the last one
            this->recordCache.pop_back();
        }
    }
    else //if record exist
    {  
        //copy it
        list<GISRecord>::iterator cache_it = this->recordCache.begin(); 
        advance(cache_it,(searchRes)); //advance iterator.
        GISRecord new_rec = *cache_it;

        //remove it at current pos
        this->recordCache.erase(cache_it);
        //push it to front
        this->recordCache.push_front(new_rec);

        //readjust if size > 15
        while(this->recordCache.size() > 15)
        {
            //remove the last one
            this->recordCache.pop_back();
        }
    }
}

//add more details is needed after
void BufferPool::str()
{   
    //vector<GISRecord> helper_vec = {};
    int i = 0;
    cout << "Feat_Name\t|\tState Alphabet" << endl;
    for(GISRecord rec : this->recordCache)
    {
        cout << i+1 << ". " << rec.getFeat_name() << "\t: \t" << rec.getState_alpha() << endl;
        i++;
    }
}



/*main function to test BufferPool functionality*/
int main (void)
{
    string dbPath = "../files/VA_Monterey.txt";
    BufferPool *pool = new BufferPool(dbPath);

    pool->fillCache_db();
    int x = 0;
    // for(BufferPool::cacheNode n : pool->cache)
    // {
    //     cout << x <<". "<<n.record->getFeat_id() << endl;
    //     cout <<"next node:" << "\t" << n.next_node << endl;
    //     cout <<"prev node:" << "\t" << n.prev_node << endl;
    //     x++;
    // }
    pool->str();


}



