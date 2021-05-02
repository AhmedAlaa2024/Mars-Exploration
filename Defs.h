#pragma once
//for all the enums and any structs to be used in any part //Like The Rovers Type Part



enum class SIM_MODE
{
	INTERACTIVE,
	STEP_BY_STEP,
	SILENT
};

enum class MISSION_TYPE {
	UNDETERMINED = 0,
	EMERGENCY = 1,
	MOUNTAINOUS = 2,
	POLAR = 3
};

enum class MISSION_STATUS {
	WAITING = 0,
	IN_EXECUTION = 1,
	COMPLETED = 2
};


enum class ROVER_TYPE {
	UNDETERMINED = 0,
	EMERGENCY = 1,
	MOUNTAINOUS = 2,
	POLAR = 3
};

enum class ROVER_STATUS {
	WAITING = 0,
	IN_EXECUTION = 1,
	CHECKUP = 2
};
