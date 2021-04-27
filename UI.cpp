#include "UI.h"

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
