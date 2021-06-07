#include "Cancellation.h"

Cancellation::Cancellation(int ed, int id, MarsStation* m_s) :Event(ed, id, m_s)
{ }


void Cancellation::Execute()   // Cancel a requested mountainous mission (if found and is waiting)
{

	
	// loop on the list
	for (int i = 1; i <= M_S->get_w_m_m().getItemCount(); i++)
	{
		Mission* m = M_S->get_w_m_m().getEntry(i);
		if (m->getID() == get_ID() && m->getMT() == MISSION_TYPE::MOUNTAINOUS)
		{
			m->setMS(MISSION_STATUS::CANCELLED);
			//then cancel it
			M_S->get_w_m_m().remove(i);   //function remove does not delete
			M_S->increment_cancelled_m();
			return;
		}
	}
	
}