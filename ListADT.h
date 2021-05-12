#pragma once

template <typename T>
class ListADT
{
public:
	//virtual int getCurrentSize() const = 0;
	virtual bool isEmpty() const = 0;
	virtual bool insertIndex(int, const T&) = 0;
	virtual bool insertBeg(const T&) = 0;
	virtual bool insertEnd(const T&) = 0;
	virtual bool remove(int index) = 0;
	virtual bool clear() = 0;
	virtual T getEntry(const int) const = 0;
	virtual bool contains(T&) const = 0;




};

