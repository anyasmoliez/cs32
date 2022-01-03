// Scaffold.cpp
#include <vector>
#include <stack>
#include <iostream>
#include "provided.h"
using namespace std;

class ScaffoldImpl
{
public:
    ScaffoldImpl(int nColumns, int nLevels);
    int cols() const;
    int levels() const;
    int numberEmpty() const;
    int checkerAt(int column, int level) const;
    void display() const;
    bool makeMove(int column, int color);
    int undoMove();
private:
    int m_cols;
    int m_levels;
    vector<vector<char>> grid;
    stack<int>colStack;
    stack<int>rowStack;
};

ScaffoldImpl::ScaffoldImpl(int nColumns, int nLevels)
{
    if (nColumns <= 0 || nLevels <= 0) {
        std::cerr << "Error! Columns and Levels must be positive!" << std::endl;
        exit(1);
    }
    else {
        m_cols = nColumns;
        m_levels = nLevels;
    }
    grid.resize(m_levels);  // creating the grid!
    for (int i = 0; i < m_levels; i++)
        grid[i].resize(m_cols);  
    
    for (int i = 0; i < m_levels; i++) {
        for (int j = 0; j < m_cols; j++) {
            grid[i][j] = ' ';
        }
       
       
    }
  
    
}


int ScaffoldImpl::cols() const
{
    return m_cols;
}

int ScaffoldImpl::levels() const
{
    return m_levels;
}

int ScaffoldImpl::numberEmpty() const
{
    int count = 0;
    for (int i = 0; i < m_levels; i++)
        for (int j = 0; j < m_cols; j++) {
            if (grid[i][j] ==' ')
                count++;
        }
    return count;
}

int ScaffoldImpl::checkerAt(int column, int level) const  
{
    int row = m_levels - level;  //flip row for indexing purposes. Ex: if m_level=4 and level passed in is 3, indexing is 1
    if (grid[row][column-1] == 'R')
        return RED;
    else if (grid[row][column-1] == 'B')
        return BLACK;
    else
        return VACANT;  
}

void ScaffoldImpl::display() const
{
    for (int i = 0; i < m_levels; i++) //displaying contents of grid as well as decorative additions
    {
        
        for (int j = 0; j < m_cols; j++)
        {
            if (j == 0)
                cout << '|' << grid[i][j] << '|';
            else
                cout<< grid[i][j]<<'|';
        }
       
        cout << endl;
    }
    cout << "+";
    for (int j = 0; j < m_cols; j++) {

        cout << "-+";


    }
    cout << endl;
}

bool ScaffoldImpl::makeMove(int column, int color) 
{
    if (column <= 0 || column > m_cols || (color!=RED && color!=BLACK))
        return false;
    else {
        int columnCount = column - 1;
        int rowCount =-1;
        for (int i = 0; i != m_levels;i++) {
            if (grid[i][columnCount]==' ') { //finding first legal vacant row
                
                rowCount++;
                
            }

        }
        if (rowCount == -1)
            return false;
        if ( grid[rowCount][columnCount] != 'B' && grid[rowCount][columnCount] != 'R') { //make move by changing checker at given location
            if (color == RED)
                grid[rowCount][columnCount] = 'R';

            else if (color == BLACK)
                grid[rowCount][columnCount] = 'B';

            colStack.push(column);   //storing column and level of move made in stack for later use
            rowStack.push(rowCount);
            return true;
        }
    }
   
        return false;
       
}

int ScaffoldImpl::undoMove()
{
   
  
    if (!colStack.empty() && !rowStack.empty()) {
        int c = colStack.top();   //use stacks to find location of recently placed checker
        int r = rowStack.top();

        if (grid[r][c - 1] != ' ') {
            //int c = colStack.top();


            grid[r][c - 1] = ' ';

            colStack.pop();
            rowStack.pop();
            return c;

        }
    }
    
        return 0;
        
}

//******************** Scaffold functions *******************************

//  These functions simply delegate to ScaffoldImpl's functions.
//  You probably don't want to change any of this code. 

Scaffold::Scaffold(int nColumns, int nLevels)
{
    m_impl = new ScaffoldImpl(nColumns, nLevels);
}

Scaffold::~Scaffold()
{
    delete m_impl;
}

Scaffold::Scaffold(const Scaffold& other)
{
    m_impl = new ScaffoldImpl(*other.m_impl);
}

Scaffold& Scaffold::operator=(const Scaffold& rhs)
{
    if (this != &rhs)
    {
        Scaffold temp(rhs);
        swap(m_impl, temp.m_impl);
    }
    return *this;
}

int Scaffold::cols() const
{
    return m_impl->cols();
}

int Scaffold::levels() const
{
    return m_impl->levels();
}

int Scaffold::numberEmpty() const
{
    return m_impl->numberEmpty();
}

int Scaffold::checkerAt(int column, int level) const
{
    return m_impl->checkerAt(column, level);
}

void Scaffold::display() const
{
    m_impl->display();
}

bool Scaffold::makeMove(int column, int color)
{
    return m_impl->makeMove(column, color);
}

int Scaffold::undoMove()
{
    return m_impl->undoMove();
}
