#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

const int INF = 999;

int width,
	height,
	area;

struct Node
{

	int x, y;
	char type;

	int priority;

	int distance_total;

	bool visited;

	Node *q_next;
};



class PriorityQueue
{
	Node *k;

public:

	PriorityQueue()
	{

		k = NULL;
	}

	void push(Node *n, int p)
	{
		Node *m;
		n->priority = p;

		if (k == NULL || p > k->priority)
		{
			n->q_next = k;
			k = n;
		}

		else
		{
			m = k;

			while (m->q_next != NULL && m->q_next->priority >= p)
			{
				m = m->q_next;
			}

			n->q_next = m->q_next;
			m->q_next = n;
		}
	}

	Node pop()
	{
		Node *n;

		if (k == NULL)
		{
			n = NULL;
			cout << "\nQueue underflow\n";
			return *n;
		}

		else
		{
			n = k;
			k = k->q_next;
			return *n;
		}
	}

	bool is_empty()
	{
		Node *ptr;
		ptr = k;

		if (k == NULL)
		{
			cout << "\nQueue is empty\n" << endl;
			return true;
		}

		else
		{
			return false;
		}
	}
};



Node *point = new Node[INF];

Node start,
	finish;

Node *pstart = &start;

Node directions[4] =
{
	Node{-1, 0 }, //left
	Node{ 0, 1 }, //down
	Node{ 1, 0 }, //right
	Node{ 0,-1 }  //up
};



void Input_data();

void Set_coordinates();

vector<Node> Neighbors(Node, Node*, vector<Node>);

int Heuristics(Node, Node);

vector<Node> AStar(Node*, Node, Node*);

void Draw_path(vector<Node>);



#include "function.cpp"