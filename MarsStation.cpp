#include "MarsStation.h"
#include <iostream>
using namespace std;
#include <sstream>
#include <iomanip>
#include <fstream>
#include <string>
#include "Defs.h"
#include "Formulation.h"
#include "Promotion.h"
#include "Cancellation.h"

MarsStation::MarsStation() :AutoP(0), current_day_(0), PRCount(0), ERCount(0), MRCount(0), AutoPCount(0)
{
	Cancelled_M = 0;
	Formulated_M = 0;

	read_input_file();
	MarsStation* it = this;
	my_ui = new UI(it);


}


SIM_MODE MarsStation::get_input_mode() const
{
	return my_ui->get_input_mode();
}


void MarsStation::execute_mode(SIM_MODE mode)
{
	if (mode == SIM_MODE::INTERACTIVE)
	{
		my_ui->InteractivePrinting();
	}
	else if (mode == SIM_MODE::STEP_BY_STEP)
	{
		my_ui->StepByStepPrinting();

	}
	else
	{
		my_ui->SilentPrinting();

	}
}


LinkedBAG<Mission*>& MarsStation::get_mission_DB()
{
	return MISSIONS_DB;
}


LinkedPriorityQueue<Mission*, int>& MarsStation::get_W_E_M() // Member Function get the waiting emergency missions
{ 
	return waiting_emergency_missions_;
}


LinkedList<Mission*>& MarsStation::get_W_M_M()
{
	return waiting_mountainous_missions_;
}


LinkedQueue<Mission*>& MarsStation::get_W_P_M()
{
	return waiting_polar_missions_;
}


LinkedList<Mission*>& MarsStation::get_in_execution_missions()
{
	return in_execution_missions_;
}


LinkedList<Rover*>& MarsStation::get_check_up_rovers_()
{
	return check_up_rovers_;
}


LinkedList<Mission*>& MarsStation::get_completed_missions_()
{
	return completed_missions_;
}


LinkedPriorityQueue<Rover*, double>& MarsStation::get_available_rovers_emergency_()
{
	return available_rovers_emergency_;
}


LinkedPriorityQueue<Rover*, double>& MarsStation::get_available_rovers_mountainous_()
{
	return available_rovers_mountainous_;
}


LinkedPriorityQueue<Rover*, double>& MarsStation::get_available_rovers_polar_()
{
	return available_rovers_polar_;
}


int MarsStation::get_current_day()
{
	return current_day_;
}


bool MarsStation::read_input_file()
{
	//TODO:: After the DS is Written
	ifstream my_file("input.txt");

	if (!my_file) {
		return false;
	}

	my_file >> MRCount >> PRCount >> ERCount;

	int N, CM, CP, CE; // no. of missions before checkup and the checkup durations
	my_file >> N >> CM >> CP >> CE;

	double SM, SP, SE; //speed of each type

	int ids = 0;

	for (int i = 0; i < MRCount; ++i) // Create Mountainous Rovers
	{
		my_file >> SM;

		Rover* r = new Rover(ROVER_TYPE::MOUNTAINOUS, CM, SM, N, ++ids);
		Pair<Rover*, double> p(r, r->getSpeed());
		available_rovers_mountainous_.enqueue(p);
		ROVERS_DB.add(r);
	}
	
	for (int i = 0; i < PRCount; ++i) // Create Polar Rovers
	{
		my_file >> SP;

		Rover* r = new Rover(ROVER_TYPE::POLAR, CP, SP, N, ++ids);
		Pair<Rover*, double> p(r, r->getSpeed());
		available_rovers_polar_.enqueue(p);
		ROVERS_DB.add(r);
	}

	for (int i = 0; i < ERCount; ++i) // Create Emergency Rovers
	{
		my_file >> SE;

		Rover* r = new Rover(ROVER_TYPE::EMERGENCY, CE, SE, N, ++ids);
		Pair<Rover*, double> p(r, r->getSpeed());
		available_rovers_emergency_.enqueue(p);
		ROVERS_DB.add(r);

	}

	int AutoP;
	my_file >> AutoP;
	this->AutoP = AutoP;

	int Events_no;
	my_file >> Events_no;

	for (int i = 0; i < Events_no; ++i)
	{
		char c;
		my_file >> c;
		if (c == 'F') //formulation event
		{
			char TYP;
			int ED;
			int ID;
			double TLOC;
			int MDUR;
			int SIG;

			my_file >> TYP >> ED >> ID >> TLOC >> MDUR >> SIG;

			Event* eve = new Formulation(TYP, ED, ID, TLOC, MDUR, SIG, this);
			events_list_.enqueue(eve);
		}
		else if (c == 'X') //cancellation Event
		{
			int ED;
			int ID;
			my_file >> ED >> ID;
			Event* eve = new Cancellation(ED, ID, this);
			events_list_.enqueue(eve);


		}
		else if (c == 'P')
		{
			int ED;
			int ID;
			my_file >> ED >> ID;
			Event* eve = new Promotion(ED, ID, this);
			events_list_.enqueue(eve);

		}
	}

	my_file.close();
	return true;
}


