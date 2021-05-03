#include "Event.h"

Event::Event(int ed,int id, MarsStation* m_s)
{
	M_S = m_s;
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
