#include "provided.h"
#include "support.h"

#include <iostream>
#include <string>
using namespace std;


//helper functions for rating function in Player.cpp
bool columnCheck1( const int& winner, int col, Scaffold& s, int N) {
    int rowCount = 0;
    int count = 1;
   
    for (int i = 1; i <= s.levels() ;i++) {
        if (s.checkerAt(col, i) != VACANT) { //find exact location
            rowCount++;
        }
    }
    if (rowCount == 0)
        rowCount = 1;


    int sr = rowCount - 1;
    while (sr >= 1 && s.checkerAt(col, sr) == s.checkerAt(col, rowCount)) {
        count++;
        sr--;
    }
    //check vertically for win
    
    if (count >= N) {
        return winner == s.checkerAt(col, rowCount);

    }
    else return false;

}
bool rowCheck1( const int& winner,int col, Scaffold& s, int N)  {
    int rowCount = 0;

    int count = 1;
    for (int i = 1; i <= s.levels() ;i++) {
        if (s.checkerAt(col, i) != VACANT) { //finding exact location of last placed checker
            rowCount++;
        }
    }
    if (rowCount == 0)
        rowCount = 1;
    int sc = col - 1;
    while (sc >= 1 && s.checkerAt(col, rowCount) == s.checkerAt(sc, rowCount)) {       //checking horizontally to the left for win
        count++;
        sc--;
    }
    if (count >= N) {
        return winner == s.checkerAt(col, rowCount);
    }

     sc = col + 1;
    while (sc <= s.cols() && s.checkerAt(col, rowCount) == s.checkerAt(sc, rowCount)) {  //checking horizontally to the right for win
        count++;
        sc++;
    }
    if (count >= N) {
        return winner == s.checkerAt(col, rowCount);
    }

    return false;


}

bool diagonalCheck1( const int& winner, int col, Scaffold& s, int N)  {
    int rowCount = 0;

    int count = 1; //initialize count to one b/c one checker is always diagonal to itself
    for (int i = 1; i <= s.levels();i++)
    {
        if (s.checkerAt(col, i) != VACANT) { 
            rowCount++;
        }
    }
    if (rowCount == 0)
        rowCount = 1;

    int sr = rowCount + 1;
    int sc = col + 1;  //going to the top right
    while (sr <= s.levels() && sc <= s.cols() && s.checkerAt(sc, sr) == s.checkerAt(col, rowCount)) {
        count++;
        sr++;
        sc++;



    }
    sr = rowCount - 1;     //going to bottom left
    sc = col - 1;
    while (sr >= 1 && sc >= 1 && s.checkerAt(sc, sr) == s.checkerAt(col, rowCount)) {
        count++;
        sr--;
        sc--;
    }
    if (count >= N) {
        return winner == s.checkerAt(col, rowCount);   //top right and bottom left correspond to eachother
    }
    else {
        count = 1;
    }
    sr = rowCount + 1;
    sc = col - 1; //going to top left
    while (sr <= s.levels() && sc >= 1 && s.checkerAt(sc, sr) == s.checkerAt(col, rowCount)) {
        count++;
        sr++;
        sc--;
    }

    sr = rowCount - 1;
    sc = col + 1; //going to bottom right
    while (sr >= 1 && sc <= s.cols() && s.checkerAt(sc, sr) == s.checkerAt(col, rowCount)) {
        count++;
        sr--;
        sc++;
    }
    if (count >= N) {
        return winner == s.checkerAt(col, rowCount);   //top left and bottom right correspond to eachother
    }
    else {
        count = 1;
    }







    return false;

}

bool checkTie1(Scaffold& s)  {
    if (s.numberEmpty() == 0)
        return true;
    else
        return false;
}

