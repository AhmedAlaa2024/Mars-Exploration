#include "Formulation.h"

Formulation::Formulation(char typ, int ed, int id, double tloc, int mdur, int sig, MarsStation* m_s)
	:Event(ed, id, m_s) {
	TYP = typ;
	TLOC = tloc;
	MDUR = mdur;
	SIG = sig;
}

void Formulation::Execute()   // Create the mission and put it in the appropriate list
{
	M_S->increment_formulated_m(); // Increasing the number of formulated messions in the mars station objects

	Mission* m = new Mission(get_ED(), MISSION_TYPE::UNDETERMINED, TLOC, MDUR, SIG, get_ID()); // Create an object of mission type and constructe it using the provided data

	//fill the data base list first
	M_S->get_mission_db().add(m);

	if (TYP == 'E') // E -> Emergency
	{
		m->setMT(MISSION_TYPE::EMERGENCY); // Setting the type of missions to Emergency Type
		Pair<Mission*, int> pE(m, m->Weight()); // Create a pair of mission and its signeficant
		M_S->get_w_e_m().enqueue(pE); // Enqueue the new mission in the Priority Queue of Waiting Emergency Missions
	}

	else if (TYP == 'M') // M -> Mountainous
	{
		m->setMT(MISSION_TYPE::MOUNTAINOUS); // Setting the type of missions to Mountainous Type
		M_S->get_w_m_m().insertEnd(m); // Insert the new mission in the LinkedList of Waiting Mountainous missions
	}

	else
	{
		m->setMT(MISSION_TYPE::POLAR); // Setting the type of missions to Polar Type
		M_S->get_w_p_m().enqueue(m);  // Enqueue the new mission in the Queue of waiting polar missions
	}

}
