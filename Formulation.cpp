#include "Formulation.h"

Formulation::Formulation(char typ,int ed, int id, double tloc, int mdur, int sig, MarsStation* m_s)
	:Event(ed,id, m_s){
	TYP = typ;
	TLOC = tloc;
	MDUR = mdur;
	SIG = sig;
}

void Formulation::Execute()   //creat the mission and put it in the appropriate list
{
	Mission* m = new Mission(get_ED(), MISSION_TYPE::UNDETERMINED, TLOC, MDUR, SIG, get_ID());

	//fill the data base list first
	M_S->get_mission_DB().add(m);

	if (TYP == 'E')
	{
		m->setMT(MISSION_TYPE::EMERGENCY);
		Pair<Mission*, int> pE(m, m->Weight());
		M_S->get_W_E_M().enqueue(pE);
	}

	else if (TYP == 'M')
	{
		m->setMT(MISSION_TYPE::MOUNTAINOUS);
		M_S->get_W_M_M().insert(m);
	}

	else
	{
		m->setMT(MISSION_TYPE::POLAR);
		M_S->get_W_P_M().enqueue(m);
	}

}
