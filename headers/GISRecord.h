#pragma once
#include <iostream>
#include <string>

using namespace std;

class GISRecord 
{
private:

	//string dbFileName;

	int offset; //number of bytes from start of gis file (not sure if we are accounting this when we process. 
	//														Most likely it's in use somehwere)

	string feat_id; //feature_id (change to int)
	string feat_name; //feature_name
	string feat_class; //featur_class

	string state_alpha; // state alphabet
	string state_num; //state numeric (change to int)
	
	string country_name; //country name
	string country_num; //country numeric (change to int)

	string lat_dms_primary; //should be struct DMS
	string long_dms_primary; //should be struct DMS
	
	string lat_dec_primary; //(change to double)
	string long_dec_primary; //(change to double)

	string src_lat_dms;  //should be struct DMS
	string src_long_dms; //should be struct DMS

	string src_lat_dec; //(change to double)
	string src_long_dec; //(change to double)

	string elevation_m; //change to int
	string elevation_ft; //change to int

	string map_name;

	string date_created; // MM/DD/YYYY format
	string date_edited; // MM/DD/YYYY format	

public:
	GISRecord(); //default constructor

	//get ready
	GISRecord(int off, string id_feat, string name_feat, string class_feat, 
		string alpha_state, string num_state, string name_country, string num_country, 
		string dms_primary_lat, string dms_primary_long, string dec_primary_lat, 
		string dec_primary_long, string dms_src_lat, string dms_src_long, 
		string dec_src_lat, string dec_src_long, string m_elevation, string ft_elevation, 
		string mapName,string createdDate, string editedDate, // MM/DD/YYYY format	
	);
	
	//void create_db_file();



	//potential helper functions
	//dms to decimal degree converters

	/*getter and setter declarations*/
	/*Offset*/
	int getOffset();
	void setOffset(int off);

	/*Feature*/
	string getFeat_id();
	void setFeat_id(int f_id);

	string getFeat_name();
	void setFeat_name(string name);

	string getFeat_class();
	void setFeat_class(string className);

	/*State*/
	string getState_alpha();
	void setState_alpha(string alpha);

	string getState_num();
	void setState_num(int num);

	/*Country*/
	string getCountry_name();
	void setCounty_name(string country);

	string getCountry_num();
	void setCountry_num(int num);

	/*Latitude/Longitude*/
	/*Primary Lat/Long*/
	/*DMS*/
	string getLat_DMS_prim();
	void setLat_DMS_prim(string lat_dms);
	string getLong_DMS_prim();
	void setLong_DMS_prim(string long_dms);
	/*Decimal*/
	string getLat_Dec_prim();
	void setLat_Dec_prim(string lat_dec);
	string getLong_Dec_prim();
	void setLong_Dec_prim(string long_dec);
	
	/*Source Lat/Long */
	/*DMS*/
	string getLat_DMS_src();
	void setLat_DMS_src(string lat_dms);
	string getLong_DMS_src();
	void setLong_DMS_src(string long_dms);
	/*Decimal*/
	string getLat_Dec_src();
	void setLat_Dec_src(string lat_dec);
	string getLong_Dec_src();
	void setLong_Dec_src(string long_dec);

	/*Elevation*/
	string getElevation_m();
	void setElevation_m(string m);
	string getElevation_ft();
	void setElevation_ft(string ft);

	/*Map Name*/
	string getMap_name();
	void setMap_name(string mapName);

	/*Date Created and modified*/
	string getDate_created();
	void setDate_created(string date);
	string getDate_edited();
	void setDate_edited(string date);

};