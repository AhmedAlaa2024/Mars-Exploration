//------- Doaa 
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

public:
	LinkedPriorityQueue();
	LinkedPriorityQueue(const LinkedPriorityQueue<T, F>& PQ);
	virtual bool isEmpty() const;
	virtual bool enqueue(const Pair<T, F>&);
	virtual bool dequeue(T&);
	virtual bool peek(T&);
	virtual ~LinkedPriorityQueue();
};


template <typename T, typename F>
LinkedPriorityQueue<T, F>::LinkedPriorityQueue()
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
		return true;
	}

	while (searchPos)
	{
		//if it has the smallest priority
		if (!searchPos->getNext())
		{
			//this means that we have checked on the priority and not found one has less priority
			//then insert it at the end of the queue
			searchPos->setNext(insert);
			insert->setNext(nullptr);
			back = insert;
			return true;
		}

		if (searchPos->getNext()->getItem().getPriority() < insert->getItem().getPriority())
		{
			insert->setNext(searchPos->getNext());
			searchPos->setNext(insert);
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
		return true;
	}
	//otherwise --> depueue the first item
	Node<Pair<T, F>>* delPtr = front;
	item = front->getItem().getItem();
	front = front->getNext();
	delete delPtr;
	return true;
}

//suggestion of < Ahmed Ata > :
//the previos 2 functions can be implemented in different way
//instead of putting each item in its correct position in the queue depending on its priority
//we can put them exactly like the ordinary queue
//and when we dequeue ---> we will search for the item with highest priority and dequeue it --> (find max technique)
//but dr. magda does not like this idea because it will have large complexity but i disagree --- > i think same complexity

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