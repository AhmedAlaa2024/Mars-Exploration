#include "UI.h"

SIM_MODE UI::select_mode()
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
