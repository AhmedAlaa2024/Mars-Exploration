/////////////////////////////// Written By: Ahmed Alaa ///////////////////////////////
#include "Mission.h"


Mission::Mission(int fd, MISSION_TYPE mt, int tl, int md, int sig , int id ): FD(fd), MT(mt), MS(MISSION_STATUS::WAITING),
TL(tl), MD(md), asigned(false), WD(0), CD(0)
{
	is_promoted = false;
	ID = id;
	SIG = sig;
}


int Mission::getFD() const
{
	return FD;
}

MISSION_TYPE Mission::getMT() const
{
	return MT;
}

MISSION_STATUS Mission::getMS() const
{
	return MS;
}

int Mission::getTL() const
{
	return TL;
}

int Mission::getMD() const
{
	return MD;
}

int Mission::getWD() const
{
	return WD;
}

int Mission::getCD() const
{
	return CD;
}

int Mission::getID() const
{
	return ID;
}

bool Mission::isCompleted(int currentDay) const
{
	if (CD == currentDay)
		return true;
	return false;
}

Rover* Mission::getRover() const
{
	return assignedRover;
}

void Mission::Assign(Rover* r)
{
	assignedRover = r;
	asigned = true;
}

int Mission::get_priority() const
{
	return priority_;
}

bool Mission::get_is_promoted() const
{
	return is_promoted;
}

bool Mission::setFD(int fd)
{
	if (FD != 0) // Means that it already has its own FD
		return false;

	FD = fd;
	return true;
}

bool Mission::setMT(MISSION_TYPE mt)
{
	if (MT != MISSION_TYPE::UNDETERMINED) // Means that it has already its own value
		return false;

	MT = mt;
	return true;
}

bool Mission::setTL(int tl)
{
	if (TL != 0) // Means that it already has its own value
		return false;

	TL = tl;
	return true;
}

bool Mission::setMD(int md)
{
	if (MD != 0) // Means that it already has its own value
		return false;

	MD = md;
	return true;
}

bool Mission::IsAssigned() const
{
	return asigned;
}

bool Mission::setWD(int wd)
{
	if (WD != 0) // Means that it already has its own value
		return false;

	MD = wd;
	return true;
}

void Mission::set_priority(int prio)
{
	priority_ = prio;
}



bool Mission::setMS(MISSION_STATUS ms)
{
	MS = ms;
	return true;
}


bool Mission::WaitAnotherDay()
{
	if (CD != 0) // Means that the mission is already completed, So no need to wait another day!
		return false;
	WD++;
	return true;
}

bool Mission::Complete(int speed)
{
	if (CD != 0) // Means that the mission is already completed, So no need to be completed!
		return false;

	MS = MISSION_STATUS::COMPLETED;
	CD = FD + (TL / speed) * 2 + MD + WD;
	return true;
}

bool Mission::Promote()
{
	if (MT != MISSION_TYPE::MOUNTAINOUS) // The Mountainous missions only are allowed to be promoted!
		return false;

	is_promoted = true;
	MT = MISSION_TYPE::EMERGENCY;


	return true;

}

int Mission::Weight()
{
	//return the value of the weighted equation

	return (40 * SIG + 15 * TL + 10 * MD + 5 * FD);
}