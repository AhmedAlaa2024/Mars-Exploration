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
	LinkedBAG<Rover*> inExecutionRovers;
	LinkedBAG<Rover*> checkUpRovers;
	LinkedPriorityQueue<Rover*, int> avaliableRovers_emergency;
	LinkedPriorityQueue<Rover*, int> avaliableRovers_mountainous;
	LinkedPriorityQueue<Rover*, int> avaliableRovers_polar;

	// Missions
	LinkedPriorityQueue<Mission*, int> waitingEmergencyMissions;
	LinkedList<Mission*> waitingMountainousMissions;
	LinkedQueue<Mission*> waitingPolarMissions;
	LinkedList<Mission*> inExecutionMissions;
	LinkedList<Mission*> completedMissions;


	// Events
	LinkedQueue<Event*> Events_list_;
	
	// User Interface
	UI* my_ui;
	int CollectStatistics_File(int&, int&, int&, int&, int&, int&, int&, int&, int&, int&) const;
	
public:
	MarsStation();

	//for getting data
	SIM_MODE get_input_mode() const;
	void execute_mode(SIM_MODE);

	bool read_input_file();

	
	bool writeOutputFile() const;
	void CollectStatistics_Console();  // TODO like for file

	
};

