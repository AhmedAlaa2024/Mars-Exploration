#include "Cancellation.h"

Cancellation::Cancellation(int ed, int id, MarsStation* m_s) :Event(ed, id, m_s)
{ }


void Cancellation::Execute()   // Cancel a requested mountainous mission (if found and is waiting)
{
	// Loop on the list
	for (int i = 1; i <= M_S->get_W_M_M().getItemCount(); i++)
	{
		Mission* m = M_S->get_W_M_M().getEntry(i);
		if (m->getID() == get_ID() && m->getMT() == MISSION_TYPE::MOUNTAINOUS)
		{
			m->setMS(MISSION_STATUS::CANCELLED);
			// Then cancel it
			M_S->get_W_M_M().remove(i);   //function remove does not delete
			M_S->increment_Cancelled_M();
		}
	}
}