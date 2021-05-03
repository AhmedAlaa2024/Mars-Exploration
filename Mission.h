/////////////////////////////// Written By: Ahmed Alaa ///////////////////////////////
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

	Rover* assignedRover;
	int priority_;
	bool is_promoted;

	int ID;

public:
	// Default Constructor
	Mission(int fd = 0, MISSION_TYPE mt = MISSION_TYPE::UNDETERMINED, int tl = 0, int md = 0, int sig = 0, int id = 0);

	
	// Getters
	int getFD() const;
	MISSION_TYPE getMT() const;
	MISSION_STATUS getMS() const;
	int getTL() const;
	int getMD() const;
	bool IsAssigned() const;
	int getWD() const;
	int getCD() const;
	bool isCompleted(int currentDay) const;

	Rover* getRover() const;


	
	int getID() const;

	
	void Assign(Rover* r);
	int get_priority()const;
	bool get_is_promoted() const;
	// Setters
	bool setFD(int fd);
	bool setMT(MISSION_TYPE mt);
	bool setTL(int tl);
	bool setMD(int md);
	bool setWD(int wd);

	void set_priority(int prio);

	bool setMS(MISSION_STATUS ms);   //modifiable


	// Specific Member Functions
	bool WaitAnotherDay();
	bool Complete(int speed);
	bool Promote();
	int Weight();

};
