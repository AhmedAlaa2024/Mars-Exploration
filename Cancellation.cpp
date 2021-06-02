#include "Cancellation.h"

Cancellation::Cancellation(int ed, int id, MarsStation* m_s) :Event(ed, id, m_s)
{

}

void Cancellation::Execute()   //cancel a requested mountainous mission (if found and is waiting)
{

	//int count = M_S->get_W_M_M().getItemCount();
	// loop on the list
	for (int i = 1; i <= M_S->get_W_M_M().getItemCount(); i++)
	{
		Mission* m = M_S->get_W_M_M().getEntry(i);
		if (m->getID() == get_ID() && m->getMT() == MISSION_TYPE::MOUNTAINOUS)
		{
			m->setMS(MISSION_STATUS::CANCELLED);
			//then cancel it
			M_S->get_W_M_M().remove(i);   //function remove does not delete
			M_S->increment_Cancelled_M();
		}

	}
	//I have a question ---> should I check if the id is not an id of a mountainous mission or not
	//I think i should ---> because if not there was no need to say only mountainous can be cancelled
}