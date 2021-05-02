/////////////////////////////// Written By: Ahmed Alaa ///////////////////////////////
#ifndef MISSION_H_
#define MISSION_H_

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

class Mission
{
private:
	int FD; // Formulation Day
	MISSION_TYPE MT; // Mission Type
	MISSION_STATUS MS; // Mission Status
	int TL; // Target Location
	int MD; // Mission Duration
	bool asigned;
	int WD; // Waiting Durations
	int CD; // Complete Date

public:
	// Default Constructor
	Mission(int fd = 0, MISSION_TYPE mt = MISSION_TYPE::UNDETERMINED, int tl = 0, int md = 0);

	// Getters
	int getFD() const;
	MISSION_TYPE getMT() const;
	MISSION_STATUS getMS() const;
	int getTL() const;
	int getMD() const;
	bool IsAssigned() const;
	int getWD() const;
	int getCD() const;
	bool isCompleted() const;

	// Setters
	bool setFD(int fd);
	bool setMT(MISSION_TYPE mt);
	bool setTL(int tl);
	bool setMD(int md);
	bool Asign();
	bool setWD(int wd);

	// Specific Member Functions
	bool WaitAnotherDay();
	bool Complete(int speed);
	bool Promote();
};
#endif // !MISSION_H_