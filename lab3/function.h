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
	Node* point = new Node[map_area];
	
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



/*class PriorityQueue
{
	int data[100],
		head,
		tail;
public:
	void push(int);
	int pop();
};*/



