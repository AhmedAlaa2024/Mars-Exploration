#include "UI.h"
#include <iostream>
#include <fstream>
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

// TO BE CHANGED....
void UI::InteractivePrinting() const
{
	cout << "Interactive Mode\n";
	p_station->CollectStatistics_Console();
	// TODO:: cout statistics and wait for cin
}
// TO BE CHANGED....
void UI::StepByStepPrinting() const
{
	cout << "Step by step Mode\n";
	p_station->CollectStatistics_Console();
	// TODO:: cout statistics and wait for some time then cout
}

void UI::SilentPrinting() const
{
	cout << "Silent Mode\n";
	cout << "Simulation Starts...\n";

	bool isWritten = p_station->writeOutputFile();
	if (isWritten)
		cout << "Simulation ends, Output file created\n";
	else
		cout << "Error! writing into file\n";
}
