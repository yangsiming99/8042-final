#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <unordered_map>

#include "../headers/CoordinateIndex.h"
#include "../headers/GISRecord.h"
#include "../headers/Logger.h"

#define LAT_OUT_OF_BOUNDS 200
#define LONG_OUT_OF_BOUNDS 200

using namespace std;

CoordinateIndex::CoordinateIndex()
{
}
CoordinateIndex::CoordinateIndex(string wLimit, string eLimit, string nLimit, string sLimit, string k)
{
    this->westLimit = string2DMS(wLimit);
    this->eastLimit = string2DMS(eLimit);
    this->northLimit = string2DMS(nLimit);
    this->southLimit = string2DMS(sLimit);
    this->buckets = stoi(k);
    
    this->dbPath = "";
    //vector<treeNode> sample = {};
    
    int k_int = stoi(k);
    int total_long = (string2DMS(wLimit) * (-1)) + string2DMS(eLimit); //raw distance
    int total_lat = string2DMS(nLimit) + (string2DMS(sLimit) * (-1)); //raw distance
    int lat_parition = total_lat / k_int; //raw distance divided by number of regions (buckets)
    int long_partition = total_long / k_int;

    for(int i = 0; i < k_int; ++i)
    {   
        if(i < k_int/2)
        {
            treeNode node1;
            node1.range.latCoords = lat_parition;
            node1.range.longCoords = long_partition; //latCoords, longCoords
            node1.northBound = string2DMS(nLimit);
            node1.southBound = string2DMS(sLimit) + (total_lat/2);
            node1.eastBound = string2DMS(wLimit) + ((i+1)*long_partition);
            node1.westBound = string2DMS(wLimit) + (i*long_partition);
            node1.coordinates.latCoords = UNSET;
            node1.coordinates.longCoords = UNSET2;
            node1.offsets = {};
            node1.children = {};
            //sample.push_back(node1); //vector of tree nodes
            this->kTree.push_back(node1); //add an empty vector of nodes k times
        }
        else // i>= k/2
        {
            treeNode node1;
            node1.range.latCoords = lat_parition;
            node1.range.longCoords = long_partition; //latCoords, longCoords
            node1.northBound = string2DMS(nLimit) - (total_lat/2);
            node1.southBound = string2DMS(sLimit);
            node1.eastBound = string2DMS(wLimit) + ((i+1)*long_partition);
            node1.westBound = string2DMS(wLimit) + (i*long_partition);
            // node1.coordinates = this->unsetNode;
            node1.coordinates.latCoords = UNSET;
            node1.coordinates.longCoords = UNSET2;
            node1.offsets = {};
            node1.children= {};
            //sample.push_back(node1); //vector of tree nodes
            this->kTree.push_back(node1); //add an empty vector of nodes k times
        }
    }
}

string CoordinateIndex::getDbPath()
{
    return this->dbPath;
}
void CoordinateIndex::setDbPath(string filePath)
{
    this->dbPath = filePath;
}

void CoordinateIndex::changeK(int k)
{
    this->buckets = k;
}

GISRecord CoordinateIndex::processTxt(string rawText, int off) //return by value
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

GISRecord CoordinateIndex::processVector(vector<string> s, int off)
{
    //vector<string> parameters = {};
    // string current = ""; //current parameter value
    // for (char c : rawText) //for each character in rawText
    // {
    //     if( c != '|') // if it is not a pipe character
    //     {
    //         current += c; //add c to current parameter
    //     }
    //     else if (c == '|') //if we encounter a pipe
    //     {
    //         parameters.push_back(current); //append whatever we have read to parameters
    //         current = ""; //reset the string
    //     }
    // }
    GISRecord new_record{off,s[0],s[1],s[2],s[3],
    s[4],s[5],s[6],s[7],
    s[8],s[9],s[10],s[11],
    s[12],s[13],s[14],s[15],
    s[16],s[17],s[18],s[19]};

    return new_record;
}


int CoordinateIndex::string2DMS(string coords)
{
    char orientation = coords[coords.length()-1];
    coords.erase(coords.end()); //remove last char
    int res = 0;
    if(orientation == 'N' || orientation == 'E')
    {
        res = stoi(coords);
    }
    else if(orientation == 'S' || orientation == 'W')
    {
        res = stoi(coords);
        res *= -1; //if south or west, our co-odrinate is a negative number
    }
    return res;
}

