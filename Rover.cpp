/////////////////////////////// Written By: Ahmed Alaa ///////////////////////////////
#include "Rover.h"

Rover::Rover(ROVER_TYPE rt, int checkupDur, double sp, int max, int id) : RS(ROVER_STATUS::WAITING), RT(rt),
checkUPDuration(checkupDur), speed(sp), assigned(false), MaxMissions(max),
completedMissions(0), mission(nullptr), ID(id)
{
	checkupENDDay = 0;
}

ROVER_STATUS Rover::getRS() const
{
	return RS;
}

ROVER_TYPE Rover::getRT() const
{
	return RT;
}

int Rover::getCheckUPDuration() const
{
	return checkUPDuration;
}

double Rover::getSpeed() const
{
	return speed;
}

bool Rover::Assigned() const
{
	return assigned;
}

int Rover::getMaxMissions() const
{
	return MaxMissions;
}

int Rover::getNumCompletedMissions() const
{
	return completedMissions;
}

Mission* Rover::getAssignedMission() const
{
	return mission;
}

int Rover::getID() const
{
	return ID;
}

int Rover::getCheckupEND() const
{
	return checkupENDDay;
}

bool Rover::setRT(ROVER_TYPE rt)
{
	if (rt != ROVER_TYPE::UNDETERMINED) // Means that it already has its own value
		return false;

	RT = rt;
	return true;
}

void Rover::SetRS(ROVER_STATUS rs)
{
	RS = rs;
}

bool Rover::setCheckUPDuration(int checkupDur)
{
	if (checkUPDuration != 0) // Means that it already has its own value
		return false;

	checkUPDuration = checkupDur;
	return true;
}

void Rover::setSpeed(double sp)
{
	speed = sp;

}

bool Rover::setMaxMissions(int max)
{
	if (MaxMissions != 0) // Means that it already has its own value
		return false;

	MaxMissions = max;
	return true;
}

bool Rover::setID(int id)
{
	if (ID != -1 && id == -1)
		return false;

	ID = id;
	return true;
}

void Rover::incrementCompletedMissions()
{
	completedMissions++;
}

void Rover::AssignTo(Mission* m)
{
	mission = m;
	assigned = true; // doaa temporarly---> i will delete it
	RS = ROVER_STATUS::IN_EXECUTION;  //doaa

}


bool Rover::CheckUP(int currentDay)
{
	if (!mission->isCompleted(currentDay)) // To make sure that the rover has been finished the assigned mission before check-up
		return false;
	checkupENDDay = currentDay + checkUPDuration; // TO BE REVISED IF -1
	completedMissions = 0;
	mission = nullptr;
	RS = ROVER_STATUS::CHECKUP;
	assigned = false; // doaa temporarly---> i will delete it
	return true;
}