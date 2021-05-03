/////////////////////////////// Written By: Ahmed Alaa ///////////////////////////////
#pragma once
#include "Defs.h"

class Mission
{
private:
	int FD; // Formulation Day
	MISSION_TYPE MT; // Mission Type
	MISSION_STATUS MS; // Mission Status
	int TL; // Target Location
	int MD; // Mission Duration
	bool asigned;
	int WD; // Waiting Durations
	int CD; // Complete Date
	int assignedRoverId;
public:
	// Default Constructor
	Mission(int fd = 0, MISSION_TYPE mt = MISSION_TYPE::UNDETERMINED, int tl = 0, int md = 0);

	// Getters
	int getFD() const;
	MISSION_TYPE getMT() const;
	MISSION_STATUS getMS() const;
	int getTL() const;
	int getMD() const;
	bool IsAssigned() const;
	int getWD() const;
	int getCD() const;
	

	
	int get_rover_id() const;

	bool get_is_promoted()const;
	int get_priority() const;
	bool isCompleted(int currentDay) const;
	int getRoverId() const;
	bool Assign(int Rover_id);
	// Setters
	bool setFD(int fd);
	bool setMT(MISSION_TYPE mt);
	bool setTL(int tl);
	bool setMD(int md);
	bool setWD(int wd);
	//bool setSssignedRoverId(int id);

	void set_priority(int p=0);

	bool setSssignedRoverId(int id);

	// Specific Member Functions
	bool WaitAnotherDay();
	bool Complete(int speed);
	bool Promote();

};