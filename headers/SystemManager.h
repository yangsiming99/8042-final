#ifndef SYSTEMANAGER_H
#define SYSTEMANAGER_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

class SystemManager
{
public:
	SystemManager();
	void set_world(vector<string> world_cmd);

private:
	double westLong;
	double eastLong;
	double southLat;
	double northLat;
	double convert_dms_to_dec(string dms);
};

#endif // !SYSTEMANAGER_H