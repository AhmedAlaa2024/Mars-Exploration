#include "UI.h"
#include <iostream>
//#include "LinkedPriorityQueue.h"
#include <fstream>
#include<Windows.h>  //for the delay
using namespace std;

UI::UI(MarsStation* p_s) : p_station(p_s)
{

}

SIM_MODE UI::get_input_mode()
{

	std::cout << "Please select The mode you want to enter" << endl <<
		"1- Interactive Mode\n2- Step-By-Step Mode\n3- Silent Mode\n enter: ";

	int n;
	cin >> n;
	while (n > 3 || n < 1)
	{
		cout << "Please enter a valid number: ";
		cin >> n;

	}

	SIM_MODE a;
	if (n == 1)
		return SIM_MODE::INTERACTIVE;

	if (n == 2)
		return SIM_MODE::STEP_BY_STEP;

	return SIM_MODE::SILENT;

}




void UI::Output_Console()const
{
	

	cout << "Current Day : " << p_station->get_current_day() << endl;


	//Waiting Missions

	//calculate # of waiting missions
	int no_W_M = p_station->get_W_E_M().get_itemCount() + p_station->get_W_P_M().get_itemCount() + p_station->get_W_M_M().getItemCount();

	cout << no_W_M << " Waiting Missions : ";
	//first --> print the ID of the E missions
	cout << " [";
	Mission* m = nullptr;
	int j = 0;
	int count = p_station->get_W_E_M().get_itemCount();
	LinkedPriorityQueue<Mission*, int> temp;
	for (int i = 1; i <= count; i++)
	{
		p_station->get_W_E_M().dequeue(m);

		if (j == 0)
			cout << m->getID();
		else
			cout << "," << m->getID();
		j++;
		//then enqueue it again
		Pair<Mission*, int> pm(m, m->get_priority());
		temp.enqueue(pm);
	}
	cout << "]";
	p_station->get_W_E_M() = temp;

	while (temp.dequeue(m))   //clear temp
	{

	}
	
	//second --> print the ID of the polar Mission
	cout << " (";
	j = 0;
	count = p_station->get_W_P_M().get_itemCount();
	for (int i = 1; i <= count; i++)
	{
		p_station->get_W_P_M().dequeue(m);

		if (j == 0)
			cout << m->getID();
		else
			cout << "," << m->getID();
		j++;
		//then enqueue it again
		p_station->get_W_P_M().enqueue(m);
	}
	cout << ")";

	

	//third --> print the ID of the mountainous missions
	cout << " {";
	for (int i = 1; i <= p_station->get_W_M_M().getItemCount(); i++)   //itemCount does not change during this loop
	{
		if (i == p_station->get_W_M_M().getItemCount())   //so print wihtout the ","
			cout << p_station->get_W_M_M().getEntry(i)->getID();
		else
			cout << p_station->get_W_M_M().getEntry(i)->getID() << ",";

	}
	cout << " } " << endl;

	cout << "--------------------------------------------------------------------------------------------" << endl;

	//In-Execution Missions/Rovers

	//calculate no of In-Execution Missions/Rovers
	int no_exe = p_station->get_in_execution_missions().getItemCount();
	cout << no_exe << " In-Execution Missions/Rovers: ";
	cout << " [";
	j = 0;
	for (int i = 1; i <= p_station->get_in_execution_missions().getItemCount(); i++)
	{
		if (p_station->get_in_execution_missions().getEntry(i)->getMT() == MISSION_TYPE::EMERGENCY)
		{
			if (j == 0)
				cout << p_station->get_in_execution_missions().getEntry(i)->getID() << "/" << p_station->get_in_execution_missions().getEntry(i)->getRover()->getID();
			else
				cout << "," << p_station->get_in_execution_missions().getEntry(i)->getID() << "/" << p_station->get_in_execution_missions().getEntry(i)->getRover()->getID();
			j++;
		}
	}
	cout << "] " << "(";

	j = 0;
	for (int i = 1; i <= p_station->get_in_execution_missions().getItemCount(); i++)
	{
		if (p_station->get_in_execution_missions().getEntry(i)->getMT() == MISSION_TYPE::POLAR)
		{
			if (j == 0)
				cout << p_station->get_in_execution_missions().getEntry(i)->getID() << "/" << p_station->get_in_execution_missions().getEntry(i)->getRover()->getID();
			else
				cout << "," << p_station->get_in_execution_missions().getEntry(i)->getID() << "/" << p_station->get_in_execution_missions().getEntry(i)->getRover()->getID();
			j++;
		}
	}
	cout << ") " << "{";

	j = 0;
	for (int i = 1; i <= p_station->get_in_execution_missions().getItemCount(); i++)
	{
		if (p_station->get_in_execution_missions().getEntry(i)->getMT() == MISSION_TYPE::MOUNTAINOUS)
		{
			if (j == 0)
				cout << p_station->get_in_execution_missions().getEntry(i)->getID() << "/" << p_station->get_in_execution_missions().getEntry(i)->getRover()->getID();
			else
				cout << "," << p_station->get_in_execution_missions().getEntry(i)->getID() << "/" << p_station->get_in_execution_missions().getEntry(i)->getRover()->getID();
			j++;
		}
	}
	cout << "}" << endl;


	cout << "--------------------------------------------------------------------------------------------" << endl;


	//Available Rovers

	int no_R = p_station->get_available_rovers_emergency_().get_itemCount() + p_station->get_available_rovers_mountainous_().get_itemCount() + p_station->get_available_rovers_polar_().get_itemCount();
	int n_ER = p_station->get_available_rovers_emergency_().get_itemCount();
	Rover* r = nullptr;
	cout << no_R << " Available Rovers: " << " [";
	j = 0;
	for (int i = 1; i <= n_ER; i++)
	{
		p_station->get_available_rovers_emergency_().dequeue(r);
		if (r->getRT() == ROVER_TYPE::EMERGENCY)
		{
			if (j == 0)
				cout << r->getID();
			else
				cout << "," << r->getID();
		}
		j++;
		//enqueue it again
		Pair<Rover*, double> pr(r, r->getSpeed());
		p_station->get_available_rovers_emergency_().enqueue(pr);
	}
	cout << "] " << "(";


	int n_PR = p_station->get_available_rovers_polar_().get_itemCount();
	j = 0;
	for (int i = 1; i <= n_PR; i++)
	{
		p_station->get_available_rovers_polar_().dequeue(r);
		if (r->getRT() == ROVER_TYPE::POLAR)
		{
			if (j == 0)
				cout << r->getID();
			else
				cout << "," << r->getID();
		}
		j++;
		//enqueue it again
		Pair<Rover*, double> pr(r, r->getSpeed());
		p_station->get_available_rovers_polar_().enqueue(pr);
	}
	cout << ") " << "{";


	int n_MR = p_station->get_available_rovers_mountainous_().get_itemCount();
	j = 0;
	for (int i = 1; i <= n_MR; i++)
	{
		p_station->get_available_rovers_mountainous_().dequeue(r);
		if (r->getRT() == ROVER_TYPE::MOUNTAINOUS)
		{
			if (j == 0)
				cout << r->getID();
			else
				cout << "," << r->getID();
		}
		j++;
		//enqueue it again
		Pair<Rover*, double> pr(r, r->getSpeed());
		p_station->get_available_rovers_mountainous_().enqueue(pr);
	}
	cout << "} " << endl;


	cout << "--------------------------------------------------------------------------------------------" << endl;

	//In-Checkup Rovers

	cout << p_station->get_check_up_rovers_().getItemCount() << " In-Checkup Rovers: ";
	cout << " [";
	j = 0;
	for (int i = 1; i <= p_station->get_check_up_rovers_().getItemCount(); i++)
	{
		if (p_station->get_check_up_rovers_().getEntry(i)->getRT() == ROVER_TYPE::EMERGENCY)
		{
			if (j == 0)
				cout << p_station->get_check_up_rovers_().getEntry(i)->getID();
			else
				cout << "," << p_station->get_check_up_rovers_().getEntry(i)->getID();
			j++;
		}
	}
	cout << "] " << "(";


	j = 0;
	for (int i = 1; i <= p_station->get_check_up_rovers_().getItemCount(); i++)
	{
		if (p_station->get_check_up_rovers_().getEntry(i)->getRT() == ROVER_TYPE::POLAR)
		{
			if (j == 0)
				cout << p_station->get_check_up_rovers_().getEntry(i)->getID();
			else
				cout << "," << p_station->get_check_up_rovers_().getEntry(i)->getID();
			j++;
		}
	}
	cout << ") " << "{";


	j = 0;
	for (int i = 1; i <= p_station->get_check_up_rovers_().getItemCount(); i++)
	{
		if (p_station->get_check_up_rovers_().getEntry(i)->getRT() == ROVER_TYPE::MOUNTAINOUS)
		{
			if (j == 0)
				cout << p_station->get_check_up_rovers_().getEntry(i)->getID();
			else
				cout << "," << p_station->get_check_up_rovers_().getEntry(i)->getID();
			j++;
		}
	}
	cout << "}" << endl;

	cout << "--------------------------------------------------------------------------------------------" << endl;


	//Completed Missions

	cout << p_station->get_completed_missions_().getItemCount() << " Completed Missions: ";
	cout << " [";
	j = 0;
	for (int i = 1; i <= p_station->get_completed_missions_().getItemCount(); i++)
	{
		if (p_station->get_completed_missions_().getEntry(i)->getMT() == MISSION_TYPE::EMERGENCY)
		{
			if (j == 0)
				cout << p_station->get_completed_missions_().getEntry(i)->getID();
			else
				cout << "," << p_station->get_completed_missions_().getEntry(i)->getID();
			j++;
		}
	}
	cout << "] " << "(";


	j = 0;
	for (int i = 1; i <= p_station->get_completed_missions_().getItemCount(); i++)
	{
		if (p_station->get_completed_missions_().getEntry(i)->getMT() == MISSION_TYPE::POLAR)
		{
			if (j == 0)
				cout << p_station->get_completed_missions_().getEntry(i)->getID();
			else
				cout << "," << p_station->get_completed_missions_().getEntry(i)->getID();
			j++;
		}
	}
	cout << ") " << "{";


	j = 0;
	for (int i = 1; i <= p_station->get_completed_missions_().getItemCount(); i++)
	{
		if (p_station->get_completed_missions_().getEntry(i)->getMT() == MISSION_TYPE::MOUNTAINOUS)
		{
			if (j == 0)
				cout << p_station->get_completed_missions_().getEntry(i)->getID();
			else
				cout << "," << p_station->get_completed_missions_().getEntry(i)->getID();
			j++;
		}
	}
	cout << "}" << endl;

	cout << "--------------------------------------------------------------------------------------------" << endl;



	//cin >> key;   //what if the user press another key ---> i will handle it later because i do not remember how right now
}


