#include "function.h"


#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;



//input map data
//enter start and end points
//algorithm, priority queue, heuristics
//output the shortest path on the map

//extern int map_area;

const int INF = 999;

struct Node
{

	int x, y;
	char type;// = '#';

	int priority;

	int distance_total;

	bool visited;

	Node *q_next;
};


void AStar(Node*, Node, Node*);


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
		//Node *n = new Node;
		Node *m;
		n->priority = p;

		if (k == NULL || p < k->priority)
		{
			n->q_next = k;
			k = n;
		}

		else
		{
			m = k;

			while (m->q_next != NULL && m->q_next->priority <= p)
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
		Node *p;
		p = k;

		if (k == NULL)
		{
			cout << "\nQueue is empty\n" << endl;
			return true;
		}

		else 
		{
			cout << "\nQueue is not empty\n";//<<<<<<<
			return false;
		}
	}
};



int main()
{
	int width,
		height,
		area;

	ifstream inFile("input.txt");
	if (!inFile.is_open()) { cout << "Error. Cannot open file\n"; }

	inFile >> width >> height;
	area = width * height;
	//map_area = area;

	Node *point = new Node[area];

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			char node;
			inFile >> node;
			cout << node;//

			point[(i * height) + j] = { j + 1, i + 1, node };
			//point[(i * height) + j]->x = j + 1;
			//point[(i * height) + j]->y = i + 1;
			//point[(i * height) + j]->type = node;
		}
		cout << "\n";//
	}

	inFile.close();
	for (int i = 0; i < area; i++)//
	{
		cout << point[i].x << "\t";
		cout << point[i].y << "\t";
		cout << point[i].type << endl;
	}

	Node start,
		finish;
	Node *pstart = &start;

	// 2 7
	//cout << "\nEnter start point coordinates:" << endl;
	//cout << "\nx= "; cin >> start.x;
	//cout << "\ny= "; cin >> start.y;
	start.x = 2; start.y = 7;

	for (int i = 0; i < area; i++)
	{
		if (point[i].x == start.x && point[i].y == start.y)
		{
			start.type = point[i].type;
		}
	}

	// 7 2
	//cout << "\nEnter finish point coordinates:" << endl;
	//cout << "\nx= "; cin >> finish.x;
	//cout << "\ny= "; cin >> finish.y;
	finish.x = 7; finish.y = 2;

	for (int i = 0; i < area; i++)
	{
		if (point[i].x == finish.x && point[i].y == finish.y)
		{
			finish.type = point[i].type;
		}
	}


	AStar(pstart, finish, point);

	return 0;
	
}



vector<Node> Neighbors(Node current, Node *point, vector<Node> &visitedPoint)
{
	vector<Node> neighborsOpen;

	Node directions[4] = { Node{ 1, 0 }, Node{ 0, 1 }, Node{ -1, 0 }, Node{ 0, -1 } };

	//  { Node{ 1, 0 }, Node{ 0, -1 }, Node{ -1, 0 }, Node{ 0, 1 } };
	//  { Node{ 1, 0 }, Node{ 0, 1 }, Node{ -1, 0 }, Node{ 0, -1 } };

	for (Node direction : directions)
	{
		Node next{ current.x + direction.x, current.y + direction.y };


		for (int i = 0; i < sizeof(point) * sizeof(point); i++)
		{
			if (next.x == point[i].x && next.y == point[i].y)
			{
				next.type = point[i].type;
			}
		}

		if (next.type == '.')
		{
			for (int i = 0; i < visitedPoint.size()-1; i++)
			{
				if (next.x == visitedPoint[i].x && next.y == visitedPoint[i].y && visitedPoint[i].visited == true)
				{
					next.visited = true;
					break;
				}
			}
			if (next.visited == true) {continue;}
			next.distance_total = INF;
			//next.visited = false;
			
			neighborsOpen.push_back(next);
		}
	}
	return neighborsOpen;
}



int Heuristics(Node next, Node finish)
{
	return abs(next.x - finish.x) + abs(next.y - finish.y);
}



void AStar (Node *start, Node finish, Node *point)
{
	vector<Node> visitedPoint;
	PriorityQueue queue;
	
	queue.push(start, 0);

	start->distance_total = 0;

	int i = 0;
	while (!queue.is_empty() && i<30)
	{
		i++;
		Node current = queue.pop();

		current.visited = true;
		visitedPoint.push_back(current);

		if (current.x == finish.x && current.y == finish.y) { break;}

		cout << "\nCurrent  " << current.x << "\t" << current.y << "\t" << current.type << "\t" << current.visited << "\n" << endl;

		for (Node next : Neighbors(current, point, visitedPoint))
		{
			cout << "Neighbor " << next.x << "\t" << next.y << "\t" << next.type << "\t" << next.visited << endl;
			
			//if (next.visited = true) { continue;}

			//next.visited = true;
			Node *pnext = &next;
			Node *pcurrent = &current;

			int distance_new = current.distance_total + 1;
			
			
			if (next.distance_total == INF || distance_new < next.distance_total)
			//if(distance_new < INF)
			{
				pnext->distance_total = distance_new;
				int priority = distance_new + Heuristics(next, finish);
				cout << "    ===\n";
				
				//pnext->visited = true;
				queue.push(pnext, priority);
			}
		}
	}

	//for (int i = 0; i < visitedPoint.size() - 1; i++) { cout << visitedPoint[i].x << visitedPoint[i].y << visitedPoint[i].type << endl; }

	char path[26];
	for (i = 0; i < 26; i++)
	{
		path[i] = i + 97;
	}

	for (int k = 0; k < visitedPoint.size() - 1; k++)
	{
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				if (j+1 == visitedPoint[k].x && i+1 == visitedPoint[k].y && visitedPoint[k].visited == true)
				{
					point[(i * 8) + j].type = path[k];
				}
			}
		}

	}
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			
			cout << point[(i * 8) + j].type;
		}
		cout << "\n";
	}
}
