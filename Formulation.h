#pragma once
#include "Event.h"


class Formulation :
	public Event
{
	char TYP; // M OR P OR E // mission type

	double TLOC; //mission’s target location (in kilometers from the base station).  
	int MDUR; //number of days needed to fulfill the mission requirements at target location
	int SIG; // mission’s significance.

public:
	Formulation(char typ, int ed, int id, double tloc, int mdur, int sig, MarsStation* m_s);
	virtual void Execute();


};

