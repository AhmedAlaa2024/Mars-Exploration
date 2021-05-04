#include "Promotion.h"

Promotion::Promotion(int ed, int id, MarsStation* m_s) :Event(ed, id, m_s)
{
}

void Promotion::Execute()
{
	int count = M_S->get_W_M_M().getItemCount();
	for (int i = 1; i <= count; i++)
	{
		Mission* m = M_S->get_W_M_M().getEntry(i);
		if (m->getID() == get_ID() && m->getMT() == MISSION_TYPE::MOUNTAINOUS)  //no need to check if it is M_M or not because it is inside the W_M_M
		{                                                                       //I think also there is no need to  check inside the promote function ??
			//then update its data
			m->Promote();
			
			//then move it to the emergency list
			M_S->get_W_M_M().remove(i);
			Pair<Mission*, int> pM(m, m->get_priority());
			M_S->get_W_E_M().enqueue(pM);
		}
	}

}
