#pragma once
// For all the enums and any structs to be used in any part //Like The Rovers Type Part


enum class SIM_MODE
{
	INTERACTIVE,
	STEP_BY_STEP,
	SILENT
};


enum class ROVER_TYPE {
	UNDETERMINED,
	EMERGENCY,
	MOUNTAINOUS,
	POLAR
};

enum class ROVER_STATUS {
	WAITING,
	IN_EXECUTION,
	CHECKUP
};

enum class MISSION_TYPE {
	UNDETERMINED,
	EMERGENCY,
	MOUNTAINOUS,
	POLAR
};

enum class MISSION_STATUS {
	WAITING,
	IN_EXECUTION,
	COMPLETED,
	CANCELLED
};