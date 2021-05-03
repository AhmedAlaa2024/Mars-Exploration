#pragma once

template <typename T>
class ListADT
{
public:
	//virtual int getCurrentSize() const = 0;
	virtual bool isEmpty() const = 0;
	virtual bool insert(const T&) = 0;
	virtual bool remove(int index) = 0;
	virtual bool clear() = 0;
	virtual int getEntry(const T&) const = 0;
	virtual bool contains(T&) const = 0;




};

