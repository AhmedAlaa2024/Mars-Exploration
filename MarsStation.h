#pragma once
#include "UI.h"

class UI; //forward declaration //makes the compilers know that there exists a class called UI


class MarsStation
{
	UI* my_ui;

public:
	MarsStation();
	
	SIM_MODE get_input_mode() const;
	
	void execute_mode(SIM_MODE);
};

