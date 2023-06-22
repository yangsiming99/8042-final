#include "../headers/GisRecord.h"
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

//idk, use this for database stuff I guess

// ofstream db_File;
// string dbFileName;

GISRecord::GISRecord(int off, string id_feat, string name_feat, string class_feat, 
		string alpha_state, string num_state, string name_country, string num_country, 
		string dms_primary_lat, string dms_primary_long, string dec_primary_lat, 
		string dec_primary_long, string dms_src_lat, string dms_src_long, 
		string dec_src_lat, string dec_src_long, string m_elevation, string ft_elevation, 
		string mapName,string createdDate, string editedDate // MM/DD/YYYY format	
):  offset(off), feat_id(id_feat), feat_name(name_feat), feat_class(class_feat),
	state_alpha(alpha_state), state_num(num_state), country_name(name_country),
	country_num(num_country), 
	lat_dms_primary(dms_primary_lat),long_dms_primary(dms_primary_long),
	lat_dec_primary(dec_primary_lat), long_dec_primary(dec_primary_long), 
	src_lat_dec(dec_src_lat), src_long_dec(dec_src_long),
	src_lat_dms(dms_src_lat), src_long_dms(dms_src_long),
	elevation_m(m_elevation), elevation_ft(ft_elevation),
	map_name(mapName), date_created(createdDate), date_edited(editedDate)
{
	//cout << "GISRecord constructed using initiatlization list" << endl;
}

// void GISRecord::create_db_file()
// {
// 	cout << "hi there" << endl;
// 	db_File.open(dbFileName, ios_base::trunc);
// 	db_File << "THIS IS THE DB FILE SDKLFJSLK \n";
// 	db_File.close();
// }



/*getter and setter declarations*/
int GISRecord::getOffset()
{
	return this->offset;
}
void GISRecord::setOffset(int off)
{
	this->offset = off;
}

/*Feature*/
string GISRecord::getFeat_id()
{
	return this->feat_id;
}
void GISRecord::setFeat_id(int f_id)
{
	this->feat_id = f_id;
}

string GISRecord::getFeat_name()
{
	return this->feat_name;
}
void GISRecord::setFeat_name(string name)
{
	this->feat_name = name;
}

string GISRecord::getFeat_class()
{
	return this->feat_class;
}
void GISRecord::setFeat_class(string className)
{
	this->feat_class = className;
}

/*State*/
string GISRecord::getState_alpha()
{
	return this->state_alpha;
}
void GISRecord::setState_alpha(string alpha)
{
	this->state_alpha = alpha;
}

string GISRecord::getState_num()
{
	return this->state_num;
}
void GISRecord::setState_num(int num)
{
	this->state_num = num;
}

/*Country*/
string GISRecord::getCountry_name()
{
	return this->country_name;
}
void GISRecord::setCounty_name(string country)
{
	this->country_name = country;
}

string GISRecord::getCountry_num()
{
	return this->country_num;
}	
void GISRecord::setCountry_num(int num)
{
	this->country_num = num;
}

/*Latitude/Longitude*/
/*Primary Lat/Long*/
/*DMS*/
string GISRecord::getLat_DMS_prim()
{
	return this->lat_dms_primary;
}
void GISRecord::setLat_DMS_prim(string lat_dms)
{
	this->lat_dms_primary = lat_dms;
}
string GISRecord::getLong_DMS_prim()
{
	return this->long_dms_primary; 
}
void GISRecord::setLong_DMS_prim(string long_dms)
{
	this->long_dms_primary = long_dms;
}

/*Decimal*/
string GISRecord::getLat_Dec_prim()
{
	return this->lat_dec_primary;
}
void GISRecord::setLat_Dec_prim(string lat_dec)
{
	this->lat_dec_primary = lat_dec;
}
string GISRecord::getLong_Dec_prim()
{
	return this->long_dec_primary;
}
void GISRecord::setLong_Dec_prim(string long_dec)
{
	this->long_dec_primary = long_dec;
}

/*Source Lat/Long */
/*DMS*/
string GISRecord::getLat_DMS_src()
{
	return this->src_lat_dms;
}
void GISRecord::setLat_DMS_src(string lat_dms)
{
	this->src_lat_dms = lat_dms;
}
string GISRecord::getLong_DMS_src()
{
	return this->src_long_dms;
}
void GISRecord::setLong_DMS_src(string long_dms)
{
	this->src_long_dms = long_dms;
}

/*Decimal*/
string GISRecord::getLat_Dec_src()
{
	return this->src_lat_dec;
}
void GISRecord::setLat_Dec_src(string lat_dec)
{
	this->src_lat_dec = lat_dec;
}
string GISRecord::getLong_Dec_src()
{
	return this->src_long_dec;
}
void GISRecord::setLong_Dec_src(string long_dec)
{
	this->src_long_dec = long_dec;
}

/*Elevation*/
string GISRecord::getElevation_m()
{
	return this->elevation_m;
}
void GISRecord::setElevation_m(string m)
{
	this->elevation_m = m;
}
string GISRecord::getElevation_ft()
{
	return this->elevation_ft;
}
void GISRecord::setElevation_ft(string ft)
{
	this->elevation_ft = ft;
}

/*Map Name*/
string GISRecord::getMap_name()
{
	return this->map_name;
}
void GISRecord::setMap_name(string mapName)
{
	this->map_name = mapName;
}

/*Date Created and modified*/
string GISRecord::getDate_created()
{
	return this->date_created;
}
void GISRecord::setDate_created(string date)
{
	this->date_created = date;
}
string GISRecord::getDate_edited()
{
	return this->date_edited;
}
void GISRecord::setDate_edited(string date)
{
	this->date_edited = date;
}