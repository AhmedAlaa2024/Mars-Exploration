#ifndef NODE_H_
#define NODE_H_

template <typename T>
class Node
{
private:
	T item;
	Node<T>* next;
public:
	// Zero Argument Default Constructor
	Node();

	// Non-default Constructor
	Node(const T&);
	Node(const T&, Node<T>*);

	// Setters
	void setItem(const T&);
	void setNext(Node<T>*);

	// Getters
	T getItem() const;
	Node<T>* getNext() const;
};

template <typename T>
Node<T>::Node() {
	next = nullptr;
}

template <typename T>
Node<T>::Node(const T& newEntry) {
	item = newEntry;
	next = nullptr;
}

template <typename T>
Node<T>::Node(const T& newEntry, Node<T>* nextNode) {
	item = newEntry;
	next = nextNode;
}

template <typename T>
void Node<T>::setItem(const T& newEntry) {
	item = newEntry;
}

template <typename T>
void Node<T>::setNext(Node<T>* nextNode) {
	next = nextNode;
}

template <typename T>
T Node<T>::getItem() const {
	return item;
}

template <typename T>
Node<T>* Node<T>::getNext() const {
	return next;
}

#endif // !NODE_H_