#pragma once
#include "Event.h"


class Promotion :
    public Event
{

public:
	Promotion(int ed, int id);
	virtual void Execute();

	
};

