 #include "Cancellation.h"

Cancellation::Cancellation(int ed,int id, MarsStation* m_s):Event(ed,id, m_s)
{
	
}

void Cancellation::Execute()   //cancel a requested mountainous mission (if found and is waiting)
{
	M_S->increment_Cancelled_M();
	int count = M_S->get_waiting_mountainous_missions_().getItemCount();
	// loop on the list
	for (int i = 1; i <= count; i++)
	{
		Node<Mission*>* m = M_S->get_waiting_mountainous_missions_().getNodeAt(i);
		if (m->getItem()->getID() == get_ID() && m->getItem()->getMT() == MISSION_TYPE::MOUNTAINOUS)
		{
			m->getItem()->setMS(MISSION_STATUS::CANCELLED);
			//then cancel it
			M_S->get_waiting_mountainous_missions_().remove(i);   //function remove does not delete
		}

	}
	//I have a question ---> should I check if the id is not an id of a mountainous mission or not
	//I think i should ---> because if not there was no need to say only mountainous can be cancelled
}