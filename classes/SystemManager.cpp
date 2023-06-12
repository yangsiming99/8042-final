#include "../headers/SystemManager.h"
#include <string>
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

SystemManager::SystemManager()
{
}

void SystemManager::set_world(vector<string> world_cmd)
{
	westLong = convert_dms_to_dec(world_cmd[1]);
	eastLong = convert_dms_to_dec(world_cmd[2]);
	southLat = convert_dms_to_dec(world_cmd[3]);
	northLat = convert_dms_to_dec(world_cmd[4]);
}

double SystemManager::convert_dms_to_dec(string dms)
{
	if (dms.length() < 8)
	{
		dms = "0" + dms;
	}
	double deg = stod(dms.substr(0, 3));
	double min = stod(dms.substr(3, 2))/60;
	double sec = stod(dms.substr(5, 2))/3600;
	string dir = dms.substr(7, 1);
	double dec;

	if (dir == "W" || dir == "S")
	{
		 dec = (deg + min + sec) *-1;
	}
	else
	{
		dec = (deg + min + sec);
	}
	return dec; 
}