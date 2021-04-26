#include <iostream>

#include "UI.h"


int main()
{
	UI my_ui;

	SIM_MODE mode = my_ui.select_mode();

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




	return 0;
}