int CoordinateIndex::determineRegion(dms_coords parentRange, GISRecord* current_record,
    int westBound, int eastBound, int northBound, int southBound)
{
    //int quotient = this->buckets/2; //default is (4/2) = 2
    // int latDivide = parentRange.latCoords / quotient;
    // int longDivide = parentRange.longCoords / quotient;
    int return_node = 0;

    int latStep = parentRange.latCoords / 2;
    int longStep = parentRange.longCoords / this->buckets;

    int latOfInterest = string2DMS(current_record->getLat_DMS_prim()); // -ve or positive
    int longOfInterest = string2DMS(current_record->getLong_DMS_prim()); // -ve or positive
    
    int latNum = southBound;
    int latIncrements = 0;
    int longNum = westBound;
    int longIncrements = 0;

    while(latNum < latOfInterest && latNum < northBound)
    {
        latNum += latStep;
        latIncrements++;
    }

    while(longNum < longOfInterest && longNum < eastBound)
    {
        longNum += longStep;
        longIncrements++;
    }
    
    if(latIncrements == 2) //north hemisphere of our world. 
    {
        return_node = longIncrements-1; //maintaining 0 being first index
    }
    else if (latIncrements < 2) //southern hemisphere of our world
    {
        int upper_long_segments = (this->buckets/2);
        if(this->buckets %2 == 0) //if even buckets
        {
            return_node = upper_long_segments + (longIncrements) - 1;
        }
        else //odd buckets
        {
            return_node = upper_long_segments + (longIncrements+1) -1 ;
        }
    }
    return return_node;
    // //indicators
    // int n = 0; //north
    // int s = 0; //south
    // int w = 0; //east
    // int e = 0; //west

    // //eLimit + wLimit = total_longitude
    // //if long_record > total_longitude/2 => east of 0 deg long. else, it is west of 0 deg long
    // if(this_rec_coords.longCoords > longDivide)
    // {
    //     e = 1;
    // }
    // else
    // {
    //     w = 1;
    // }
    // //nLimit + sLimit = total_latitude
    // //if lat_record > total_latitude/2 => north of 0 deg lat. else, it is south of 0 deg lat
    // if(this_rec_coords.latCoords > latDivide)
    // {
    //     n = 1;
    // }
    // else 
    // {
    //     s = 1;
    // }

    // //time to return states
    // if(n == 1 && w == 1) //if north and west triggered
    // {
    //     return 0;
    // }
    // else if(n == 1 && e == 1) //if north and east triggered
    // {
    //     return 1;
    // }
    // else if(s == 1 && w == 1) //if south and west triggered
    // {
    //     return 2;
    // }
    // else if(s == 1 && e == 1) //if south and east triggered
    // {
    //     return 3;
    // }
}

int CoordinateIndex::determineRegion_split(dms_coords parentRange, int old_recordLat, int old_recordLong, 
        int westBound, int eastBound, int northBound, int southBound)
{
    int return_node = 0;

    int latStep = parentRange.latCoords / 2;
    int longStep = parentRange.longCoords / this->buckets;

    int latNum = southBound;
    int latIncrements = 0;
    int longNum = westBound;
    int longIncrements = 0;

    while(latNum < old_recordLat && latNum < northBound)
    {
        latNum += latStep;
        latIncrements++;
    }

    while(longNum < old_recordLong && longNum < eastBound)
    {
        longNum += longStep;
        longIncrements++;
    }
    
    if(latIncrements == 2) //north hemisphere of our world. 
    {
        return_node = longIncrements-1; //maintaining 0 being first index
    }
    else if (latIncrements < 2) //southern hemisphere of our world
    {
        int upper_long_segments = (this->buckets/2);
        if(this->buckets %2 == 0) //if even buckets
        {
            return_node = upper_long_segments + (longIncrements) - 1;
        }
        else //odd buckets
        {
            return_node = upper_long_segments + (longIncrements+1) -1 ;
        }
    }
    return return_node;
}