bool MarsStation::write_output_file()
{
	int Missions = completed_missions_.getItemCount();
	string Text = "";
	ofstream outFile("output.txt");
	if (!(outFile.is_open()))return false;
	if (!Missions)
		Text = "THERE ARE NO COMPLETED MISSIONS!!!!\n";
	else
		collect_statistics_file(Missions, Text);
	outFile << Text;
	outFile.close();
	if (outFile.is_open())return false;
	return true;
}


int MarsStation::collect_statistics_file(int& Missions, string& str)
{
	Mission* Ptr = nullptr;
	stringstream s;
	int TotalPrCount = 0;
	int Auto = 0;
	int WD = 0;
	int ED = 0;
	int CurrWD = 0, CurrED = 0;
	s << "CD\tID\tFD\tWD\tED\n";
	int MM = 0, PM = 0, EM = 0, Rovers = 0;
	float AvgW = 0, AvgEx = 0;
	MISSION_TYPE TYP;
	for (int i = 1; i <= Missions; i++)
	{
		Ptr = completed_missions_.getEntry(i);
		CurrWD = Ptr->getWD();
		CurrED = Ptr->getED();
		s << Ptr->getCD() << '\t' << Ptr->getID() << '\t' << Ptr->getFD() << '\t' << CurrWD << '\t' << CurrED << '\n';
		TYP = Ptr->getMT();
		WD += CurrWD;
		ED += CurrED;
		switch (TYP)
		{
		case MISSION_TYPE::MOUNTAINOUS:
			MM++;
			break;
		case MISSION_TYPE::POLAR:
			PM++;
			break;
		case MISSION_TYPE::EMERGENCY:
			if (Ptr->get_is_promoted())
				TotalPrCount++;
			EM++;
			break;
		}
	}

	Rovers = MRCount + PRCount + ERCount;
	if (Missions)
	{
		AvgW = (float)WD / Missions;
		AvgEx = (float)ED / Missions;
	}
	if (MM)
		Auto = ((double)AutoPCount / (MM + TotalPrCount)) * 100;

	if (!waiting_polar_missions_.isEmpty())
	{
		s << "Completed missions: " << to_string(Missions) << " [M: " << to_string(MM);
		s << ",P: " << to_string(PM);
		s << ",E: " << to_string(EM) << "]\n";
		s << "Uncompleted missions:  [P: " << to_string(waiting_polar_missions_.get_itemCount()) << "]\n";
	}
	else
	{
		s << "Missions: " << to_string(Missions) << " [M: " << to_string(MM);
		s << ",P: " << to_string(PM);
		s << ",E: " << to_string(EM) << "]\n";
	}
	s << "Rovers: " << to_string(Rovers) << " [M: " << to_string(MRCount) << ",P: " << to_string(PRCount) << ",E: " << to_string(ERCount) << "]\n";
	s << fixed << setprecision(2);
	s << "Avg Wait = " << AvgW << ", " << "Avg Exec = " << AvgEx << '\n';
	if (MM)
		s << "Auto-promoted: " << to_string(Auto) << "%\n";
	else
		s << "There are no Mountainious missions.\n";
	str = s.str();
	return 0;
}


