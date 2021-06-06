#include "MarsStation.h"
#include <iostream>
#include <fstream>
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


LinkedPriorityQueue<Mission*, int>& MarsStation::get_W_E_M()
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
	//TODO:: after the DS is Written
	ifstream my_file("input.txt");

	if (!my_file) {
		return false;
	}


	my_file >> MRCount >> PRCount >> ERCount;



	int N, CM, CP, CE; // no. of missions before checkup and the checkup durations
	my_file >> N >> CM >> CP >> CE;


	double SM, SP, SE; //speed of each type


	int ids = 0;

	// Create Mountainous Rovers
	for (int i = 0; i < MRCount; ++i)
	{
		my_file >> SM;

		Rover* r = new Rover(ROVER_TYPE::MOUNTAINOUS, CM, SM, N, ++ids);
		Pair<Rover*, double> p(r, r->getSpeed());
		available_rovers_mountainous_.enqueue(p);
		ROVERS_DB.add(r);
	}

	// Create Polar Rovers
	for (int i = 0; i < PRCount; ++i)
	{
		my_file >> SP;
		Rover* r = new Rover(ROVER_TYPE::POLAR, CP, SP, N, ++ids);
		Pair<Rover*, double> p(r, r->getSpeed());
		available_rovers_polar_.enqueue(p);
		ROVERS_DB.add(r);

	}

	// Create Emergency Rovers
	for (int i = 0; i < ERCount; ++i)
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

bool MarsStation::writeOutputFile()
{
	int Missions = completed_missions_.getItemCount();
	Mission* Ptr = nullptr;
	ofstream outFile("output.txt");
	if (!(outFile.is_open()))return false;
	if (!Missions)
	{
		outFile << "THERE ARE NO MISSIONS!!!!\n";
		return true;
	}
	int Auto_promoted , MM, PM, EM, Rovers, MR, PR, ER, AvgW, AvgEx;
	Auto_promoted = CollectStatistics_File(Missions, MM, PM, EM, Rovers, MR, PR, ER, AvgW, AvgEx);
	outFile << "CD\tID\tFD\tWD\tED\n";
	for (int i = 1; i <= Missions; i++)
	{
		Ptr = completed_missions_.getEntry(i);
		outFile << Ptr->getCD() << '\t' << Ptr->getID() << '\t' << Ptr->getFD() << '\t' << Ptr->getWD() << '\t' << Ptr->getED() << endl;
	}
	outFile << "Missions: " << Missions << " [M: " << MM << ",P: " << PM << ",E: " << EM << "]\n";
	outFile << "Rovers: " << Rovers << " [M: " << MR << ",P: " << PR << ",E: " << ER << "]\n";
	outFile << "Avg Wait = " << AvgW << ", " << "Avg Exec = " << AvgEx << '\n';
	if (MM)
		outFile << "Auto-promoted: " << Auto_promoted << "%\n";
	else
		outFile << "There are no Mountainious missions.\n";
	outFile.close();
	if (outFile.is_open())return false;
	return true;
}


int MarsStation::CollectStatistics_File(const int& Missions, int& MM, int& PM, int& EM, int& Rovers, int& MR, int& PR, int& ER, int& AvgW, int& AvgEx)
{
	Mission* Ptr = nullptr;
	int Auto = 0;
	int WD = 0;
	int ED = 0;
	MM = 0; PM = 0; EM = 0; Rovers = 0; MR = 0; PR = 0; ER = 0; AvgW = 0; AvgEx = 0;
	MISSION_TYPE TYP;
	//int Count = completed_missions_.getItemCount();
	for (int i = 1; i <= Missions; i++)
	{
		Ptr = completed_missions_.getEntry(i);
		TYP = Ptr->getMT();
		WD += Ptr->getWD();
		ED += Ptr->getED();
		switch (TYP)
		{
		case MISSION_TYPE::MOUNTAINOUS:
			MM++;
			break;
		case MISSION_TYPE::POLAR:
			PM++;
			break;
		case MISSION_TYPE::EMERGENCY:
			EM++;
			break;
		}
	}
	MR = MRCount;
	PR = PRCount;
	ER = ERCount;
	Rovers = MR + PR + ER;
	if (Missions)
	{
		AvgW = WD / Missions;
		AvgEx = ED / Missions;
	}
	if (MM)
		Auto = (AutoPCount / MM) * 100;
	return Auto;
}


