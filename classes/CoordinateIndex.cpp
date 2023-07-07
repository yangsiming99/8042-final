#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <iterator>
#include <algorithm>

#include "../headers/CoordinateIndex.h"
#include "../headers/GISRecord.h"
#include "../headers/Logger.h"

#define LAT_OUT_OF_BOUNDS 200
#define LONG_OUT_OF_BOUNDS 200

using namespace std;

CoordinateIndex::CoordinateIndex()
{
    this->westLimit = 150;
    this->eastLimit = 150;
    this->northLimit = 45;
    this->southLimit = 45;
    this->buckets = 4;
    this->dbPath = "";
    this->kTree = {};
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
    
    total_long = (string2DMS(wLimit) * (-1)) + string2DMS(eLimit); //raw distance
    total_lat = string2DMS(nLimit) + (string2DMS(sLimit) * (-1)); //raw distance
    lat_parition = total_lat / k; //raw distance divided by number of regions (buckets)
    long_partition = total_long / k;

    for(int i = 0; i < k; ++i)
    {   
        if(i < k/2)
        {
            treeNode node1;
            node1.range{lat_parition,long_partition}; //latCoords, longCoords
            node1.northBound = string2DMS(nLimit);
            node1.southBound = string2DMS(sLimit) + (total_lat/2);
            node1.eastBound = string2DMS(wLimit) + ((i+1)*long_partition);
            node1.westBound = string2DMS(wLimit) + (i*long_partition);
            node1.coordinates = this->unsetNode;
            node1.offsets{{}};
            node1.children{{}};
            //sample.push_back(node1); //vector of tree nodes
            this->kTree.push_back(node1); //add an empty vector of nodes k times
        }
        else // i>= k/2
        {
            treeNode node1;
            node1.range{lat_parition,long_partition}; //latCoords, longCoords
            node1.northBound = string2DMS(nLimit) - (total_lat/2);
            node1.southBound = string2DMS(sLimit);
            node1.eastBound = string2DMS(wLimit) + ((i+1)*long_partition);
            node1.westBound = string2DMS(wLimit) + (i*long_partition);
            node1.coordinates = this->unsetNode;
            node1.offsets{{}};
            node1.children{{}};
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

int string2DMS(string coords)
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
    int addThisLat = string2DMS(addThis->getLat_DMS_prim);
    int addThisLong = string2DMS(addThis->getLong_DMS_prim);
    dms_coords this_rec_coords{addThisLat,addThisLong};

    //determine add2This node status
    dms_coords nodeCoords = add2This->coordinates;
    int childrenAmount = add2This->children.length();
    if((nodeCoords == this->unsetNode) && childrenAmount == 0) //if coords are unset and no children
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
    else if ((nodeCoords == this->unsetNode) && childrenAmount > 0) //coords unset WITH children
    {
        //note that we use this sub-node's range and bounds
        int subNode = determineRegion(add2This->range, addThis, 
            add2This->westBound, add2This->eastBound, add2This->northBound, add2This->southBound);
        treeNode sub = add2This->children[subNode];
        add_to_node(add2This->children[subNode], add2This->range, addThis, 
            sub->westBound, sub->eastBound, sub->northBound, sub->southBound);
    }
    else if ((nodeCoords != this->unsetNode) && childrenAmount == 0) //set cords and no children
    {
        dms_coords oldCoords = add2This->coordinates;
        add2This->coordinates = this.unsetNode;

        vector<int> oldOffsets = add2This->offsets;
        add2This->offsets.clear();

        int oldLatRange = add2This->range.latCoords;
        int oldLongRange = add2This->range.longCoords;
        int oldWestBound = add2This->westBound;
        int oldEastBound = add2This->eastBound;
        int oldNorthBound = add2This->northBound;
        int oldSouthBound = add2This->southBound;
        total_long = (oldWestBound * (-1)) + (oldEastBound); //raw distance
        total_lat = (oldNorthBound) + (oldSouthBound * (-1)); //raw distance
        lat_parition = total_lat / this->buckets; //raw distance divided by number of regions (buckets)
        long_partition = total_long / this->buckets;
        
        for(int i = 0; i < this->buckets; ++i)
        {   
            if(i < (this->buckets/2))
            {
                treeNode node1;
                node1.range{lat_parition,long_partition}; //latCoords, longCoords
                node1.northBound = oldNorthBound;
                node1.southBound = oldSouthBound + (total_lat/2);
                node1.eastBound = oldWestBound + ((i+1)*long_partition);
                node1.westBound = oldWestBound + (i*long_partition);
                node1.coordinates = this->unsetNode;
                node1.offsets{{}};
                node1.children{{}};
                //sample.push_back(node1); //vector of tree nodes
                add2This->children.push_back(node1); //add an empty vector of nodes k times
            }
            else // i>= k/2
            {
                treeNode node1;
                node1.range{lat_parition,long_partition}; //latCoords, longCoords
                node1.northBound = oldNorthBound - (total_lat/2);
                node1.southBound = oldSouthBound;
                node1.eastBound = oldWestBound + ((i+1)*long_partition);
                node1.westBound = oldWestBound + (i*long_partition);
                node1.coordinates = this->unsetNode;
                node1.offsets{{}};
                node1.children{{}};
                //sample.push_back(node1); //vector of tree nodes
                add2This->children.push_back(node1); //add an empty vector of nodes k times
            }
        }
        dms_coords newRange{lat_parition,long_partition};
        int old_record_newIndex = determineRegion_split(add2This->range, oldCoords.latCoords, 
            oldCoords.longCoords,oldWestBound,oldEastBound,oldNorthBound,oldSouthBound);
        auto it = add2This->children.begin();
        advance(it,old_record_newIndex);
        treeNode* n = add2This->children.at(it);
        n->coordinates = oldCoords;
        n->offsets = oldOffsets;
        //finished adding the record that was previously by itself

        int subNode = determineRegion(add2This->range, addThis, 
            add2This->westBound, add2This->eastBound, add2This->northBound, add2This->southBound);

        treeNode sub = add2This->children[subNode];

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

void CoordinateIndex::splitNode(GISRecord* this_record)
{
    //take the range values
    //divide them with k. gives us entire lat and long range of each sub regions 

}

void CoordinateIndex::add(GISRecord* record)
{
    //get lat of record i.e 383000N        
    string recLat_str = record->getLat_DMS_prim;
    int recLat = string2DMS(recLat_str);
    
    //get long of record i.e 0793259W
    string recLong_str = record->getLong_DMS_prim;
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

    add_to_node(kTree[subNode], parentRange, record, this->westLimit,
    this->eastLimit, this->northLimit, this->southLimit);
    // do this after : 
    this.records.push_back(record);


}