bool MarsStation::check_Last_Day()
{
	// First of all we have to check on both the event list and the the completed list
	// if the no of missoins in the completed list == # formulated missions - # cancelled missions
	// && the event list is empty 

	// Then no simulate_day() any more 


	// Now, we have to check if after all missions are completed and there sill exists polar missions with no rovers
	// So we have to force days to stop
	if (check_polar_R_M())
	{
		return (completed_missions_.getItemCount() == Formulated_M - Cancelled_M) && (events_list_.isEmpty());
	}

	else
	{
		// hint : unfor. it will not work if there is a polar rover with speed 0 
		//there is a sol in my mind but will damage class responsibility
		int count = Formulated_M - Cancelled_M - (waiting_polar_missions_.get_itemCount());
		return(completed_missions_.getItemCount() == count && (events_list_.isEmpty()));  //why ??
	}
}


bool MarsStation::check_valid_data() // It Will be checked before simulation begins
{
	// In case no of rovers is 0 and there are missions     
	// with no cancelation for them in the event list
	if (ROVERS_DB.isEmpty() && !MISSIONS_DB.isEmpty())
	{
		return false;
	}

	// In case all speeds of all rovers _from all types_ are zero and there are missions in the input file
	// has been formulated and has not been cancelled
	// so we have to check the event list
	int zero_speed = 0;
	Rover* r;
	LinkedPriorityQueue<Rover*, double> temp;
	int count_P = 0;
	int count_M = 0;
	int count_E = 0;
	if (!available_rovers_polar_.isEmpty())
	{
		count_P = available_rovers_polar_.get_itemCount();
		while (available_rovers_polar_.peek(r))
		{
			available_rovers_polar_.dequeue(r);
			if (r->getSpeed() == 0)
				zero_speed++;
			Pair<Rover*, double> pr(r, r->getSpeed());
			temp.enqueue(pr);
		}
		available_rovers_polar_ = temp;

		while (temp.dequeue(r));   //clear temp
	}

	if (!available_rovers_emergency_.isEmpty())
	{
		count_E = available_rovers_emergency_.get_itemCount();
		while (available_rovers_emergency_.peek(r))
		{
			available_rovers_emergency_.dequeue(r);
			if (r->getSpeed() == 0)
				zero_speed++;
			Pair<Rover*, double> pr(r, r->getSpeed());
			temp.enqueue(pr);
		}
		available_rovers_emergency_ = temp;

		while (temp.dequeue(r));   //clear temp
	}

	if (!available_rovers_mountainous_.isEmpty())
	{
		count_M = available_rovers_mountainous_.get_itemCount();
		while (available_rovers_mountainous_.peek(r))
		{
			available_rovers_mountainous_.dequeue(r);
			if (r->getSpeed() == 0)
				zero_speed++;
			Pair<Rover*, double> pr(r, r->getSpeed());
			temp.enqueue(pr);
		}
		available_rovers_mountainous_ = temp;

		while (temp.dequeue(r));   //clear temp
	}
	if (zero_speed == count_M + count_P + count_E)
		return false;

	return true;
}


bool MarsStation::check_polar_R_M() // It will be called first before the simulation
{
	if (available_rovers_polar_.isEmpty() && !waiting_polar_missions_.isEmpty())
		return false;

	return true;
}


void MarsStation::increment_Cancelled_M()
{
	Cancelled_M++;
}


void MarsStation::increment_Formulated_M()
{
	Formulated_M++;
}


MarsStation::~MarsStation()
{
	MISSIONS_DB.clear();
	ROVERS_DB.clear();
	delete my_ui;
}


void MarsStation::simulate_day()
{
	current_day_++; // Advance the day

	check_auto_promotion(); // At the beginning of The day, See if any Mount Mission was auto_promoted

	check_checkup_list(); // Check for rovers finished checkup

	Event* eve = nullptr;

	// Execute events
	while (true)      // The reason of using loop is that  may be more than one event in the same day
	{
		events_list_.peek(eve);
		if (eve && eve->get_ED() == current_day_)
		{
			events_list_.dequeue(eve);
			eve->Execute();
			delete eve;
			eve = nullptr;

		}
		else
			break;
	}
	
	check_completed_missions(); // Check completion

	assign_missions();// Assign missions
}

