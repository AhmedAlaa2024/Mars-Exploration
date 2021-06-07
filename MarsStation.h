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
	int collect_statistics_file(int&, string&);

	//misc info
	int auto_p_;
	int cancelled_m_;
	int formulated_m_;

	int current_day_;

	int mr_count_;
	int pr_count_;
	int er_count_;
	int auto_p_count_;

	void check_auto_promotion();
	void check_checkup_list();
	//utility functions
	void move_to_in_ex_list(Mission* miss);

	void move_to_available(Rover*);
	void move_to_available(int);
	void move_to_checkup(Rover*);
	void insert_by_ed(int start, Mission* MPtr);
public:
	MarsStation();

	//for getting data
	SIM_MODE get_input_mode() const;
	void execute_mode(SIM_MODE);

	bool read_input_file();

	int get_current_day();


	bool write_output_file();



	//Simulation
	void simulate_day();
	void assign_missions();
	void check_completed_missions();


	
	LinkedBAG<Mission*>& get_mission_db();
	LinkedPriorityQueue<Mission*, int>& get_w_e_m();
	LinkedQueue<Mission*>& get_w_p_m();
	LinkedList<Mission*>& get_w_m_m();
	LinkedList<Mission*>& get_in_execution_missions();
	LinkedList<Rover*>& get_check_up_rovers();
	LinkedList<Mission*>& get_completed_missions_();
	LinkedPriorityQueue<Rover*, double>& get_available_rovers_emergency_();
	LinkedPriorityQueue<Rover*, double>& get_available_rovers_mountainous_();
	LinkedPriorityQueue<Rover*, double>& get_available_rovers_polar_();

	bool check_last_day();
	bool check_valid_data();
	bool check_polar_r_m();
	void increment_cancelled_m();
	void increment_formulated_m();


	//Destructor
	~MarsStation();

};




