#pragma once
#include <iostream>
#include <fstream>
#include <string>

using namespace std;



//input map data
//enter start and end points
//algorithm, priority queue, heuristics
//shortest path
//output the path on the map

//const int INF = 99999;



struct Node
{
	
	int x, y;
	char type;

	int priority;
	
	struct Node *next;
};



class PriorityQueue
{
	Node *k;

public:

	PriorityQueue()
	{

		k = NULL;
	}

	void push(Node *point, int p)
	{
		Node *n, *m;
		n = new Node;
		n->priority = p;
		if (k == NULL || p < k->priority)
		{
			n->next = k;
			k = n;
		}
		else
		{
			m = k;
			while (m->next != NULL && m->next->priority <= p)
				m = m->next;
			n->next = m->next;
			m->next = n;
		}
	}

	Node pop()
	{
		Node *n;
		if (k == NULL)
			cout << "Queue underflow\n";
		else
		{
			n = k;
			k = k->next;
			return *n;
		}
	}

	bool is_empty()
	{
		Node *p;
		p = k;
		if (k == NULL) { return true; }
	}
};



void input_data()
{
	int width,
		height,
		map_area;

	ifstream inFile("input.txt");
	if (!inFile.is_open()) { cout << "Error. Cannot open file\n"; return; }

	inFile >> width >> height;
	map_area = width * height;
	Node *point = new Node[map_area];

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			char node;
			inFile >> node;
			cout << node;//

			point[(i * height) + j] = { j + 1, i + 1, node };
		}
		cout << "\n";//
	}

	for (int i = 0; i < map_area; i++)//
	{
		cout << point[i].x << "\t";
		cout << point[i].y << "\t";
		cout << point[i].type << endl;
	}
}



void enter_points()
{
	Node start,
		finish;

	// 2 7
	cout << "\nEnter start point coordinates:" << endl;
	cout << "\nx= "; cin >> start.x;
	cout << "\ny= "; cin >> start.y;

	// 7 2
	cout << "\nEnter finish point coordinates:" << endl;
	cout << "\nx= "; cin >> finish.x;
	cout << "\ny= "; cin >> finish.y;
}



