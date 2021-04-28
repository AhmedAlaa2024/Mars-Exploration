#pragma once
#include "LinkedQueue.h"
#include "UI.h"
#include "Event.h"
class UI; //forward declaration //makes the compilers know that there exists a class called UI


class MarsStation
{
	UI* my_ui;
	LinkedQueue<Event*> Events_list_;

	
public:
	MarsStation();

	//for getting data
	SIM_MODE get_input_mode() const;
	void execute_mode(SIM_MODE);

	bool read_input_file();

	

	

	
};