// TO BE CHANGED....
void UI::InteractivePrinting() const
{
	cout << "Interactive Mode\n";

	//TODO:: cout statistics and wait for cin

	char key;
	//cin >> key;
	//check if end of days
	while (!p_station->check_Last_Day())
	{
		cin >> key;
		//if (key != 10)   //TODO:: Change this
			//continue;

		p_station->simulate_day();

		Output_Console();


		//cin >> key;   //what if the user press another key ---> i will handle it later because i do not remember how right now
	}

	//finally create the file
	p_station->writeOutputFile();

	bool isWritten = p_station->writeOutputFile();
	if (isWritten)
		cout << "Simulation ends, Output file created\n";
	else
		cout << "Error! writing into file\n";
}





// TO BE CHANGED....
void UI::StepByStepPrinting() const
{
	cout << "Step by step Mode\n";
	
	// TODO:: cout statistics and wait for some time then cout
	while (!p_station->check_Last_Day())
	{
		p_station->simulate_day();
		Output_Console();
		Sleep(1);
	}

	p_station->writeOutputFile();  // i think it should be removed

	bool isWritten = p_station->writeOutputFile();
	if (isWritten)
		cout << "Simulation ends, Output file created\n";
	else
		cout << "Error! writing into file\n";
}

void UI::SilentPrinting() const
{
	cout << "Silent Mode\n";
	cout << "Simulation Starts...\n";

	while (!p_station->check_Last_Day())
	{
		p_station->simulate_day();
	}

	bool isWritten = p_station->writeOutputFile();
	if (isWritten)
		cout << "Simulation ends, Output file created\n";
	else
		cout << "Error! writing into file\n";
}