void CoordinateIndex::add_to_node(treeNode* add2This, dms_coords parentRange, GISRecord* addThis,
int p_westBound, int p_eastBound, int p_northBound, int p_southBound)
{
    int addThisLat = string2DMS(addThis->getLat_DMS_prim());
    int addThisLong = string2DMS(addThis->getLong_DMS_prim());
    dms_coords this_rec_coords{addThisLat,addThisLong};

    //determine add2This node status
    dms_coords nodeCoords = add2This->coordinates;
    int childrenAmount = add2This->children.size();
    if(((nodeCoords.latCoords == UNSET) && (nodeCoords.longCoords == UNSET2)) 
            && childrenAmount == 0) //if coords are unset and no children
    {
        add2This->range = parentRange;
        add2This->westBound = p_westBound;
        add2This->eastBound = p_eastBound;
        add2This->northBound = p_northBound;
        add2This->southBound = p_southBound;
        add2This->coordinates = this_rec_coords;
        add2This->offsets.push_back(addThis->getOffset());
        add2This->children = {}; //since was unset prior, we have no children at the moment
    } //changes to a SET state with no children
    else if (((nodeCoords.latCoords == UNSET) && (nodeCoords.longCoords == UNSET2)) 
            && childrenAmount > 0) //coords unset WITH children
    {
        //note that we use this sub-node's range and bounds
        int subNode = determineRegion(add2This->range, addThis, 
            add2This->westBound, add2This->eastBound, add2This->northBound, add2This->southBound);
        treeNode* sub = add2This->children[subNode];
        add_to_node(add2This->children[subNode], add2This->range, addThis, 
            sub->westBound, sub->eastBound, sub->northBound, sub->southBound);
    }
    else if (((nodeCoords.latCoords != UNSET) && (nodeCoords.longCoords != UNSET2)) 
            && childrenAmount == 0) //set cords and no children
    {
        dms_coords oldCoords = add2This->coordinates;
        add2This->coordinates.latCoords = UNSET;
        add2This->coordinates.longCoords = UNSET2;

        vector<int> oldOffsets = add2This->offsets;
        add2This->offsets.clear();

        int oldLatRange = add2This->range.latCoords;
        int oldLongRange = add2This->range.longCoords;
        int oldWestBound = add2This->westBound;
        int oldEastBound = add2This->eastBound;
        int oldNorthBound = add2This->northBound;
        int oldSouthBound = add2This->southBound;
        int total_long = (oldWestBound * (-1)) + (oldEastBound); //raw distance
        int total_lat = (oldNorthBound) + (oldSouthBound * (-1)); //raw distance
        int lat_parition = total_lat / this->buckets; //raw distance divided by number of regions (buckets)
        int long_partition = total_long / this->buckets;
        
        for(int i = 0; i < this->buckets; ++i)
        {   
            if(i < (this->buckets/2))
            {
                treeNode* node1;
                node1->range.latCoords = lat_parition;
                node1->range.longCoords = long_partition; //latCoords, longCoords
                node1->northBound = oldNorthBound;
                node1->southBound = oldSouthBound + (total_lat/2);
                node1->eastBound = oldWestBound + ((i+1)*long_partition);
                node1->westBound = oldWestBound + (i*long_partition);
                node1->coordinates.latCoords = UNSET;
                node1->coordinates.longCoords = UNSET2;
                node1->offsets = {};
                node1->children = {};
                //sample.push_back(node1); //vector of tree nodes
                add2This->children.push_back(node1); //add an empty vector of nodes k times
            }
            else // i>= k/2
            {
                treeNode *node1;
                node1->range.latCoords = lat_parition;
                node1->range.longCoords = long_partition; //latCoords, longCoords
                node1->northBound = oldNorthBound - (total_lat/2);
                node1->southBound = oldSouthBound;
                node1->eastBound = oldWestBound + ((i+1)*long_partition);
                node1->westBound = oldWestBound + (i*long_partition);
                add2This->coordinates.latCoords = UNSET;
                add2This->coordinates.longCoords = UNSET2;
                node1->offsets = {};
                node1->children = {};
                //sample.push_back(node1); //vector of tree nodes
                add2This->children.push_back(node1); //add an empty vector of nodes k times
            }
        }
        dms_coords newRange{lat_parition,long_partition};
        int old_record_newIndex = determineRegion_split(add2This->range, oldCoords.latCoords, 
            oldCoords.longCoords,oldWestBound,oldEastBound,oldNorthBound,oldSouthBound);
        auto it = add2This->children.begin();
        advance(it,old_record_newIndex);
        treeNode* n = *it;
        n->coordinates = oldCoords;
        n->offsets = oldOffsets;
        //finished adding the record that was previously by itself

        int subNode = determineRegion(add2This->range, addThis, 
            add2This->westBound, add2This->eastBound, add2This->northBound, add2This->southBound);

        treeNode* sub = add2This->children[subNode];

        add_to_node(add2This->children[subNode], add2This->range, addThis, 
            sub->westBound, sub->eastBound, sub->northBound, sub->southBound);

        // int childrenLatRange = oldLatRange / this->buckets;
        // int childrenLongRange = oldLongRange / this->buckets;
        // for(int i = 0; i < this->buckets; ++i)
        // {
        //     treeNode subNode;
        //     subNode.range{childrenLatRange,childrenLongRange}; //latCoords, longCoords
        //     subNode.coordinates{UNSET,UNSET2};
        //     subNode.offsets{{}};
        //     subNode.children{{}};
        //     //sample.push_back(node1); //vector of tree nodes
        //     add2This->children.push_back(subNode); //add an empty vector of nodes k times
        // }
    }   
}

