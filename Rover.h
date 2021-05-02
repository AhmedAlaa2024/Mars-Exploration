/////////////////////////////// Written By: Ahmed Alaa ///////////////////////////////
#include "Mission.h"

#ifndef ROVER_H_
#define ROVER_H_

enum class ROVER_TYPE {
	UNDETERMINED = 0,
	EMERGENCY = 1,
	MOUNTAINOUS = 2,
	POLAR = 3
};

enum class ROVER_STATUS {
	WAITING = 0,
	IN_EXECUTION = 1,
	CHECKUP = 2
};

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

public:
	// Default Arguments Constructor
	Rover(ROVER_TYPE rt = ROVER_TYPE::UNDETERMINED, int checkupDur = 0, int sp = 0, int max = 0);

	// Getters
	ROVER_STATUS getRS() const;
	ROVER_TYPE getRT() const;
	int getCheckUPDuration() const;
	int getSpeed() const;
	bool Assigned() const;
	int getMaxMissions() const;
	int getNumCompletedMissions() const;
	Mission* getAssignedMission() const;

	// Setters
	bool setRT(ROVER_TYPE rt);
	bool setCheckUPDuration(int checkupDur);
	bool setSpeed(int sp);
	bool setMaxMissions(int max);

	// Specific Member Functions
	bool Assign(Mission* m, int currentDay);
	bool CheckUP(int currentDay);

};

#endif // !ROVER_H_