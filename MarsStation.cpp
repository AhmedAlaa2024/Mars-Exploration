#include "MarsStation.h"

MarsStation::MarsStation() 
{
	my_ui = new UI(this);
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
