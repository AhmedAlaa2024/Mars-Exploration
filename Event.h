#pragma once

class Event
{
	int ED; // execution day
	int ID; // Mission's id
public:
	Event(int ed , int id);
	virtual void Execute() = 0;

	int get_ED() const;
	virtual ~Event() {}
};
