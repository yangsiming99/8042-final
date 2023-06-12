#include "../headers/GISRecord.h"
#include <string.h>
#include <fstream>
#include <iostream>

using namespace std;

//idk, use this for database stuff I guess

ofstream db_File;
string dbFileName;

GISRecord::GISRecord(string ndbFile) 
{
	dbFileName = ndbFile;
}

void GISRecord::create_db_file()
{
	cout << "hi there" << endl;
	db_File.open(dbFileName, ios_base::trunc);
	db_File << "THIS IS THE DB FILE SDKLFJSLK \n";
	db_File.close();
}



/*getter and setter declarations*/
/*Feature*/
int getFeat_id()
{
	return this->feat_id;
}
void setFeat_id(int f_id)
{
	this->feat_id = f_id;
}

string getFeat_name()
{
	return this->feat_name;
}
void setFeat_name(string name)
{
	this->feat_name = name;
}

string getFeat_class()
{
	return this->feat_class;
}
void setFeat_class(string className)
{
	this->feat_class = className;
}

/*State*/
string getState_alpha()
{
	return this->state_alpha;
}
void setState_alpha(string alpha)
{
	this->state_alpha = alpha;
}

int getState_num()
{
	return this->state_num;
}
void setState_num(int num)
{
	this->state_num = num;
}

/*Country*/
string getCountry_name()
{
	return this->country_name;
}
void setCounty_name(string country)
{
	this->country_name = country;
}

int getCountry_num()
{
	return this->country_num;
}	
void setCountry_num(int num)
{
	this->country_num = num;
}

/*Latitude/Longitude*/
/*Primary Lat/Long*/
/*DMS*/
string getLat_DMS_prim()
{
	return this->lat_dms_primary;
}
void setLat_DMS_prim(string lat_dms)
{
	this->lat_dms_primary = lat_dms;
}
string getLong_DMS_prim()
{
	return this->long_dms_primary; 
}
void setLong_DMS_prim(string long_dms)
{
	this->long_dms_primary = long_dms;
}

/*Decimal*/
double getLat_Dec_prim()
[
	return this->lat_dec_primary;
]
void setLat_Dec_prim(double lat_dec)
{
	this->lat_dec_primary = lat_dec;
}
double getLong_Dec_prim()
{
	return this->long_dec_primary;
}
void setLong_Dec_prim(double long_dec)
{
	this->long_dec_primary = long_dec;
}

/*Source Lat/Long */
/*DMS*/
string getLat_DMS_src()
{
	return this->src_lat_dms;
}
void setLat_DMS_src(string lat_dms)
{
	this->src_lat_dms = lat_dms
}
string getLong_DMS_src()
{
	return this->src_long_dms;
}
void setLong_DMS_src(string long_dms)
{
	this->src_long_dms = long_dms;
}

/*Decimal*/
double getLat_Dec_src()
{
	return this->src_lat_dec;
}
void setLat_Dec_src(double lat_dec)
{
	this->src_lat_dec = lat_dec;
}
double getLong_Dec_src()
{
	return this->src_long_dec;
}
void setLong_Dec_src(double long_dec)
{
	this->src_long_dec = long_dec;
}

/*Elevation*/
int getElevation_m()
{
	return this->elevation_m;
}
void setElevation_m(int m)
{
	this->elevation_m = m;
}
int getElevation_ft()
{
	return this->elevation_ft;
}
void setElevation_ft(int ft)
{
	this->elevation_ft = ft;
}

/*Map Name*/
string getMap_name()
{
	return this->map_name;
}
void setMap_name(string mapName)
{
	this->map_name = mapName;
}

/*Date Created and modified*/
string getDate_created()
{
	return this->date_created;
}
void setDate_created(string date)
{
	this->date_created = date;
}
string getDate_edited()
{
	return this->date_edited;
}
void setDate_edited(string date)
{
	this->date_edited = date;
}