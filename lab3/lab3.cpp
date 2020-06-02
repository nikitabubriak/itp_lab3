#include "function.h"

using namespace std;



int main()
{
	Input_data();

	Set_coordinates();

	Draw_path(AStar(pstart, finish, point));

	return 0;
}