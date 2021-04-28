#pragma once
#include "Event.h"


class Formulation :
    public Event
{
	char TYP; // M OR P OR E // mission type
	
	double TLOC; //missionís target location (in kilometers from the base station).  
	int MDUR; //number of days needed to fulfill the mission requirements at target location
	int SIG; // missionís significance.
	
public:
	Formulation(char typ, int ed, int id, double tloc,int mdur, int sig );
	virtual void Execute();

	
};

