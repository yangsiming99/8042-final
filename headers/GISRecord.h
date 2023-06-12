#pragma once
#include <iostream>
#include <string.h>

using namespace std;

class GISRecord 
{
private:

	string dbFileName;

	int feat_id; //feature_id
	string feat_name; //feature_name
	string feat_class; //featur_class

	string state_alpha; // state alphabet
	int state_num; //state numeric
	
	string country_name; //country name
	int country_num; //country numeric

	string lat_dms_primary; //should be struct DMS
	string long_dms_primary; //should be struct DMS
	
	double lat_dec_primary:
	double long_dec_primary;

	string src_lat_dms;  //should be struct DMS
	string src_long_dms; //should be struct DMS

	double src_lat_dec;
	double src_long_dec;

	int elevation_m;
	int elevation_ft;

	string map_name;

	string date_created; // MM/DD/YYYY format
	string date_edited; // MM/DD/YYYY format	

public:
	GISRecord(string dbFile);
	void create_db_file();


	/*getter and setter declarations*/
	/*Feature*/
	int getFeat_id();
	void setFeat_id(int f_id);

	string getFeat_name();
	void setFeat_name(string name);

	string getFeat_class();
	void setFeat_class(string className);

	/*State*/
	string getState_alpha();
	void setState_alpha(string alpha);

	int getState_num();
	void setState_num(int num);

	/*Country*/
	string getCountry_name();
	void setCounty_name(string country);

	int getCountry_num();
	void setCountry_num(int num);

	/*Latitude/Longitude*/
	/*Primary Lat/Long*/
	/*DMS*/
	string getLat_DMS_prim();
	void setLat_DMS_prim(string lat_dms);
	string getLong_DMS_prim();
	void setLong_DMS_prim(string long_dms);
	/*Decimal*/
	double getLat_Dec_prim();
	void setLat_Dec_prim(double lat_dec);
	double getLong_Dec_prim();
	void setLong_Dec_prim(double long_dec);
	
	/*Source Lat/Long */
	/*DMS*/
	string getLat_DMS_src();
	void setLat_DMS_src(string lat_dms);
	string getLong_DMS_src();
	void setLong_DMS_src(string long_dms);
	/*Decimal*/
	double getLat_Dec_src();
	void setLat_Dec_src(double lat_dec);
	double getLong_Dec_src();
	void setLong_Dec_src(double long_dec);

	/*Elevation*/
	int getElevation_m();
	void setElevation_m(int m);
	int getElevation_ft();
	void setElevation_ft(int ft);

	/*Map Name*/
	string getMap_name();
	void setMap_name(string mapName);

	/*Date Created and modified*/
	string getDate_created();
	void setDate_created(string date);
	string getDate_edited();
	void setDate_edited(string date);

};