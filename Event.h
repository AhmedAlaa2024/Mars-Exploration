#pragma once


#include "MarsStation.h"
class MarsStation;    //forward class decleration


class Event
{
	int ED; // execution day
	int ID; // Mission's id
protected:
	MarsStation* M_S;  // for the class to do its job
public:
	Event(int ed, int id, MarsStation* m_s);
	virtual void Execute() = 0;

	int get_ED() const;
	int get_ID() const;

	virtual ~Event() {}
};
