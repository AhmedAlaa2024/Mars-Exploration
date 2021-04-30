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