void MarsStation::move_to_in_ex_list(Mission* miss)
{
	in_execution_missions_.insertEnd(miss);

	//remove from waiting

	MISSION_TYPE type = miss->getMT();

	if (type == MISSION_TYPE::MOUNTAINOUS)
	{
		//Delete it from waiting

		for (int i = 1; i <= waiting_mountainous_missions_.getItemCount(); ++i)
		{
			Mission* m = waiting_mountainous_missions_.getEntry(i);
			if (m->getID() == miss->getID())
			{
				waiting_mountainous_missions_.remove(i);
				return;
			}
		}
	}
}


void MarsStation::move_to_available(Rover* RPtr)
{
	int count = in_execution_rovers_.getItemCount();
	if (RPtr->getRS() == ROVER_STATUS::IN_EXECUTION)
	{
		for (int i = 1; i <= count; i++)
		{
			if (RPtr == in_execution_rovers_.getEntry(i))
			{
				in_execution_rovers_.remove(i);
				break;
			}
		}
	}

	Pair<Rover*, double> pair(RPtr, RPtr->getSpeed());

	switch (RPtr->getRT())
	{
	case ROVER_TYPE::MOUNTAINOUS:
		available_rovers_mountainous_.enqueue(pair);
		break;
	case ROVER_TYPE::POLAR:
		available_rovers_polar_.enqueue(pair);
		break;
	case ROVER_TYPE::EMERGENCY:
		available_rovers_emergency_.enqueue(pair);
		break;
	}
	RPtr->SetRS(ROVER_STATUS::WAITING);
}


void MarsStation::move_to_available(int i)
{
	Rover* RPtr = check_up_rovers_.getEntry(i);
	check_up_rovers_.remove(i);
	Pair<Rover*, double> pair(RPtr, RPtr->getSpeed());

	switch (RPtr->getRT())
	{
	case ROVER_TYPE::MOUNTAINOUS:
		available_rovers_mountainous_.enqueue(pair);
		break;
	case ROVER_TYPE::POLAR:
		available_rovers_polar_.enqueue(pair);
		break;
	case ROVER_TYPE::EMERGENCY:
		available_rovers_emergency_.enqueue(pair);
		break;
	}
	RPtr->SetRS(ROVER_STATUS::WAITING);
}


void MarsStation::move_to_checkup(Rover* RPtr)
{
	RPtr->CheckUP(current_day_);
	int count = in_execution_rovers_.getItemCount();
	for (int i = 1; i <= count; i++)
	{
		if (RPtr == in_execution_rovers_.getEntry(i))
		{
			in_execution_rovers_.remove(i);
			break;
		}
	}
	check_up_rovers_.insertBeg(RPtr);
}


void MarsStation::insert_by_ED(int start, Mission* MPtr)
{
	int i = -1;
	int count = completed_missions_.getItemCount();

	for (i = count; i >= start; i--)
	{
		if (completed_missions_.getEntry(i)->getED() > MPtr->getED());
		else
			break;
	}
	if (i != -1)
		completed_missions_.insertIndex(i + 1, MPtr);
}


void MarsStation::check_auto_promotion()
{
	for (int i = 1; i <= waiting_mountainous_missions_.getItemCount(); ++i)
	{
		Mission* mm = waiting_mountainous_missions_.getEntry(i);
		if (!mm->get_is_promoted() && mm->getWD() > AutoP)
		{
			Promotion pr(current_day_, mm->getID(), this);
			pr.Execute();
			AutoPCount++;
			i--;
		}
	}
}

void MarsStation::check_checkup_list()
{
	for (int i = 1; i <= check_up_rovers_.getItemCount(); i++)
	{
		if (check_up_rovers_.getEntry(i)->getCheckupEND() != current_day_)
			continue;
		move_to_available(i);
		i--;
	}
}


