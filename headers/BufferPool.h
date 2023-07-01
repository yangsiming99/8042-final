/*Front end for our GIS Database.
    Buffer upto 15 records
    use Least Recently Used (LRU) replacement

    not implementing anything at the moment for world and import command
    import command bypasses BufferPool and instantiate records into our DB file directly    

    commands to respond to: 
    debug pool - str() function
    quit
    what_is_at <geographic co-ordinates>
    what_is <feature-name> <state-abbreviation>
    what_is_in <geographic co-ordinates> <half-height> <half-width> [optional: -long OR -filter]

    using std::list as it is a pre build double link list - covers most functionality we need from container
    
    At current state, requires search function to search for a specific record. 
    to improve lookup map used to index the cache.OPTIONAL FOR NOW
        either have to finalize GISRecord operators which we have to do anyway
        Figure out how to index and maintain at 15 records. Also need to remember LRU Replacement
    
    *****O(N) is not bad price to pay, to avoid bugs and not use <map> altogether
*/
#ifndef BUFFERPOOL_H
#define BUFFERPOOL_H

#define CACHE_LIMIT 15

#include <string>
#include <iostream>  //good for machine io (stdio, stderr, stdout, stdlog)
#include <fstream> //good for files
#include <vector>
#include <iterator>
#include <map> //remove at the end of project if not implemented
#include <list> //already is a double link list
#include "../headers/GISRecord.h"

using namespace std;
class BufferPool
{
    public:

    list<GISRecord> recordCache; // the LRU Replacement cache we will use
    string dbPath;
    //map<int,GISRecord*> cacheMap; // map used to index the cache, to reduce retrieval.OPTIONAL FOR NOW


    /*
    Node in Buffer Pool cache. 
    Contains a GISRecord, 
    2 pointers - one points to next record
                 one points to previous record
    */
    // struct cacheNode
    // {
    //     cacheNode *prev_node;
    //     cacheNode *next_node;
    //     GISRecord *record; //current record. (pointer to GISRecord)
    // };

    // vector<cacheNode> cache; //doubly linked list that BufferPool maintains

    
    BufferPool(); //create an empty cache 
    explicit BufferPool(string dbFilePath);

    //initiate pool cache from db file (the last 15 records, or however available if under 15)
    //At the moment, this is the function that is interacting directly with the DB file
    //if we can have a function that interacts with something more indexed, we can reduce time cost
    void fillCache_db(); 

    GISRecord processTxt(string rawText, int off); //return by value

    /*Some Buffer Pool functionality*/

    /*At the moment, operations deal with tha cache in BufferPool only*/

    /*atm, seems like Name Index and Co-ords Index will do more work on the DB*/
    /*get a record from cache*/ 
        //when not in cache, we have to consult the DB
    GISRecord* getRecord(GISRecord* rec);

    /*remove a record from cache*/
        //when not in cache, are we removing from DB?
    void deleteRecord(GISRecord* rec); 

    /*insert this record into the cache*/
        //remove Least recently used if cache full
    void insertRecord(GISRecord* rec);
    
    //implement a str() that will be used in debug command
    void str();

    /*getters and setters*/
    string getDbPath();
    void setDbPath(string dbFilePath);
    
    private:

    //-1 is not found. 0 or more is index of found record
    // -1 is not found
    // any other number, zero or positive, should be index of record in cache
    int lookFor(GISRecord* target);

};
#endif

/*Built in from std::list
    push front
    pop front

    push back
    pop back

    insert BEFORE index

    remove element AT index

    resize the double link list

    --------------------------------------
    Have to implement:
    search function to search for a specific record. 
*/