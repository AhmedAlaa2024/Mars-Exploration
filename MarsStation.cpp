#include "MarsStation.h"
#include <iostream>
#include <fstream>
#include "Defs.h"
#include "Formulation.h"
#include "Promotion.h"
#include "Cancellation.h"
MarsStation::MarsStation() :AutoP(0), current_day_(0), Cancelled_M(0), Formulated_M(0)
{

	my_ui = new UI(this);
	read_input_file();


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



LinkedList<Mission*>& MarsStation::get_waiting_mountainous_missions_()
{
	return waiting_mountainous_missions_;
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



	int M, P, E; //no of each Rover Type
	my_file >> M >> P >> E;
	int SM, SP, SE; //speed of each type
	my_file >> SM >> SP >> SE;



	int N, CM, CP, CE; // no. of missions before checkup and the checkup durations
	my_file >> N >> CM >> CP >> CE;


	int ids = 0;

	// Create Mountainous Rovers
	for (int i = 0; i < M; ++i)
	{
		Rover* r = new Rover(ROVER_TYPE::MOUNTAINOUS, CM, SM, N, ++ids);
		Pair<Rover*, double> p(r, r->getSpeed());
		available_rovers_mountainous_.enqueue(p);
	}

	// Create Polar Rovers
	for (int i = 0; i < P; ++i)
	{
		Rover* r = new Rover(ROVER_TYPE::POLAR, CP, SP, N, ++ids);
		Pair<Rover*, double> p(r, r->getSpeed());
		available_rovers_polar_.enqueue(p);
	}

	// Create Emergency Rovers
	for (int i = 0; i < E; ++i)
	{
		Rover* r = new Rover(ROVER_TYPE::EMERGENCY, CE, SE, N, ++ids);
		Pair<Rover*, double> p(r, r->getSpeed());
		available_rovers_emergency_.enqueue(p);
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

bool MarsStation::writeOutputFile() const
{
	int Auto_promoted, Missions, MM, PM, EM, Rovers, MR, PR, ER, AvgW, AvgEx;
	Auto_promoted = CollectStatistics_File(Missions, MM, PM, EM, Rovers, MR, PR, ER, AvgW, AvgEx);
	ofstream outFile("output.txt");
	if (!(outFile.is_open()))return false;
	outFile << "CD\tID\tFD\tWD\tED\n";
	while (true) // To be changed after making CM Queue
	{
		//TODO:: writing info about missions
	}
	outFile << "Missions: " << Missions << " [M: " << MM << ",P: " << PM << ",E: " << EM << "]\n";
	outFile << "Rovers: " << Rovers << " [M: " << MR << ",P: " << PR << ",E: " << ER << "]\n";
	outFile << "Avg Wait = " << AvgW << ", " << "Avg Exec = " << AvgEx << '\n' << "Auto-promoted: " << Auto_promoted << "%\n";
	return false;
}

void MarsStation::CollectStatistics_Console()
{




}





int MarsStation::CollectStatistics_File(int& Missions, int& MM, int& PM, int& EM, int& Rovers, int& MR, int& PR, int& ER, int& AvgW, int& AvgEx) const
{
	int Auto = 0;
	int WD = 0;
	int ED = 0;
	Missions = 0; MM = 0; PM = 0; EM = 0; Rovers = 0; MR = 0; PR = 0; ER = 0; AvgW = 0; AvgEx = 0;
	char TYP = 'j'; //mission type, TO BE CHANGED
	while (true) // To be changed after making CM Queue
	{
		Missions++;
		//WD += WD for the current mission
		//ED += ED for the current mission
		switch (TYP)
		{
		case 'M':
			MM++;
			break;
		case 'P':
			PM++;
			break;
		case 'E':
			EM++;
			break;
		}
	}
	while (true) // To be changed after making Rovers
	{
		//counting rovers and their type
	}

	//TODO:: Calcuclate Auto

	AvgW = WD / Missions;
	AvgEx = ED / Missions;
	Auto = (Auto / MM) * 100;
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


void MarsStation::simulate_day()
{
	current_day_++; //advance the day

	//at the beginning of The day, See if any Mount Mission was auto_promoted
	check_auto_promotion();

	Event* eve;

	//execute events
	while (true)      //why loop ?? because there may be more than one event in the same day
	{
		events_list_.peek(eve);
		if (eve->get_ED() == current_day_)
		{
			events_list_.dequeue(eve);
			eve->Execute();
		}
		else
			break;

	}

	//assign missions
	assign_missions();


	//check completion
	check_completed_missions();



}

void MarsStation::move_to_in_ex_list(Mission* miss)
{
	in_execution_missions_.insert(miss);

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
void MarsStation::check_auto_promotion()
{

	for (int i = 0; i < waiting_mountainous_missions_.getItemCount(); ++i) //TODO :: YOU might NEED TO Change The LIMITS
	{

		Mission* mm = waiting_mountainous_missions_.getEntry(i);
		if (!mm->get_is_promoted() && mm->getWD() > AutoP)
		{
			Promotion pr(current_day_, mm->getID(), this);
			pr.Execute();

		}

	}

}

void MarsStation::assign_missions()
{
	//TODO:: ADD THE CD Assignment
	
	Mission* mm;

	//first assign emergency missions
	LinkedPriorityQueue<Mission*, int> temp;
	while (waiting_emergency_missions_.dequeue(mm))
	{
		Rover* r;
		if (available_rovers_emergency_.dequeue(r))
		{

			mm->Assign(r);
			r->AssignTo(mm, current_day_);
			//add to in_ex list
			move_to_in_ex_list(mm);

		}
		else if (available_rovers_mountainous_.dequeue(r))
		{
			mm->Assign(r);
			r->AssignTo(mm, current_day_);

			//add to in_ex list
			move_to_in_ex_list(mm);


		}
		else if (available_rovers_polar_.dequeue(r)) {
			mm->Assign(r);
			r->AssignTo(mm, current_day_);

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
	waiting_emergency_missions_ = temp;

	while (temp.dequeue(mm)) // to clear it
	{

	}

	//second: assign polar missions

	while (waiting_polar_missions_.dequeue(mm))
	{
		Rover* r;
		if (available_rovers_polar_.dequeue(r)) {
			mm->Assign(r);
			r->AssignTo(mm, current_day_);

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

	}

	//now The Mountainous
	
	for (int i = 0; i < waiting_mountainous_missions_.getItemCount(); ++i) //TODO :: YOU might NEED TO Change The LIMITS
	{
		Rover* r;
		mm = waiting_mountainous_missions_.getEntry(i);


		if (available_rovers_mountainous_.dequeue(r))
		{
			mm->Assign(r);
			r->AssignTo(mm, current_day_);
			//add to in_ex list
			Pair<Mission*, int> p(mm, mm->get_priority());
			temp.enqueue(p);

		}
		else if (available_rovers_emergency_.dequeue(r))
		{
			mm->Assign(r);
			r->AssignTo(mm, current_day_);

			//add to in_ex list
			Pair<Mission*, int> p(mm, mm->get_priority());
			temp.enqueue(p);

		}
		else //no rover is available
		{
			mm->WaitAnotherDay();
		}
		while (temp.dequeue(mm)) // to clear it
		{
			move_to_in_ex_list(mm);

		}

		
	}




}

void MarsStation::check_completed_missions()
{








}