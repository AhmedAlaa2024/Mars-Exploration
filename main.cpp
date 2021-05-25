#include <iostream>


#include "LinkedPriorityQueue.h"

#include "MarsStation.h"



int main()
{
	
	MarsStation station_;
	
	
	
	/*SIM_MODE mode = station_.get_input_mode();

	station_.execute_mode(mode);*/

	

	//for Ahmed Atta ---> please, do not delete this large comment because i need it temporarily  

	//test the priority queue class
	//LinkedPriorityQueue<int, int> p;
	//Pair<int, int > p1(33, 2);
	//Pair<int, int > p2(1, 4);
	//Pair<int, int > p3(1, 5);
	//Pair<int, int > p4(1, 3);
	////Pair<int, int > p5(20, 0);
	//Pair<int, int > p5(20, 2);


	//
	//p.enqueue(p1);
	///*p.enqueue(p2);
	//p.enqueue(p3);
	//p.enqueue(p4);
	//p.enqueue(p5);*/

	////test the copy constructor
	//LinkedPriorityQueue<int, int> l = p;


	//int ps;
	//l.peek(ps);
	//int item = 0;
	//l.dequeue(item);
	//cout << item << endl;
	//bool ispeek = l.dequeue(item);


	//cout << ispeek << endl;
	////p.peek(ps);

	//cout << ps << endl;
	//

	//p.peek(ps);
	//cout << ps << endl;
	//
	//int is;
	//l.peek(is);
	//cout << is << endl;


	/*LinkedList<int> l;
	l.insert(4);
	l.insert(5);
	l.insert(6);
	l.insert(7);

	Node<int>* n = l.getNodeAt(1);
	cout << n->getItem();*/



	/*LinkedPriorityQueue<int, int> l;
	LinkedPriorityQueue<int, int> q;


	Pair<int, int> p1(3, 1);
	Pair<int, int> p2(33, 6);
	Pair<int, int> p3(8, 3);
	Pair<int, int> p4(5, 4);

	l.enqueue(p1);
	l.enqueue(p2);
	l.enqueue(p3);
	l.enqueue(p4);

	q = l;

	int temp;
	q.peek(temp);
	cout << temp;*/

	Mission* m1 = nullptr, * m2 = nullptr, * m3 = nullptr;
	m1 = new Mission;
	m2 = new Mission;
	m3 = new Mission;
	m1->setED(10);
	m2->setED(3);
	m3->setED(4);
	m1->setWD(3);
	m2->setWD(4);
	m3->setWD(0);
	m1->setFD(1);
	m2->setFD(5);
	m3->setFD(7);
	m1->setID(1);
	m2->setID(2);
	m3->setID(3);
	m1->setCD();
	m2->setCD();
	m3->setCD();
	station_.setCompletedMission(m1);
	station_.setCompletedMission(m2);
	station_.setCompletedMission(m3);
	station_.SortCompletedList();
	LinkedList<Mission*> list = station_.get_completed_missions_();
	int count = list.getItemCount();
	for (int i = 1; i <= count; i++)
	{
		cout << list.getEntry(i)->getID() << ", " << list.getEntry(i)->getCD() << endl;
	}
	return 0;
}


