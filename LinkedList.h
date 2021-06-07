#pragma once
#include "ListADT.h"

template <typename T>
class LinkedList :
	public ListADT<T>
{
private:
	Node<T>* Head;	//Pointer to the head of the list
	int itemCount;
	
	Node<T>* getNodeAt(int index);
public:

	LinkedList();
	~LinkedList();
	LinkedList(LinkedList& l);
	virtual bool isEmpty() const;
	virtual bool insertIndex(int, const T&);
	virtual bool insertBeg(const T&);
	virtual bool insertEnd(const T&);
	virtual bool remove(int index);
	virtual T getEntry(const int) const;
	virtual bool contains(T&) const;
	int getItemCount();
	void DeleteAll();
	const LinkedList<T>& operator = (LinkedList&);
};

template <typename T>
LinkedList<T>::LinkedList()
{
	Head = nullptr;
	itemCount = 0;
}


template <typename T>
const LinkedList<T>& LinkedList<T>::operator = (LinkedList& right_list)
{
	if (!isEmpty())  DeleteAll();

	Node<T>* ptr = right_list.Head;
	while (ptr)
	{
		insertEnd(ptr->getItem());
		ptr = ptr->getNext();
	}
	return *this;
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






template <typename T>
bool LinkedList<T>::isEmpty() const
{
	return Head == nullptr;
}


template <typename T>
bool LinkedList<T>::insertIndex(int index, const T& data)   
{
	bool validIndex = index <= itemCount + 1 && index >= 1;

	if (validIndex)
	{
		Node<T>* ptr = Head;
		Node<T>* insert = new Node<T>(data);
		if (!insert) return false;
		
		if (index == 1)
		{
			insert->setNext(Head);
			Head = insert;
			itemCount++;
			return true;
		}

		for (int i = 2; i < index; i++)
		{
			ptr = ptr->getNext();
		}
		// Now ptr is pointing at the item after which we want to insert the data

		insert->setNext(ptr->getNext());
		ptr->setNext(insert);
		itemCount++;
		return true;
	}
	return false;
}


template <typename T>
bool LinkedList<T>::insertBeg(const T& data)
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
bool LinkedList<T>::insertEnd(const T& data)
{
	Node<T>* R = new Node<T>(data);
	if (!R) return false;   // No space in the memory
	if (!Head)
	{
		Head = R;
		Head->setNext(nullptr);
		itemCount++;
		return true;
	}
	Node<T>* p = Head;
	while (p->getNext())
		p = p->getNext();
	p->setNext(R);
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
T LinkedList<T>::getEntry(const int ind) const
{
	Node<T>* ptr = Head;

	if (!ptr) return nullptr; 

	for (int i = 1; i < ind; ++i)
		ptr = ptr->getNext();

	if (ptr)
		return ptr->getItem();

	return nullptr;
}


template <typename T>
bool LinkedList<T>::contains(T& item) const
{
	// Empty list
	if (!Head) return false;

	Node<T>* ptr = Head;
	while (ptr)
	{
		if (ptr->getItem() == item)
			return true;
		ptr = ptr->getNext();
	}

	return false;
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