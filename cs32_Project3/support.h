#ifndef SUPPORT_H
#define SUPPORT_H
#include "provided.h"


bool columnCheck1( const int& winner, int col,Scaffold& s, int N);
bool rowCheck1( const int& winner, int col, Scaffold& s, int N);
bool diagonalCheck1(const  int& winner, int col, Scaffold& s, int N);
bool checkTie1(Scaffold& s);


#endif // !SUPPORT_H


