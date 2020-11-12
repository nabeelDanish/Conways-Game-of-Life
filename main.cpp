#include <iostream>
#include <cstdlib>
#include <fstream>
#include <Windows.h>
#include "unInit_Array.h"
#include "update.h"
using namespace std;
int main()
{
	//---------------------------------------------Preparing the Grid
	const int rows = 32;
	const int columns = 32;
	bool **grid = new bool*[rows];
	for (int i = 0; i < rows; i++)
	{	
		grid[i] = new bool[columns];
	}
	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < columns; j++)
		{
			grid[i][j] = 0;
		}
	}
	
	//--------------------------------------------Taking Input from the file
	char fileName[1000];
	cout << "Enter the name of the File" << endl;
	cin >> fileName;
	fstream inFile(fileName, ios::in);
	if (!inFile)
	{
		cout << "Error! File could not be opened" << endl;
	}
	int iteration;
	int numCells;
	inFile >> iteration >> numCells;
	unInit_array<position> cells(numCells);
	for (int i = 0; i < numCells; i++)
	{
		int x, y;
		inFile >> x >> y;
		position temp(x, y);
		cells.insertion(temp);
		grid[x][y] = 1;
	}
	inFile.close();

	//--------------------------------------------Printing on Screen
	for (int k = 0; k < iteration; ++k)
	{
		cout << "------------------------GENERATION " << k + 1 << "---------------------------" << endl;
		for (int i = 0; i < rows; ++i)
		{
			for (int j = 0; j < columns; j++)
			{
				cout << grid[i][j] << " ";
			}
			cout << endl;
		}

		//Calling our Update Function
		update(grid, cells, rows, columns);

		//Waiting for user input for next iteration
		cout << "Enter Any Key to Continue" << endl;
		int key;
		cin >> key;
	}
}