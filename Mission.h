#pragma once
#include "Defs.h"

class Rover;

class Mission
{
private:
	int SIG;  //Mission Significance
	int FD; // Formulation Day
	MISSION_TYPE MT; // Mission Type
	MISSION_STATUS MS; // Mission Status
	int TL; // Target Location
	int MD; // Mission Duration
	bool asigned;
	int WD; // Waiting Durations
	int CD; // Complete Date
	int ED; // Execution days

	Rover* assignedRover; // The rover assigned to the current mission
	int priority_;
	bool is_promoted; // Like a flag to incicate if the mission is pure emergency (false) or promoted Mountainous (true)

	int ID;

public:
	// Default Constructor
	Mission(int fd = 0, MISSION_TYPE mt = MISSION_TYPE::UNDETERMINED, int tl = -1, int md = 0, int sig = 0, int id = 0);


	// Getters
	int getFD() const; // To get Formulation Day
	MISSION_TYPE getMT() const; // To get the mission type
	MISSION_STATUS getMS() const;
	int getTL() const;
	int getMD() const;
	bool IsAssigned() const;
	int getWD() const;
	int getCD() const;
	int getED() const;
	bool isCompleted(int currentDay) const;
	Rover* getRover() const;
	int getID() const;
	int get_priority()const;
	bool get_is_promoted() const;


	// Setters
	bool setFD(int fd);
	bool setMT(MISSION_TYPE mt);
	bool setTL(int tl);
	bool setMD(int md);
	bool setWD(int wd);
	void setED(int ed);
	void set_priority(int prio);
	bool setMS(MISSION_STATUS ms);


	// Specific Member Functions
	void Assign(Rover* r, double r_speed, int currentDay);
	void WaitAnotherDay();
	bool Promote();
	int Weight();
};