bool MarsStation::check_Last_Day()
{
	// first of all we have to check on both the event list and the the completed list
	//if the no of missoins in the completed list == # formulated missions - # cancelled missions
	// && the event list is empty 
	//then no simulate_day() any more 
	return (completed_missions_.getItemCount() == Formulated_M - Cancelled_M) && (events_list_.isEmpty());

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
	current_day_++; //advance the day

	//at the beginning of The day, See if any Mount Mission was auto_promoted
	check_auto_promotion();

	//check for rovers finished checkup
	check_checkup_list();

	Event* eve = nullptr;

	//execute events
	while (true)      //why loop ?? because there may be more than one event in the same day
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


	//check completion
	check_completed_missions();

	//assign missions
	assign_missions();




}

void MarsStation::move_to_in_ex_list(Mission* miss)
{
	in_execution_missions_.insertBeg(miss);

	//remove from waiting

	MISSION_TYPE type = miss->getMT();

	if (type == MISSION_TYPE::MOUNTAINOUS)
	{
		//Delete it from waiting

		for (int i = 1; i <= waiting_mountainous_missions_.getItemCount(); ++i) //3lshan 5ater Rofaida
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
void MarsStation::MoveToAvailable(Rover* RPtr)
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


void MarsStation::MoveToAvailable(int i)
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


void MarsStation::MoveToCheckUp(Rover* RPtr)
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

void MarsStation::InsertAccorToED(int start, Mission* MPtr)
{
	//int index = start;
	int i;
	int count = completed_missions_.getItemCount();
	for (i = count; i >= start; i--)
	{
		if (completed_missions_.getEntry(i)->getED() > MPtr->getED());
		else
			break;
	}
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
	int count = check_up_rovers_.getItemCount();
	for (int i = 1; i <= count; i++)
	{
		if (check_up_rovers_.getEntry(i)->getCheckupEND() != current_day_)
			continue;
		MoveToAvailable(i);
	}
}

void MarsStation::assign_missions()
{

	Mission* mm;

	//first assign emergency missions
	LinkedPriorityQueue<Mission*, int> temp;   //from doaa --> what about using peek then if we find a rover, then dequeue the mission ????
	while (waiting_emergency_missions_.dequeue(mm))
	{
		Rover* r;
		if (available_rovers_emergency_.dequeue(r))
		{

			mm->Assign(r, r->getSpeed(), current_day_);

			r->AssignTo(mm);
			//add to in_ex list
			move_to_in_ex_list(mm);

		}
		else if (available_rovers_mountainous_.dequeue(r))
		{
			mm->Assign(r, r->getSpeed(), current_day_);
			r->AssignTo(mm);

			//add to in_ex list
			move_to_in_ex_list(mm);


		}
		else if (available_rovers_polar_.dequeue(r)) {
			mm->Assign(r, r->getSpeed(), current_day_);

			r->AssignTo(mm);

			//add to in_ex list
			move_to_in_ex_list(mm);

		}
		else //no rover is available
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

	//second: assign polar missions

	LinkedQueue<Mission*> temp_p;

	while (waiting_polar_missions_.dequeue(mm))
	{
		Rover* r;
		if (available_rovers_polar_.dequeue(r)) {
			mm->Assign(r, r->getSpeed(), current_day_);

			r->AssignTo(mm);

			//add to in_ex list
			move_to_in_ex_list(mm);

		}
		else //no rover is available
		{
			mm->WaitAnotherDay();
			//Pair<Mission*, int> p(mm, mm->get_priority());
			//temp.enqueue(p);
			temp_p.enqueue(mm);  //doaa

		}

	}


	while (temp_p.dequeue(mm)) // to clear it
	{
		waiting_polar_missions_.enqueue(mm);
	}

	//now The Mountainous

	for (int i = 1; i <= waiting_mountainous_missions_.getItemCount(); ++i) //TODO :: YOU might NEED TO Change The LIMITS
	{
		Rover* r;
		mm = waiting_mountainous_missions_.getEntry(i);


		if (available_rovers_mountainous_.dequeue(r))
		{
			mm->Assign(r, r->getSpeed(), current_day_);

			r->AssignTo(mm);
			//add to in_ex list
			Pair<Mission*, int> p(mm, mm->get_priority());
			temp.enqueue(p);

		}
		else if (available_rovers_emergency_.dequeue(r))
		{
			mm->Assign(r, r->getSpeed(), current_day_);

			r->AssignTo(mm);

			//add to in_ex list
			Pair<Mission*, int> p(mm, mm->get_priority());
			temp.enqueue(p);

		}
		else //no rover is available
		{
			mm->WaitAnotherDay();
		}


	}
	while (temp.dequeue(mm)) // to clear it
	{
		move_to_in_ex_list(mm);

	} //to move all the Assigned Mountainous missions to in_ex List



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
				MoveToCheckUp(RPtr);
			else
				MoveToAvailable(RPtr);

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
				InsertAccorToED(LastDistinctIndex, MPtr);
			}
		}
	}
}












