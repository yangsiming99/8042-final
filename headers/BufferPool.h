/*Front end for our GIS Database.
    Buffer upto 15 records
    use Least Recently Used (LRU) replacement

    not implementing anything at the moment for world and import command
    choosing import command to bypass BufferPool and instantiate records into our DB file directly    

    commands to respond to: 
    debug pool
    quit
    what_is_at <geographic co-ordinates>
    what_is <feature-name> <state-abbreviation>
    what_is_in <geographic co-ordinates> <half-height> <half-width> [optional: -long OR -filter]

    if time: Add Hash Table to this data type, change retrieval to from O(15) to O(1)
                (maybe a simple map since it's just 15 items)
             Try to make Buffer Pool generic so it can operate on any of our GIS dB files
*/
#ifndef BUFFERPOOL_H
#define BUFFERPOOL_H

#define CACHE_LIMIT 15

#include <string>
#include <fstream>
#include "../headers/GISRecord.h"

using namespace std;
class BufferPool
{
    public:
    BufferPool(); //create an empty cache 
    explicit BufferPool(string dbFilePath);

    //initiate pool cache from db file (the last 15 records, or however available if under 15)
    //At the moment, this is the function that is interacting directly with the DB file
    //if we can have a function that interacts with something more indexed, we can reduce time cost
    void fillCache_db(); 

    GISRecord processTxt(string rawText, int off); //return by value

    /*Some Buffer Pool functionality*/
    /*atm, seems like Name Index and Co-ords Index will do more work on the DB*/
    /*get a record from cache*/ 
        //when not in cache, we have to consult the DB
    GISRecord getRecord();
    /*remove a record from cache*/
        //when not in cache, are we removing from DB?
    void deleteRecord(); 
    /*insert this record into the cache*/
        //remove Least recently used if cache full
    void insertRecord();
    
    /*getters and setters*/
    string getDbPath();
    void setDbPath(string dbFilePath);
    
    private:
    /*
    Node in Buffer Pool cache. 
    Contains a GISRecord, 
    2 pointers - one points to next record
                 one points to previous record
    */
    struct cacheNode
    {
        cacheNode *prev_node;
        cacheNode *next_node;
        GISRecord *record; //current record. (pointer to GISRecord)
    };


    // cacheNode dummyNode = 
    // {
    //     prev_node = NULL;
    //     next_node = NULL;

    // }; //dummy node which indicates end of the list
    vector<cacheNode> cache; //doubly linked list that BufferPool maintains
    string dbPath; //database file path
    
    /*Operations of a doubly linked list*/
    
    cacheNode getNode();

    //insertion at beginning
    void insert_beginning();
    //insertion at end
    void insert_end();
    //inertion after specified node
    void insert_after();

    //deletion at beginning
    void delete_beginning();
    //deletion at end
    void delete_end();
    //deletion of node that has given GISRecord
    void delete_this();

    //Searching - Look for a GISRecord in the cache and return the result
    int search_record(GISRecord *rec);

    //Traversing - Vising each node of the cache at least once to perform an operation.

};
#endif