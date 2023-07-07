/* Index of offset and primary co-ords of a record
    
    ---------------------
    Background theory:
    ---------------------
    we are implementing a PR Quadtree. Defaults to a tree with 4 leaves, but we can change the value of K
    Technically, a PR K-Tree
    Where, K is the number of buckets that we divide geographic co-ordinate space by.
    We see a co-ordinate, the buckets I am dividing starting from NW, going to NE. then from SW, going to SE
    So, if we have a K of 8, we will have 4 regions up top (above equator), 4 bottom (below equator). 
    Explicating that:
    2 regions in NW, 2 regions in NE. 2 in SW, 2 in SE. 8 total

    we will default K to 4
    We start with a tree with 4 regions in geography that are denoted as leaves.
    These leaves cover a certain geographic area. Once, the leaf is occupied and we want to 
    place another co-ordiante in this region that the leaf occupies.

    We divide that particular region again in K sub-regions. This is denoted as a subtree.
    This subtree has a root also. 

    A single co-ordinate can hold many GIS Records. 

    We start with big chunks of area that is occupied by just one leaf. (4 chunks is all of the world at start)
    Imagine one leaf occupying all of NW quadrant in ur simulation. so, if you wish to place another
    co-ordinate anywhere in NW quadrant, we are left with dividing that quadrant again. 
    
    And thus, any position in a <vector>, is a range of latitude and logitude 
    As far as I believe, A vector will have 4 elements. Where each of those elements
    can be vectors of 4 elements also huehuehue. Everything containing GIS Records

    ---------------------
    Commands to respond to:
    ---------------------
    NOTE: <geographic coordinate> equals <geog. coords lat> <geog. coords long>
    
    world <westLong> <eastLong> <southLat> <northLat>
    import <GIS Record file>
    debug <quad>
    quit
    what_is_at <geographic coordinate>
    what_is <feature_name> <geographic coordinate>
    what_is_in <geographic coordinate> <half-height> <half-width>
        about: this geog. coord is the center. from center go half height N and S
                                                              half width E and W
        half-height and half-width specified as seconds
        OPTIONAL -long switch which logs every important NON-EMPTY field
        OPTIONAL -filter pop 
                 -filter water
                 -filter structure

 */

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <iterator>
#include <algorithM.

#include "../headers/GISRecord.h"
#include "../headers/Logger.h"

#define UNSET 999999
#define UNSET2 999999

using namespace std;

class CoordinateIndex
{
    public:
    
    vector<GISRecord> records; //raw set of records. Ideally we only fill this up once during "Indexing"
    
    int buckets; //number of divisions a spatial regions goes through

    // spatial bounds. Fluid depending on commands/inputs
    int westLimit;
    int eastLimit;
    int northLimit;
    int southLimit;

    //helper structs.
    //dms_coords: initiate using GISRecord co_ordinates 
    //helps me to avoid making operators with std::pair. I'm not good enough to think of smth elses 
    struct dms_cords 
    {
        int latCoords;
        int longCoords;
    };
    const dms_coords unsetNode{UNSET,UNSET2};
    struct treeNode
    {
        int westBound;
        int eastBound;
        int northBound;
        int southBound;
        dms_coords range; //lat range covered by this node at current level
        dms_coords coordinates; //the co-ordinate placed from database
        vector<int> offsets; //number of records in current coordinate
        vector<treeNode*> children;
    };
    
    //we triple layered the nodes, so this way don't have to maintain a vector
    //of nodes in the node itself
    vector<treeNode> kTree; //the tree. vector, of treeNode vectors 
    
    string dbPath;

    //initialize empty stuff
    CoordinateIndex();
    //db not set yet when constructed
    CoordinateIndex(int wLimit, int eLimit, int nLimit, int sLimit, int k);

    //functions

    int string2DMS(string coords);
    int determineRegion(dms_coords parentRange, GISRecord* current_record, 
        int westBound, int eastBound, int northBound, int southBound);

    int determineRegion_split(dms_coords parentRange, int old_recordLat, int old_recordLong, 
        int westBound, int eastBound, int northBound, int southBound);

    GISRecord processTxt(string rawText, int off); //return by value
   
    //inner helper function. spawns k child nodes and calls add upon the subnode 
    void add_to_node(treeNode* add2This, dms_coords parentRange, GISRecord* addThis, 
        int westBound, int eastBound, int northBound, int southBound);

   //spawn a vector of 4 nodes, place the offset and co-ords into their regions
    void splitNode(GISRecord* this_record);

    //add to raw vector of records, && add() to kTree and process any change in the tree structure
    void add(GISRecord* record);


    //read whole file
    //turn to records
    //uses add() function, so the tree is also updated
    void index_db();

    void remove(GISRecord *record);

    //logic behind spatial regions
    //westLimit to eastLimit is our longitude range
    //northLimit and southLimit is our latitude range
    //whatever is K, we divide that by 2. Answer of that is number of regions north and south
        //let's take that, divide by 2 and now we have the amount in each leaf (region for now) 
    void adjust(int westNum, int eastNum, int northNum, int southNum);

    void changeK(int newK); //changes the divisions of spatial regions

    string getDbPath();
    void setDbPath(string filePath);

    private:

    //possible helper functions
    //convert decimals to dms 


}

