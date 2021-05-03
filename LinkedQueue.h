/////////////////////////////// Written By: Ahmed Alaa ///////////////////////////////

#ifndef QUEUEADT_H_
#define QUEUEADT_H_
#include "QueueADT.h"
#include "Node.h"

template <typename T>
class LinkedQueue :
    public QueueADT<T>
{
private:
    Node<T>* front;
    Node<T>* back;
    int itemCount;

public:
    // Zero Argument Default Constructor
    LinkedQueue(); // Complexity = O(1)

    // Copy Constructor
    LinkedQueue(const LinkedQueue<T>&); // Complexity = O(n)
    
    // Queue Specified Member Functions
    bool isEmpty() const; // Complexity = O(1)
    bool enqueue(const T&); // Complexity = O(1)
    bool dequeue(T&); // Complexity = O(1)
    bool peek(T&); // Complexity = O(1)

    int get_itemCount();

    // Destructor
    ~LinkedQueue(); // Complexity = O(n)
};

template <typename T>
LinkedQueue<T>::LinkedQueue():itemCount(0){
    front = nullptr;
    back = nullptr;
}

template <typename T>
LinkedQueue<T>::LinkedQueue(const LinkedQueue<T> &LQ) {    //why do not you use the enqueue() member function ??????  Doaa
    Node<T>* LQptr = LQ.front;
    if (!LQptr)
    {
        front = back = nullptr;
        return;
    }

    Node<T>* ptr = new Node<T>(LQptr->getItem());
    front = back = ptr;
    LQptr = LQptr->getNext();

    while (LQptr)
    {
        Node<T>* ptr = new Node<T>(LQptr->getItem());
        back->setNext(ptr);
        back = ptr;
        LQptr = LQptr->getNext();
    }
}

template <typename T>
int LinkedQueue<T>::get_itemCount()
{
    return itemCount;
}

template <typename T>
bool LinkedQueue<T>::isEmpty() const {
    return (front == nullptr);
}


template <typename T>
bool LinkedQueue<T>::enqueue(const T& newEntry) {
    Node<T>* ptr = new Node<T>(newEntry);

    if (isEmpty())
        front = ptr;
    else
        back->setNext(ptr);

    back = ptr;
    itemCount++;
    return true;
}


template <typename T>
bool LinkedQueue<T>::dequeue(T& fEntry)
{
    if (isEmpty())
        return false;

    Node<T>* ptr = front;
    fEntry = front->getItem();
    front = front->getNext();

    if (ptr == back)    // Special Case: if there is only one node in the queue
        back = nullptr;

    delete ptr;
    itemCount--;
    return true;
}


template <typename T>
bool LinkedQueue<T>::peek(T& fEntry)
{
    if (isEmpty())
        return false;

    fEntry = front->getItem();
    return true;
}

template <typename T>
LinkedQueue<T>::~LinkedQueue() {
    T temp;

    while (dequeue(temp));
}

#endif // !QUEUEADT_H_