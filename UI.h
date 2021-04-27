#pragma once
#include <iostream>
using namespace std;
#include "Defs.h"
#include "MarsStation.h"
class MarsStation;
class UI
{

	MarsStation* p_station;



public:
	UI(MarsStation* p_s);
	SIM_MODE get_input_mode();
	bool read_input_file();



};

