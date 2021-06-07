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
class Event;

class MarsStation
{
private:
	// Data Base
	LinkedBAG<Mission*> MISSIONS_DB;
	LinkedBAG<Rover*> ROVERS_DB;

	// Rovers
	LinkedList<Rover*> in_execution_rovers_;
	LinkedList<Rover*> check_up_rovers_;
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
	int CollectStatistics_File(int&, int&, int&, int&, int&, int&, int&, int&, int&, int&);

	//masc info
	int AutoP;
	int Cancelled_M;
	int Formulated_M;

	int current_day_;

	int MRCount;
	int PRCount;
	int ERCount;
	int AutoPCount;

	void check_auto_promotion();
	void check_checkup_list();
	//utility functions
	void move_to_in_ex_list(Mission* miss);

	void MoveToAvailable(Rover*);
	void MoveToAvailable(int);
	void MoveToCheckUp(Rover*);
	void SortCompletedList();
public:
	MarsStation();

	//for getting data
	SIM_MODE get_input_mode() const;
	void execute_mode(SIM_MODE);

	bool read_input_file();

	int get_current_day();


	bool writeOutputFile();
	void CollectStatistics_Console();  // TODO like for file



	//Simulation
	void simulate_day();
	void assign_missions();
	void check_completed_missions();


	//getters --> Don't create new functions without making sure it's not here

	LinkedBAG<Mission*>& get_mission_DB();
	LinkedPriorityQueue<Mission*, int>& get_W_E_M();
	LinkedQueue<Mission*>& get_W_P_M();
	LinkedList<Mission*>& get_W_M_M();
	LinkedList<Mission*>& get_in_execution_missions();
	LinkedList<Rover*>& get_check_up_rovers_();
	LinkedList<Mission*>& get_completed_missions_();
	LinkedPriorityQueue<Rover*, double>& get_available_rovers_emergency_();
	LinkedPriorityQueue<Rover*, double>& get_available_rovers_mountainous_();
	LinkedPriorityQueue<Rover*, double>& get_available_rovers_polar_();

	bool check_Last_Day();
	bool check_valid_data();
	bool check_polar_R_M();
	void increment_Cancelled_M();
	void increment_Formulated_M();


	//Destructor
	~MarsStation();

};




