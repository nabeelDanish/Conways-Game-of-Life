#ifndef UPDATE_H
#define UPDATE_H
#include "unInit_Array.h"
#include <iostream>
#include <fstream>
using namespace std;

//The Main Update Function, Takes Arguments as the 2D array of the Grid, the List of Cells

//The List of Cells is passed by reference, as the values are changed 
//The size of the Grid is also passed to make sure the Cells values donot go out of bound

void update(bool **grid, unInit_array<position>& cells, int rows, int columns)
{
	//The Aux Array holds all the Neighbours of the Living Cells
	unInit_array<position> aux_array(cells.count * 8);

	//Initializing the Offset array, allows for computing of neighbours easily
	int offset[][2] = { {-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1} };


	//-----------------------------------------Adding Neighbours
	for (int i = 0; i < cells.count; i++)
	{
		int x, y;
		x = cells[i].x;
		y = cells[i].y;
		cells[i].liveNeighbourCount = 0;
		for (int j = 0; j < 8; ++j)
		{
			int temp_x = x + offset[j][0];
			int temp_y = y + offset[j][1];
			if (((temp_x >= 0) && (temp_x < rows)) && ((temp_y >= 0) && (temp_y < columns)))
			{
				if (grid[temp_x][temp_y] == 0)
				{
					position temp(x + offset[j][0], y + offset[j][1]);
					aux_array.insertion(temp);
					//Setting the Neighbour Position to 1
					//This allows us to not add duplciate Neighbours
					grid[temp_x][temp_y] = 1;
				}
			}
		}
	}
	//Setting back the Neighbour Positon to 0
	for (int i = 0; i < aux_array.count; ++i)
	{
		grid[aux_array[i].x][aux_array[i].y] = 0;
	}
	//-----------------------------------------Counting Live Neighbours for Dead Cells
	for (int i = 0; i < aux_array.count; i++)
	{
		int x = aux_array[i].x;
		int y = aux_array[i].y;
		for (int j = 0; j < 8; ++j)
		{
			int temp_x = x + offset[j][0];
			int temp_y = y + offset[j][1];
			if (((temp_x >= 0) && (temp_x < rows)) && ((temp_y >= 0) && (temp_y < columns)))
			{
				if (grid[temp_x][temp_y] == 1)
				{
					++aux_array[i].liveNeighbourCount;
				}
			}
		}
	}
	//-----------------------------------------Counting Live Neighbours for Alive Cells
	for (int i = 0; i < cells.count; i++)
	{
		int x = cells[i].x;
		int y = cells[i].y;
		for (int j = 0; j < 8; ++j)
		{
			int temp_x = x + offset[j][0];
			int temp_y = y + offset[j][1];
			if (((temp_x >= 0) && (temp_x < rows)) && ((temp_y >= 0) && (temp_y < columns)))
			{
				if (grid[temp_x][temp_y] == 1)
				{
					++cells[i].liveNeighbourCount;
				}
			}
		}
	}
	//-----------------------------------------Cell Propagation
	for (int i = 0; i < cells.count; i++)
	{
		if (cells[i].liveNeighbourCount <= 1 || cells[i].liveNeighbourCount > 3)
		{
			grid[cells[i].x][cells[i].y] = 0;
			position temp(cells[i].x, cells[i].y);
			cells.deletion(temp);
			--i;
		}
	}
	//-----------------------------------------Cell Birth
	for (int i = 0; i < aux_array.count; i++)
	{
		if (aux_array[i].liveNeighbourCount == 3)
		{
			grid[aux_array[i].x][aux_array[i].y] = 1;
			position temp(aux_array[i].x, aux_array[i].y);
			cells.insertion(temp);
		}
	}
}
#endif // !UPDATE_H
