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

	return 0;
}