// void CoordinateIndex::splitNode(GISRecord* this_record)
// {
//     //take the range values
//     //divide them with k. gives us entire lat and long range of each sub regions 

// }

void CoordinateIndex::add(GISRecord* record)
{
    //get lat of record i.e 383000N        
    string recLat_str = record->getLat_DMS_prim();
    int recLat = string2DMS(recLat_str);
    
    //get long of record i.e 0793259W
    string recLong_str = record->getLong_DMS_prim();
    int recLong = string2DMS(recLong_str);
    
    //turn them into dms_coords 
    dms_coords this_rec_coords{recLat,recLong};
    
    //I can go through each spot in tree vector
    //treeNode.range consist of integers latCoords, and longCoords
    
    int world_lat_range = (this->westLimit)*(-1) + this->eastLimit; //raw distance
    int world_long_range = (this->southLimit)*(-1) + this->northLimit;
    // int world_lat_partition = world_lat_range/this->buckets;
    // int world_long_partition = world_long_range/this->buckets;

    dms_coords parentRange{world_lat_range,world_long_range}; //range co ordinates of parent
    int subNode = determineRegion(parentRange, record, this->westLimit,
    this->eastLimit, this->northLimit, this->southLimit); //determine which sub region to place record
    
    // one of four states that leads to one of the major quadrants of our world
    // enter one of the 4 vector of treeNodes. (this can possibly be our state zero if doing recursive)
    // [0] vector has wLimit, nLimit, [1] has nLimit, eLimit
    // [2] vector has wLimit, sLimit, [3] has sLimit, eLimit 
    // if coordinates are unset and no children, 
    //  we can place current co-ordinate here along with the records it has

    //there will be a need to turn the current treeNode from just a node to,  
    //a treeNode with children treeNodes, and unset co-ords
    // indicate that there are multiple nodes
    //choosing to preserve the range value even when node ends up spawning children because can help with
        //the math

    add_to_node(&kTree[subNode], parentRange, record, this->westLimit,
    this->eastLimit, this->northLimit, this->southLimit);
    // do this after : 
    this->records.push_back(*record);
}

void CoordinateIndex::index_db()
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
            add(&new_record);
        } //EOF reached
    }
    else
    {
        cout << "error opening DB File (CoordinateIndex::index_db() method)" << endl;
    }
    dbFile.close();
}

vector<int> CoordinateIndex::traverseSubNode(treeNode* subnode, GISRecord* record)
{
    vector<int> answer = {};

    string lat = record->getLat_DMS_prim();
    string long_str = record->getLong_DMS_prim();
    int lat_record = string2DMS(lat);
    int long_record = string2DMS(long_str);

    dms_coords nodeCoords = subnode->coordinates;
    int childrenAmount = subnode->children.size();

    if(((nodeCoords.latCoords == UNSET) && (nodeCoords.longCoords == UNSET2)) 
            && childrenAmount == 0) //if coords are unset and no children
    {
        answer.push_back(-1); //nothing is set here, so not found
    } //changes to a SET state with no children
    else if (((nodeCoords.latCoords == UNSET) && (nodeCoords.longCoords == UNSET2)) 
            && childrenAmount > 0) //coords unset WITH children
    {
        int majorIndex = 0;
        for(int i = 0; i < subnode->children.size(); ++i)
        {
            int westB = subnode->children[i]->westBound;
            int eastB = subnode->children[i]->eastBound;
            int northB = subnode->children[i]->northBound;
            int southB = subnode->children[i]->southBound;

            if((long_record >= westB && long_record <= eastB) && (lat_record >= southB && lat_record <= northB))
            {
                majorIndex = i;
            }
        }
        answer.push_back(majorIndex);
        vector<int> subNodeTravel = traverseSubNode(&kTree[majorIndex], record);
        answer.insert(answer.end(), subNodeTravel.begin(),subNodeTravel.end());
    }
    else if (((nodeCoords.latCoords != UNSET) && (nodeCoords.longCoords != UNSET2)) 
            && childrenAmount == 0) //set cords and no children
    {
        if(nodeCoords.latCoords == lat_record && nodeCoords.longCoords == long_record)
        {
            answer.push_back(this->buckets); //pushing buckets means we found the answer at this level
            //means at the level in element that is before this number, in the answer vector, 
        }
        else
        {
            answer.push_back(-1); //not found
        }
    }

    return answer;
}

