#include <iostream>


#include "MarsStation.h"



int main()
{
	
	MarsStation station_;
	SIM_MODE mode = station_.get_input_mode();

	station_.execute_mode(mode);

	





	return 0;
}


