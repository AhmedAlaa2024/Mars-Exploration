#pragma once
#include "Event.h"


class Cancellation :
    public Event
{
	
	
public:
	Cancellation(int ed, int id);
	virtual void Execute();

};