//for finding exact coords
vector<int> CoordinateIndex::traverseSubNode_b(treeNode* subnode, int lat_Coords, int long_Coords)
{
    vector<int> answer = {};

    dms_coords nodeCoords = subnode->coordinates;
    int childrenAmount = subnode->children.size();

    if(((nodeCoords.latCoords == UNSET) && (nodeCoords.longCoords == UNSET2)) 
            && childrenAmount == 0) //if coords are unset and no children
    {
        answer.push_back(-1); //nothing is set here, so not found
    } //changes to a SET state with no children
    else if (((nodeCoords.latCoords == UNSET) && (nodeCoords.longCoords == UNSET2)) 
            && childrenAmount > 0) //coords unset WITH children
    {
        int majorIndex = 0;
        for(int i = 0; i < subnode->children.size(); ++i)
        {
            int westB = subnode->children[i]->westBound;
            int eastB = subnode->children[i]->eastBound;
            int northB = subnode->children[i]->northBound;
            int southB = subnode->children[i]->southBound;

            if((long_Coords >= westB && long_Coords <= eastB) && (lat_Coords >= southB && lat_Coords <= northB))
            {
                majorIndex = i;
            }
        }
        answer.push_back(majorIndex);
        vector<int> subNodeTravel = traverseSubNode_b(&kTree[majorIndex], lat_Coords, long_Coords);
        answer.insert(answer.end(), subNodeTravel.begin(),subNodeTravel.end());
    }
    else if (((nodeCoords.latCoords != UNSET) && (nodeCoords.longCoords != UNSET2)) && childrenAmount == 0) //set cords and no children
    {
        if(nodeCoords.latCoords == lat_Coords && nodeCoords.longCoords == long_Coords)
        {
            answer.push_back(this->buckets); //pushing buckets means we found the answer at this level
            //means at the level in element that is before this number, in the answer vector, 
        }
        else
        {
            answer.push_back(-1); //not found
        }
    }

    return answer;
}

//for finding range of coords
vector<int> CoordinateIndex::traverseSubNode_range(treeNode* subnode, dms_coords center, int lat_Coords, int long_Coords)
{
    vector<int> answer = {};
    int westBound_region = center.longCoords - long_Coords;
    int eastBound_region = center.longCoords + long_Coords;
    int northBound_region = center.latCoords + lat_Coords;
    int southBound_region = center.latCoords - lat_Coords;
    
    dms_coords nodeCoords = subnode->coordinates;
    int childrenAmount = subnode->children.size();

    if(((nodeCoords.latCoords == UNSET) && (nodeCoords.longCoords == UNSET2)) 
            && childrenAmount == 0) //if coords are unset and no children
    {
        answer.push_back(-1); //nothing is set here, so not found
    } //changes to a SET state with no children
    else if (((nodeCoords.latCoords == UNSET) && (nodeCoords.longCoords == UNSET2)) 
            && childrenAmount > 0) //coords unset WITH children
    {
        int majorIndex = 0;
        for(int i = 0; i < subnode->children.size(); ++i)
        {
            int westB = subnode->children[i]->westBound;
            int eastB = subnode->children[i]->eastBound;
            int northB = subnode->children[i]->northBound;
            int southB = subnode->children[i]->southBound;

            if((westBound_region >= westB && eastBound_region <= eastB) && 
                (southBound_region >= southB && northBound_region <= northB))
            {
                majorIndex = i;
            }
        }
        answer.push_back(majorIndex);
        vector<int> subNodeTravel = traverseSubNode_range(&kTree[majorIndex], center, lat_Coords, long_Coords);
        answer.insert(answer.end(), subNodeTravel.begin(),subNodeTravel.end());
    }
    else if (((nodeCoords.latCoords != UNSET) && (nodeCoords.longCoords != UNSET2)) 
            && childrenAmount == 0) //set cords and no children
    {
        if((nodeCoords.longCoords >= westBound_region && nodeCoords.longCoords <= eastBound_region) && 
        (nodeCoords.latCoords >= southBound_region && nodeCoords.latCoords <= northBound_region))
        {
            answer.push_back(this->buckets); //pushing buckets means we found the answer at this level
            //means at the level in element that is before this number, in the answer vector, 
        }
        else
        {
            answer.push_back(-1); //not found
        }
    }

    return answer;
}

