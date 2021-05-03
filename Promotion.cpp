#include "Promotion.h"

Promotion::Promotion(int ed, int id, MarsStation* m_s) :Event(ed, id, m_s)
{
}

void Promotion::Execute()
{
	int count = M_S->get_W_M_M().getItemCount();
	for (int i = 1; i <= count; i++)
	{
		Node<Mission*>* m = M_S->get_W_M_M().getNodeAt(i);
		if (m->getItem()->getID() == get_ID() && m->getItem()->getMT() == MISSION_TYPE::MOUNTAINOUS)
		{
			//then update its data
			m->getItem()->setMT(MISSION_TYPE::EMERGENCY);
			
			//then move it to the emergency list
			M_S->get_W_M_M().remove(i);
			Pair<Mission*, int> pM(m->getItem(), m->getItem()->Weight());
			M_S->get_W_E_M().enqueue(pM);
		}
	}

}
