// i think that there is no need to this class ---> we can use the QueueADT class because they have the same functions ---> question to Ahmed Alaa
//aslan ana 3malt copy ll class ally enta kont 3amlo :D
//------- Doaa
#pragma once
template <typename T>
class PriorityQueueADT
{
public:
	virtual bool isEmpty() const = 0;
	virtual bool enqueue(const T&) = 0;
	virtual bool dequeue(T&) = 0;
	virtual bool peek(T&) = 0;
	virtual ~PriorityQueueADT() {};
};