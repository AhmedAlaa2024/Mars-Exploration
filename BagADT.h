#ifndef BAGADT_H_
#define BAGADT_H_

template <typename T>
class BagADT
{
public:
	virtual int getCurrentSize() const = 0;
	virtual bool isEmpty() const = 0;
	virtual bool add(const T&) = 0;
	virtual bool remove(const T&) = 0;
	virtual bool clear() = 0;
	virtual int getFrequencyOf(const T&) const = 0;
	virtual bool contains(const T&) const = 0;

};
#endif 