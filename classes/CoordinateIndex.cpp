#include <string>
#include <vector>
#include <fstream>
#include <iostream>

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
CoordinateIndex::CoordinateIndex(int wLimit, int eLimit, int nLimit, int sLimit, int k)
: westLimit(wLimit), eastLimit(eLimit), northLimit(nLimit), southLimit(sLimit), buckets(k),
{
    this->dbPath = "";
    vector<treeNode> sample = {};
    
    total_lat = wLimit + eLimit;
    total_long = nLimig + sLimit;
    lat_parition = total_lat / k;
    long_partition = total_long / k;

    for(int i = 0; i < k; ++i)
    {   
        treeNode node1;
        node1.range{lat_parition,long_partition}; //latCoords, longCoords
        node1.coordinates = this->unsetNode;
        node1.offsets{{}};
        node1.children{{}};
        sample.push_back(node1); //vector of tree nodes
        this->kTree[i].push_back(sample); //add an empty vector of nodes k times
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

void changeK(int k)
{
    this->buckets = k;
}



void splitNode(GISRecord* this_record)
{
    //take the range values
    //divide them with k. gives us entire lat and long range of each sub regions 
    
}

void add(GISRecord* record)
{
    // do this after : this.records.push_back(record);
    //get lat of record i.e 383000N 
    //get long of record i.e 0793259W
        //convert them by removing the last characters
        //if N and E, it's positive, if S and W it's negative
        //if N and E, change to stoi, keep the integer
        //if W and S, change to stoi, multiply by -1
        //turn them into dms_coords 
    //I can go through each spot in tree vector
    //treeNode, range consist of integers lat_partition, and long_partition
    //lat_parition give us the latitude range in the node
    //long_parition give us the longitude range in the node
    //lat_partition / 2 gives us the distance from center of region to west/east most bound
    //long_partition / 2 gives us the distance from center of region to north/south most bound
    
    //eLimit + wLimit = total_longitude
    //if long_record > total_longitude/2 => east of 0 deg long. else, it is west of 0 deg long
    //nLimit + sLimit = total_latitude
    //if long_record > total_latitude/2 => north of 0 deg lat. else, it is south of 0 deg lat
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


}

