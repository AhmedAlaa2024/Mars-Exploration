#pragma once
#include "LinkedQueue.h"
#include "UI.h"
#include "Event.h"
#include "LinkedBAG.h"
#include "Mission.h"
#include "LinkedQueue.h"
#include "Rover.h"
#include "LinkedPriorityQueue.h"
#include "LinkedList.h"

class UI; //forward declaration //makes the compilers know that there exists a class called UI


class MarsStation
{
private:
	// Data Base
	LinkedBAG<Mission*> MISSIONS_DB;
	LinkedBAG<Rover*> ROVERS_DB;

	// Rovers
	LinkedBAG<Rover*> in_execution_rovers_;
	LinkedBAG<Rover*> check_up_rovers_;
	LinkedPriorityQueue<Rover*, double> available_rovers_emergency_;
	LinkedPriorityQueue<Rover*, double> available_rovers_mountainous_;
	LinkedPriorityQueue<Rover*, double> available_rovers_polar_;

	// Missions
	LinkedPriorityQueue<Mission*, int> waiting_emergency_missions_;
	LinkedList<Mission*> waiting_mountainous_missions_;
	LinkedQueue<Mission*> waiting_polar_missions_;
	LinkedList<Mission*> in_execution_missions_;
	LinkedList<Mission*> completed_missions_;


	// Events
	LinkedQueue<Event*> events_list_;

	// User Interface
	UI* my_ui;
	int CollectStatistics_File(int&, int&, int&, int&, int&, int&, int&, int&, int&, int&) const;


	//masc info
	int AutoP;
	int current_day_;

public:
	MarsStation();

	//for getting data
	SIM_MODE get_input_mode() const;
	void execute_mode(SIM_MODE);

	bool read_input_file();


	bool writeOutputFile() const;
	void CollectStatistics_Console();  // TODO like for file


	//Simulation
	void simulate_day();
	void assign_missions();
	void check_completed_missions();



};

