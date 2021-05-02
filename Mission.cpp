/////////////////////////////// Written By: Ahmed Alaa ///////////////////////////////
#include "Mission.h"

Mission::Mission(int fd, MISSION_TYPE mt, int tl, int md) : FD(fd), MT(mt), MS(MISSION_STATUS::WAITING),
TL(tl), MD(md), asigned(false), WD(0), CD(0), is_promoted(false), priority_(0)
{
	// Nothing To do
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

bool Mission::isCompleted() const
{
	if (CD == 0)
		return false;
	return true;
}

int Mission::get_rover_id() const
{
	return assigned_rover_id;
}

bool Mission::get_is_promoted() const
{
	return is_promoted;
}

int Mission::get_priority() const
{
	return priority_;
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

bool Mission::Assign(int Rover_id)
{
	if (asigned)
		return false;

	assigned_rover_id = Rover_id;

	MS = MISSION_STATUS::IN_EXECUTION;
	asigned = true;
	return true;
}

bool Mission::setWD(int wd)
{
	if (WD != 0) // Means that it already has its own value
		return false;

	MD = wd;
	return true;
}

void Mission::set_priority(int p)
{
	priority_ = p;

}

void Mission::WaitAnotherDay()
{
	
	WD++;
	
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
	if (CD != 0) // Means that the mission is already completed, So no need to be promoted!
		return false;

	if (MT != MISSION_TYPE::MOUNTAINOUS) // The Mountainous missions only are allowed to be promoted!
		return false;

	is_promoted = true;
	//MT = MISSION_TYPE::EMERGENCY; //TODO: ASK about this
	return true;
}
