//------- Doaa
#pragma once
#include "Pair.h"
template <typename T, typename F>
class PriorityQueueADT
{
public:
	virtual bool isEmpty() const = 0;
	virtual bool enqueue(const Pair<T, F>&) = 0;
	virtual bool dequeue(T&) = 0;
	virtual bool peek(T&) = 0;
	virtual ~PriorityQueueADT() {};
};