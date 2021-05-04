#pragma once
#include "ListADT.h"

template <typename T>
class LinkedList :
	public ListADT<T>
{
private:
	Node<T>* Head;	//Pointer to the head of the list
	int itemCount;
	//utility functions
/*	Node<T>* getPointerTo(const T&) ;
	Node<T>* getPrevOf(const T&);*/
	Node<T>* getNodeAt(int index);
public:

	LinkedList();
	~LinkedList();
	LinkedList(LinkedList& l);
	virtual bool isEmpty() const;
	virtual bool insert(const T&);
	virtual bool remove(int index);
	virtual bool clear();
	virtual T getEntry(const int) const;
	virtual bool contains(T&) const;
	int getItemCount();
	void DeleteAll();

};



template <typename T>
LinkedList<T>::LinkedList()
{
	Head = nullptr;
	itemCount = 0;
}



template <typename T>
LinkedList<T>::LinkedList(LinkedList& l)
{
	itemCount = l.itemCount;
	Node<T>* ptr = l->Head;
	while (ptr)
	{
		insert(ptr->getItem());
		ptr = ptr->getNext();
	}
}


template <typename T>
Node<T>* LinkedList<T>::getNodeAt(int index)
{
	if (index > itemCount || index <= 0) return nullptr;
	Node<T>* curPtr = Head;
	for (int i = 1; i < index; i++)
	{
		curPtr = curPtr->getNext();
	}
	return curPtr;
}


//template <typename T>
//Node<T>* getPointerTo(const T& target)
//{
//	Node<T>* ptr = head;
//	while (ptr) {
//		if (ptr->getItem() == target)
//			return ptr;
//		ptr = ptr->getNext();
//	}
//	return nullptr;
//}
//
//
//template <typename T>
//Node<T>* getPrevOf(const T& target)
//{
//	Node<T>* ptr = head;
//	while (ptr->getNext()) {
//		if (ptr->getNext()->getItem() == target)
//			return ptr;
//		ptr = ptr->getNext();
//	}
//	return nullptr;
//}



template <typename T>
bool LinkedList<T>::isEmpty() const
{
	return Head == nullptr;
}



template <typename T>
bool LinkedList<T>::insert(const T& data)
{
	Node<T>* R = new Node<T>(data);

	if (!R)
		return false;

	R->setNext(Head);
	Head = R;
	itemCount++;
	return true;
}



template <typename T>
bool LinkedList<T>::remove(int index)
{
	bool ableToRemove = (index >= 1 && index <= itemCount);

	if (ableToRemove)
	{
		Node<T>* curptr = nullptr;
		if (index == 1)
		{
			curptr = Head;
			Head = Head->getNext();
		}
		else
		{
			Node<T>* prevPtr = getNodeAt(index - 1);
			curptr = prevPtr->getNext();
			prevPtr->setNext(curptr->getNext());
		}
		
		curptr->setNext(nullptr);
		itemCount--;
	}
	return ableToRemove;
}



template <typename T>
bool LinkedList<T>::clear()
{
	return 0;
}


template <typename T>
T LinkedList<T>::getEntry(const int ind) const
{
	Node<T>* ptr = Head;


	for (int i = 1; i < ind; ++i)
	{
		ptr = ptr->getNext();
	}

	if (ptr)
		return ptr->getItem();
	return nullptr;
}



template <typename T>
bool LinkedList<T>::contains(T&) const
{
	return 0;
}


template <typename T>
int LinkedList<T>::getItemCount()
{
	return itemCount;
}


template <typename T>
void LinkedList<T>::DeleteAll()
{
	Node<T>* P = Head;
	while (Head)
	{
		P = Head->getNext();
		delete Head;
		Head = P;
	}
}


template <typename T>
LinkedList<T>::~LinkedList()
{
	DeleteAll();
}