vector<int> CoordinateIndex::lookForCoords(int lat_Coords, int long_Coords)
{
    vector<int> answer = {};
    int majorIndex = -1;
    for(int i = 0; i < this->kTree.size(); ++i)
    {
        int westB = kTree[i].westBound;
        int eastB = kTree[i].eastBound;
        int northB = kTree[i].northBound;
        int southB = kTree[i].southBound;

        if((long_Coords >= westB && long_Coords <= eastB) && (lat_Coords >= southB && lat_Coords <= northB))
        {
            majorIndex = i;
        }
    }
    answer.push_back(majorIndex);
    if(majorIndex != -1)
    {
        vector<int> subNodeTravel = traverseSubNode_b(&kTree[majorIndex], lat_Coords,long_Coords);
        answer.insert(answer.end(),subNodeTravel.begin(),subNodeTravel.end());
    }
    
    return answer;
}

vector<int> CoordinateIndex::lookFor(GISRecord* record)
{
    vector<int> answer = {};
    string lat = record->getLat_DMS_prim();
    string long_str = record->getLong_DMS_prim();
    int lat_record = string2DMS(lat);
    int long_record = string2DMS(long_str);
    int majorIndex = -1;
    for(int i = 0; i < this->kTree.size(); ++i)
    {
        int westB = kTree[i].westBound;
        int eastB = kTree[i].eastBound;
        int northB = kTree[i].northBound;
        int southB = kTree[i].southBound;

        if((long_record >= westB && long_record <= eastB) && (lat_record >= southB && lat_record <= northB))
        {
            majorIndex = i;
        }
    }
    answer.push_back(majorIndex);
    if(majorIndex != -1)
    {
        vector<int> subNodeTravel = traverseSubNode(&kTree[majorIndex], record);
        answer.insert(answer.end(),subNodeTravel.begin(),subNodeTravel.end());
    }
    
    return answer;
}


vector<int> CoordinateIndex::lookForCoords_range(dms_coords center, int lat_Coords, int long_Coords)
{
    vector<int> answer = {};
    int westBound_region = center.longCoords - long_Coords;
    int eastBound_region = center.longCoords + long_Coords;
    int northBound_region = center.latCoords + lat_Coords;
    int southBound_region = center.latCoords - lat_Coords;
    
    int majorIndex = -1;
    for(int i = 0; i < this->kTree.size(); ++i)
    {
        int westB = kTree[i].westBound;
        int eastB = kTree[i].eastBound;
        int northB = kTree[i].northBound;
        int southB = kTree[i].southBound;

        if((westBound_region >= westB && eastBound_region <= eastB) && (southBound_region >= southB && northBound_region <= northB))
        {
            majorIndex = i;
        }
    }
    answer.push_back(majorIndex);
    if(majorIndex != -1)
    {
        vector<int> subNodeTravel = traverseSubNode_range(&kTree[majorIndex], center, lat_Coords,long_Coords);
        answer.insert(answer.end(),subNodeTravel.begin(),subNodeTravel.end());
    }
    
    return answer;
}

vector<int> CoordinateIndex::what_is_at(dms_coords coords)
{
    vector<int> offs = {};
    vector<int> found = lookForCoords(coords.latCoords, coords.longCoords);
    int lastDigit = found[found.size()-1];
    if(lastDigit == -1)
    {
        cout << "co ordinates not found" << endl;
    }
    else if(lastDigit == this->buckets)
    {
        treeNode firstPath = this->kTree[found[0]];
        auto it_node = firstPath.children.begin();
        for(int i = 1; i < found.size(); ++i)
        {
            if (i != this->buckets)
            {
                treeNode* newFound = firstPath.children[i];
                firstPath = *newFound; //readjust the new found child
                it_node = newFound->children.begin();
                advance(it_node,i);
            }
        }
        treeNode *hasCoords = *it_node;
        vector<int> o = hasCoords->offsets;
        offs.insert(offs.begin(),o.begin(),o.end());
    }

    return offs;
}

