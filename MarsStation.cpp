#include "MarsStation.h"
#include <iostream>
#include <fstream>

#include "Formulation.h"
#include "Promotion.h"
#include "Cancellation.h"
MarsStation::MarsStation()
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
		cout << "Interactive" << endl; //to be changed
	}
	else if (mode == SIM_MODE::STEP_BY_STEP)
	{
		cout << "step by step" << endl; //to be changed

	}
	else
	{
		cout << "Silent" << endl; //to be changed

	}
}

bool MarsStation::read_input_file()
{
	//TODO:: after the DS is Written
	ifstream my_file("input.txt");

	if (!my_file) {
		return false;
	}

	int input;

	int M, P, E; //no of each Rover Type
	my_file >> M >> P >> E;

	int SM, SP, SE; //speed of each type
	my_file >> SM >> SP >> SE;

	int N, CM, CP, CE; // no. of missions before checkup and the checkup durations

	my_file >> N >> CM >> CP >> CE;

	int AutoP;

	my_file >> AutoP;

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

			Event* eve = new Formulation(TYP, ED, ID, TLOC, MDUR, SIG);
			Events_list_.enqueue(eve);
		}
		else if (c == 'X') //cancellation Event
		{
			int ED;
			int ID;
			my_file >> ED >> ID;
			Event* eve = new Cancellation(ED, ID);
			Events_list_.enqueue(eve);


		}
		else if (c == 'P')
		{
			int ED;
			int ID;
			my_file >> ED >> ID;
			Event* eve = new Promotion(ED, ID);
			Events_list_.enqueue(eve);

		}






	}






	my_file.close();


	return true;
}
