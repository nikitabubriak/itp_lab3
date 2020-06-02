#include "function.h"

using namespace std;



void Input_data()
{
	ifstream inFile("input.txt");
	if (!inFile.is_open()) { cout << "Error. Cannot open file\n"; return; }

	inFile >> width >> height;
	area = width * height;

	cout << "Map:\n\n";

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			char node;
			inFile >> node;
			cout << node << " ";

			point[(i * height) + j] = { j + 1, i + 1, node };
		}
		cout << "\n";
	}

	inFile.close();
}



void Set_coordinates()
{
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

	//cout << "\nEnter finish point coordinates:" << endl;
	//cout << "\nx= "; cin >> finish.x;
	//cout << "\ny= "; cin >> finish.y;
	finish.x = 7; finish.y = 2;

	for (int i = 0; i < width * height; i++)
	{
		if (point[i].x == finish.x && point[i].y == finish.y)
		{
			finish.type = point[i].type;
		}
	}

	cout << "\nStart>    x= " << start.x << "\ty= " << start.y << endl;
	cout << "\nFinish>   x= " << finish.x << "\ty= " << finish.y << "\n\n\n Finding path...\n\n" << endl;
}



vector<Node> Neighbors(Node current, Node *point, vector<Node> visitedPoint)
{
	vector<Node> neighborsOpen;

	for (Node direction : directions)
	{
		Node next{ current.x + direction.x, current.y + direction.y };

		for (int i = 0; i < area; i++)
		{
			if (next.x == point[i].x && next.y == point[i].y)
			{
				next.type = point[i].type;
			}
		}

		if (next.type == '.')
		{
			for (int i = 0; i < visitedPoint.size(); i++)
			{
				if (next.x == visitedPoint[i].x && next.y == visitedPoint[i].y && visitedPoint[i].visited == true)
				{
					next.visited = true;
					break;
				}
			}

			if (next.visited == true) { continue; }
			next.distance_total = INF;

			neighborsOpen.push_back(next);
		}
	}

	return neighborsOpen;
}



int Heuristics(Node next, Node finish)
{
	return abs(next.x - finish.x) + abs(next.y - finish.y);
}



vector<Node> AStar(Node *start, Node finish, Node *point)
{
	vector<Node> visitedPoint;
	PriorityQueue queue;

	queue.push(start, 0);

	start->distance_total = 0;

	while (!queue.is_empty())
	{
		Node current = queue.pop();

		current.visited = true;
		visitedPoint.push_back(current);

		if (current.x == finish.x && current.y == finish.y) { cout << "\nReached finish point\n" << endl; break; }

		cout << "\nCurrent>  " << current.x << "\t" << current.y << "\t" << current.type << "\t" << current.visited << "\n" << endl;

		for (Node next : Neighbors(current, point, visitedPoint))
		{
			cout << "Neighbor> " << next.x << "\t" << next.y << "\t" << next.type << "\t" << next.visited << endl;

			Node *pnext = &next;

			int distance_new = current.distance_total + 1;

			if (next.distance_total == INF)
			{
				pnext->distance_total = distance_new;
				int npriority = distance_new + Heuristics(next, finish);
				cout << "---------\n\n";

				queue.push(pnext, npriority);
			}
		}
	}

	return visitedPoint;
}



void Draw_path(vector<Node> visited)
{
	char path[26];

	for (int i = 0; i < 26; i++)
	{
		path[i] = i + 97;
	}

	for (int k = 0; k < visited.size(); k++)
	{
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				if (j + 1 == visited[k].x && i + 1 == visited[k].y && visited[k].visited == true)
				{
					point[(i * height) + j].type = path[k];
				}
			}
		}
	}

	cout << "Path:\n\n";

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			cout << point[(i * height) + j].type << " ";
		}
		cout << "\n";
	}
}