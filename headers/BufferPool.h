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
*/
#ifndef BUFFERPOOL_H
#define BUFFERPOOL_H

#include <string>
#include "../headers/GISRecord.h"

using namespace std;
class BufferPool
{
    public:
    BufferPool(); //create an empty cache 
    explicit BufferPool(string dbFilePath);

    fillCache(); //initiate pool cache from db file (the last 15 records, or however available if under 15)

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
        GISRecord& record; //current record. A reference
    };

    string dbPath; //database file path
    vector<cacheNode> cache; //doubly linked list that BufferPool maintains
    
    /*Operations of a doubly linked list*/
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