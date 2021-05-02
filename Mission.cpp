/////////////////////////////// Written By: Ahmed Alaa ///////////////////////////////
#include "Mission.h"

Mission::Mission(int fd, MISSION_TYPE mt, int tl, int md) : FD(fd), MT(mt), MS(MISSION_STATUS::WAITING), TL(tl), MD(md), asigned(false), WD(0), CD(0)
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

bool Mission::isCompleted(int currentDay) const
{
	if (CD > currentDay)
		return false;
	return true;
}

int Mission::getRoverId() const
{
	return assignedRoverId;
}

bool Mission::setFD(int fd)
{
	if (FD != 0) // Means that it already has its own FD
		return false;

	FD = fd;
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

bool Mission::setSssignedRoverId(int id)
{
	if (asigned)
		return false;

	assignedRoverId = id;
	asigned = true;
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
	if (CD != 0) // Means that the mission is already completed, So no need to be promoted!
		return false;

	if (MT != MISSION_TYPE::MOUNTAINOUS) // The Mountainous missions only are allowed to be promoted!
		return false;

	MT = MISSION_TYPE::EMERGENCY;
	return true;
}
