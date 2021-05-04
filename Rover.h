/////////////////////////////// Written By: Ahmed Alaa ///////////////////////////////
#pragma once
#include "Mission.h"
#include "Defs.h"

class Rover
{
private:
	ROVER_TYPE RT;
	ROVER_STATUS RS;
	int checkUPDuration;
	int speed; // Don't forget that the day in Mars = 25 hours
	bool assigned;
	int MaxMissions;
	int completedMissions;
	Mission* mission;
	int ID;

public:
	// Default Arguments Constructor
	Rover(ROVER_TYPE rt = ROVER_TYPE::UNDETERMINED, int checkupDur = 0, int sp = 0, int max = 0, int id = -1);

	// Getters
	ROVER_STATUS getRS() const;
	ROVER_TYPE getRT() const;
	int getCheckUPDuration() const;
	int getSpeed() const;
	bool Assigned() const;
	int getMaxMissions() const;
	int getNumCompletedMissions() const;
	Mission* getAssignedMission() const;
	int getID() const;


	// Setters
	bool setRT(ROVER_TYPE rt);
	void SetRS(ROVER_STATUS rs);
	bool setCheckUPDuration(int checkupDur);
	void setSpeed(int sp);
	bool setMaxMissions(int max);
	bool setID(int id);


	void incrementCompletedMissions();

	// Specific Member Functions
	void AssignTo(Mission* m, int currentDay);
	
	bool CheckUP(int currentDay);

	
};