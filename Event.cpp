#include "Event.h"

Event::Event(int ed,int id)
{
	ED = ed;
	ID = id;
}

int Event::get_ED() const
{
    return ED;
}

int Event::get_ID() const
{
	return ID;
}