void MarsStation::assign_missions()
{
	Mission* mm;

	// First assign emergency missions
	LinkedPriorityQueue<Mission*, int> temp;   

	while (waiting_emergency_missions_.dequeue(mm))
	{
		Rover* r;
		if (available_rovers_emergency_.dequeue(r))
		{
			mm->Assign(r, r->getSpeed(), current_day_);
			r->AssignTo(mm);
			
			move_to_in_ex_list(mm); // Add to in_ex list
		}
		else if (available_rovers_mountainous_.dequeue(r))
		{
			mm->Assign(r, r->getSpeed(), current_day_);
			r->AssignTo(mm);

			move_to_in_ex_list(mm); // Add to in_ex list
		}
		else if (available_rovers_polar_.dequeue(r)) {
			mm->Assign(r, r->getSpeed(), current_day_);
			r->AssignTo(mm);

			move_to_in_ex_list(mm); // Add to in_ex list
		}
		else // If No rover is available
		{
			mm->WaitAnotherDay();
			Pair<Mission*, int> p(mm, mm->get_priority());
			temp.enqueue(p);
		}
	}

	while (temp.dequeue(mm)) // to clear it
	{
		Pair<Mission*, int> p(mm, mm->get_priority());
		waiting_emergency_missions_.enqueue(p);
	}

	// Second: assign polar missions

	LinkedQueue<Mission*> temp_p;

	while (waiting_polar_missions_.dequeue(mm))
	{
		Rover* r;
		if (available_rovers_polar_.dequeue(r)) {
			mm->Assign(r, r->getSpeed(), current_day_);
			r->AssignTo(mm);

			move_to_in_ex_list(mm); // Add to in_ex list
		}
		else // No rover is available
		{
			mm->WaitAnotherDay();
			temp_p.enqueue(mm);
		}
	}

	while (temp_p.dequeue(mm)) // to clear it
	{
		waiting_polar_missions_.enqueue(mm);
	}

	// Now The Mountainous

	for (int i = 1; i <= waiting_mountainous_missions_.getItemCount(); ++i) //TODO :: YOU might NEED TO Change The LIMITS
	{
		Rover* r;
		mm = waiting_mountainous_missions_.getEntry(i);

		if (available_rovers_mountainous_.dequeue(r))
		{
			mm->Assign(r, r->getSpeed(), current_day_);
			r->AssignTo(mm);
			
			Pair<Mission*, int> p(mm, mm->get_priority());
			temp.enqueue(p); // Add to in_ex list
		}
		else if (available_rovers_emergency_.dequeue(r))
		{
			mm->Assign(r, r->getSpeed(), current_day_);
			r->AssignTo(mm);

			Pair<Mission*, int> p(mm, mm->get_priority());
			temp.enqueue(p); // Add to in_ex list
		}
		else // If No rover is available
		{
			mm->WaitAnotherDay();
		}
	}
	while (temp.dequeue(mm)) // to clear it
	{
		move_to_in_ex_list(mm);
	} // To move all the Assigned Mountainous missions to in_ex List
}


void MarsStation::check_completed_missions()
{
	int LastDistinctIndex = -1, LastDistinctCD = -1;
	Mission* MPtr = nullptr;
	Rover* RPtr = nullptr;
	bool isComp = false;

	for (int i = 1; i <= in_execution_missions_.getItemCount(); i++)
	{
		isComp = false;
		MPtr = in_execution_missions_.getEntry(i);

		if (MPtr)
		{
			isComp = MPtr->isCompleted(current_day_);

		}
		if (isComp)
		{
			RPtr = MPtr->getRover();
			RPtr->incrementCompletedMissions();
			if (RPtr->getMaxMissions() == RPtr->getNumCompletedMissions())
				move_to_checkup(RPtr);
			else
				move_to_available(RPtr);

			MPtr->setMS(MISSION_STATUS::COMPLETED);
			in_execution_missions_.remove(i);
			i--;
			if (current_day_ != LastDistinctCD)
			{
				completed_missions_.insertEnd(MPtr);
				LastDistinctCD = current_day_;
				LastDistinctIndex = completed_missions_.getItemCount();
			}
			else
			{
				insert_by_ED(LastDistinctIndex, MPtr);
			}
		}
	}
}