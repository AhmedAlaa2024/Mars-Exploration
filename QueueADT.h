/////////////////////////////// Written By: Ahmed Alaa ///////////////////////////////

#ifndef QUEUEADT_H_
#define QUEUEADT_H_

template <typename T>
class QueueADT
{
public:
	virtual bool isEmpty() const = 0;
	virtual bool enqueue(const T&) = 0;
	virtual bool dequeue(T&) = 0;
	virtual bool peek(T&) = 0;
	virtual ~QueueADT() {};
};

#endif // !QUEUEADT_H_