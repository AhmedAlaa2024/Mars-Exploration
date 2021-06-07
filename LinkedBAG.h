#pragma once

#include "BagADT.h"
#include "Node.h"

template <typename T>
class LinkedBAG :
	public BagADT<T>
{
private:
	Node<T>* head;
	int itemCount;
	Node<T>* getPointerTo(const T& target) const; // Complexity = O(n)
public:
	// Zero Argument Default Constructor
	LinkedBAG();

	// Copy Constructor
	LinkedBAG(LinkedBAG<T>&); // Complexity = O(n)

	// BAG Specified Member Functions
	int getCurrentSize() const; // Complexity = O(1)
	bool isEmpty() const; // Complexity = O(1)
	bool add(const T&); // Complexity = O(1)
	bool remove(const T&); // Complexity = O(n)
	bool clear(); // Complexity = O(n)
	int getFrequencyOf(const T&) const; // Complexity = O(n)
	bool contains(const T&) const; // Complexity = O(n)

	// Destructor
	~LinkedBAG();
};

template <typename T>
Node<T>* LinkedBAG<T>::getPointerTo(const T& target) const {
	Node<T>* ptr = head;
	while (ptr) {
		if (ptr->getItem() == target)
			return ptr;
		ptr = ptr->getNext();
	}
	return nullptr;
}

template <typename T>
LinkedBAG<T>::LinkedBAG() {
	head = nullptr;
	itemCount = 0;
}

template <typename T>
LinkedBAG<T>::LinkedBAG(LinkedBAG<T>& LB) {
	Node<T>* ptr = LB.head;
	if (!ptr)
		return;

	do {
		add(ptr->getItem());
		ptr = ptr->getNext();
	} while (ptr);
}

template <typename T>
bool LinkedBAG<T>::add(const T& newEntry) {
	Node<T>* newNodePtr = new Node<T>(newEntry, head);
	head = newNodePtr;
	itemCount++;
	return true;
}

template <typename T>
int LinkedBAG<T>::getCurrentSize() const {
	return itemCount;
}

template <typename T>
bool LinkedBAG<T>::isEmpty() const {
	return (head == nullptr);
}

template <typename T>
bool LinkedBAG<T>::remove(const T& entry) {
	Node<T>* entryNodePtr = getPointerTo(entry);
	bool canRemoveItem = !isEmpty() && (entryNodePtr != nullptr);
	if (canRemoveItem)
	{
		entryNodePtr->setItem(head->getItem());
		Node<T>* nodeToDeletePtr = head;
		head = head->getNext();
		delete nodeToDeletePtr;
		nodeToDeletePtr = nullptr;
		itemCount--;
	}
	return canRemoveItem;
}

template <typename T>
bool LinkedBAG<T>::clear() {
	Node<T>* nodeToDeletePtr = head;
	while (nodeToDeletePtr) {
		head = head->getNext();
		nodeToDeletePtr->setNext(nullptr);
		delete nodeToDeletePtr;
		nodeToDeletePtr = head;
	}

	itemCount = 0;
	return true;
}

template <typename T>
int LinkedBAG<T>::getFrequencyOf(const T& entry) const {
	int frequency = 0;
	Node<T>* ptr = head;
	while (ptr)
	{
		if (entry == ptr->getItem())
			frequency++;

		ptr = ptr->getNext();
	}

	return frequency;
}

template <typename T>
bool LinkedBAG<T>::contains(const T& entry) const {
	return (getPointerTo(entry) != nullptr);
}

template <typename T>
LinkedBAG<T>::~LinkedBAG() {
	clear();
}