#pragma once


#include "PriorityQueueADT.h"
#include "Node.h"
#include "Pair.h"


template <typename T, typename F>
class LinkedPriorityQueue :public PriorityQueueADT<T, F>
{
	//data members
	Node<Pair<T, F>>* front;
	Node<Pair<T, F>>* back;   //or call it rear i think ---> which is better ):
	int itemCount;

public:
	LinkedPriorityQueue();
	LinkedPriorityQueue(const LinkedPriorityQueue<T, F>& PQ);
	virtual bool isEmpty() const;
	virtual bool enqueue(const Pair<T, F>&);
	virtual bool dequeue(T&);
	virtual bool peek(T&);
	virtual ~LinkedPriorityQueue();
	int get_itemCount();

	const LinkedPriorityQueue<T, F>& operator = (LinkedPriorityQueue&);
};

template <typename T, typename F>
const LinkedPriorityQueue<T, F>& LinkedPriorityQueue<T, F>::operator = (LinkedPriorityQueue& right_LQ)  // i think it should be passed const ---> but we will call non const member func on it so we can not pass it const ---> is it ok ????
{
	//in case the right obj is empty
	if (right_LQ.isEmpty()) return *this;

	T temp;
	//delete all items in the left queue
	while (dequeue(temp));

	Node<Pair<T, F>>* ptr = right_LQ.front;

	while (ptr)
	{
		enqueue(ptr->getItem());
		ptr = ptr->getNext();
	}

	
	return *this;
}







template <typename T, typename F>
LinkedPriorityQueue<T, F>::LinkedPriorityQueue() :itemCount(0)
{
	front = nullptr;
	back = nullptr;
}

//copy constructor
template <typename T, typename F>
LinkedPriorityQueue<T, F>::LinkedPriorityQueue(const LinkedPriorityQueue<T, F>& PQ)
{
	if (PQ.isEmpty())
		return;
	Node<Pair<T, F>>* ptr = PQ.front;
	while (ptr)
	{
		enqueue(ptr->getItem());
		ptr = ptr->getNext();
	}
}


template <typename T, typename F>
int LinkedPriorityQueue<T, F>::get_itemCount()
{
	return itemCount;
}


template <typename T, typename F>
bool LinkedPriorityQueue<T, F>::isEmpty() const
{
	return front == nullptr;
}



template <typename T, typename F>
bool LinkedPriorityQueue<T, F>::enqueue(const Pair<T, F>& item)
{
	//in case the list is empty
	if (!front)
	{
		front = new Node<Pair<T, F>>(item);
		back = front;
		back->setNext(nullptr);
		itemCount++;
		return true;
	}

	//enqueue depends on the priority
	Node<Pair<T, F>>* insert = new Node<Pair<T, F>>(item);
	Node<Pair<T, F>>* searchPos = front;
	//in case it has the highest priority
	if (insert->getItem().getPriority() > front->getItem().getPriority())
	{
		insert->setNext(front);
		front = insert;
		itemCount++;
		return true;
	}

	while (searchPos)
	{
		//if it has the smallest priority
		if (!searchPos->getNext())
		{
			
			searchPos->setNext(insert);
			insert->setNext(nullptr);
			back = insert;
			itemCount++;
			return true;
		}

		if (searchPos->getNext()->getItem().getPriority() < insert->getItem().getPriority())
		{
			insert->setNext(searchPos->getNext());
			searchPos->setNext(insert);
			itemCount++;
			return true;
		}
		searchPos = searchPos->getNext();
	}


}

template <typename T, typename F>
bool LinkedPriorityQueue<T, F>::dequeue(T& item)
{
	//in case of empty queue
	if (!front)
		return false;
	//in case there is only one item
	if (front == back)
	{
		item = front->getItem().getItem();
		delete front;
		front = back = nullptr;
		itemCount--;
		return true;
	}
	//otherwise --> depueue the first item
	Node<Pair<T, F>>* delPtr = front;
	item = front->getItem().getItem();
	front = front->getNext();
	delete delPtr;
	itemCount--;
	return true;
}


template <typename T, typename F>
bool LinkedPriorityQueue<T, F>::peek(T& item)
{
	if (!front)
		return false;
	item = front->getItem().getItem();
	return true;
}


template <typename T, typename F>
LinkedPriorityQueue<T, F>::~LinkedPriorityQueue()
{
	T temp;
	//delete all items 
	while (dequeue(temp));
}