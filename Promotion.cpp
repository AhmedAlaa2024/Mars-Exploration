#include "Promotion.h"


Promotion::Promotion(int ed, int id, MarsStation* m_s) :Event(ed, id, m_s)
{ }


void Promotion::Execute()
{
	for (int i = 1; i <= M_S->get_w_m_m().getItemCount(); i++) // Looping on all the waiting mountainous missions (LinkedList)
	{
		Mission* m = M_S->get_w_m_m().getEntry(i); // Holding Each Misson every iteration
		if (m->getID() == get_ID()) // ID Match
		{
			// Update its data
			m->Promote();

			// Move it to the emergency list
			M_S->get_w_m_m().remove(i);
			Pair<Mission*, int> pM(m, m->get_priority());
			M_S->get_w_e_m().enqueue(pM);
			break;
		}
	}
}