#include "History.h"
#include "globals.h"
//#include "City.h"
#include <iostream>
using namespace std;

History::History(int nRows, int nCols) {
	m_nRows = nRows;
	m_nCols = nCols;
	m_r = 0;
	m_c = 0;
	//nRows = 0;
	//nCols = 0;
	int x, y;
	for (x = 0; x < m_nRows;x++)//initializes grid for history
		for (y = 0; y < m_nCols;y++)
			m_grid[x][y] = '.';

}

bool History::record(int r, int c) {
	m_r = r;
	m_c = c;
	

	if (r < 1 || c <1) //if out of bounds
		return false;
	else {
		

		switch (m_grid[r - 1][c - 1])//updates history grid to correct value
		{
		case '.': m_grid[r - 1][c - 1] = 'A'; break;
		case 'Z': break;
		default: (m_grid[r - 1][c - 1])++; break;


		}
	}return true;

}


		
		
		

	

		



void History::display() const {
	clearScreen();
    
	for (int i = 0;i < m_nRows;i++) {//outputs the history grid
		for (int j = 0;j < m_nCols;j++) {
			cout << m_grid[i][j];
			
		}
		cout<< endl;
	}

	cout << endl;
	
	
}