vector<int> CoordinateIndex::what_is_in(dms_coords center_coords, int half_height, int half_width, string optional)
{
    vector<int> paths = lookForCoords_range(center_coords, half_height, half_width);
    treeNode n;
    for(int i = 0; i < paths.size(); ++i)
    {
        if(i == 0)
        {
            if((paths[0] != -1) || (paths[0] != this->buckets))
            {
                n = this->kTree[paths[0]];
            }
        }
        else
        {
            if((paths[i] != -1) || (paths[i] != this->buckets))
            {
                treeNode* newNode = n.children[i];
                n = *newNode;
            }
        }
    }
    vector<int> rec_offsets = n.offsets;
    return rec_offsets;
}

void CoordinateIndex::remove(GISRecord* record)
{
    vector<int> foundPath = lookFor(record);
    int lastDigit = foundPath[foundPath.size()-1];
    if(lastDigit == -1)
    {
        cout << "record not found in co-ordinate index" << endl;
    }
    else if (lastDigit == this->buckets)
    {
        treeNode found = this->kTree[foundPath[0]];
        auto it_node = found.children.begin();
        for(int i = 1; i < foundPath.size(); ++i)
        {
            if (i != this->buckets)
            {
                treeNode* newFound = found.children[i];
                found = *newFound; //readjust the new found child
                it_node = newFound->children.begin();
                advance(it_node,i);
            }
        }
        // found.coordinates=this->unsetNode;
        found.coordinates.latCoords = UNSET;
        found.coordinates.longCoords = UNSET2;
        found.offsets.clear();
        found.children={};
        //found.erase(it_node);
        cout << "erased co-ordinate and offset info." << endl;
    }
}

void CoordinateIndex::print_subTree(vector<treeNode*> subnode)
{
    for(int i = 0; i < subnode.size(); ++i)
    {
        auto it = subnode.begin();
        advance(it,i);
        treeNode* n = *it;
        dms_coords nodeCoords = n->coordinates;
        int childrenAmount = n->children.size();
        if(((nodeCoords.latCoords == UNSET) && (nodeCoords.longCoords == UNSET2)) 
                && childrenAmount == 0) //if coords are unset and no children
        {
            cout << "subTree co-ordinates UNSET" << endl; //nothing is set here, so not found
        } 
        else if (((nodeCoords.latCoords == UNSET) && (nodeCoords.longCoords == UNSET2)) 
                && childrenAmount > 0) //coords unset WITH children
        {
            print_subTree(n->children);
        }
        else if (((nodeCoords.latCoords != UNSET) && (nodeCoords.longCoords != UNSET2)) 
                && childrenAmount == 0) //coords set;  NO children
        {
            cout << "sub-tree index: " << i <<", contains: " <<endl;
            cout <<"offsets: " << endl;
            for(int x : subnode[i]->offsets)
            {
                cout << x << ", ";
            } 
            cout << endl;
        }
    }
}

void CoordinateIndex::to_str()
{
    for(int j = 0; j < this->kTree.size(); ++j)
    {
        treeNode t = kTree[j];
        dms_coords nodeCoords = t.coordinates;
        int childrenAmount = t.children.size();

        if(((nodeCoords.latCoords == UNSET) && (nodeCoords.longCoords == UNSET2))
            && childrenAmount == 0) //if coords are unset and no children
        {
            cout << "parent_node : " << j << ": UNSET" << endl;//nothing is set here, so not found
        } //changes to a SET state with no children
        else if (((nodeCoords.latCoords == UNSET) && (nodeCoords.longCoords == UNSET2)) 
            && childrenAmount > 0) //coords unset WITH children
        {
            //print subTree
            cout << "parent_node : " << j << endl;
            print_subTree(kTree[j].children);
        }
        else if (((nodeCoords.latCoords != UNSET) && (nodeCoords.longCoords != UNSET2)) 
            && childrenAmount == 0) //set cords and no children
        {
            cout << "parent_node : " << j << endl;
            cout << "child of " << j << ", contains: "<< endl;
            for (int o : t.offsets)
            {
                cout << o <<", ";
            }
            cout << endl;
        }
    }
}
