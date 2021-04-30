#include <iostream>


#include "LinkedPriorityQueue.h"

#include "MarsStation.h"



int main()
{
	
	MarsStation station_;
	SIM_MODE mode = station_.get_input_mode();

	station_.execute_mode(mode);

	

	//for Ahmed Atta ---> please, do not delete this large comment because i need it temporarily  

	//test the priority queue class
	//LinkedPriorityQueue<int, int> p;
	//Pair<int, int > p1(1, 2);
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


	//Pair<int, int>ps;
	//l.peek(ps);
	//l.dequeue(ps);
	//bool ispeek = l.dequeue(ps);
	//cout << ispeek << endl;
	////p.peek(ps);

	//cout << ps.getPriority() << endl;
	//cout << ps.getItem() << endl;

	//p.peek(ps);
	//cout << ps.getPriority() << endl;
	//cout << ps.getItem() << endl;


	return 0;
}


