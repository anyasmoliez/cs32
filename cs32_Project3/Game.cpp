// Game.cpp
#include <vector>
#include <stack>
#include <string>
#include <iostream>
#include "provided.h"

using namespace std;


class GameImpl
{
public:
    GameImpl(int nColumns, int nLevels, int N, Player* red, Player* black);
    bool completed(int& winner) const;
    bool takeTurn();
    void play();
    int checkerAt(int c, int r) const;
private:
    int m_col;
    int m_level;
    int m_n;
    Player* m_red;
    Player* m_black;
    Scaffold s;
    //stack<int>turnStack;
    int color;
    int last_col;
    Player* player;
    bool columnCheck( const int& winner) const;
    bool rowCheck( const int& winner) const;
    bool diagonalCheck(const int& winner) const;
    bool checkTie() const;
   
    
};

GameImpl::GameImpl(int nColumns, int nLevels, int N, Player* red, Player* black):s(nColumns,nLevels), m_red(red),player(m_red)
{
    m_col = nColumns;
    m_level = nLevels;
    m_n = N;
    
    m_black = black;
    color = RED;
    //player = m_red;
    last_col = 1;
    
    

}

bool GameImpl::completed(int& winner) const  //uses helper functions to check if game has been won/tied
{
  
    if (columnCheck(RED)) {
        winner = RED;
        return true;
    }
    else if (columnCheck(BLACK)) {
        winner = BLACK;
        return true;
    }
    else if (rowCheck(BLACK)) {
        winner = BLACK;
        return true;
    }
    else if (rowCheck(RED)) {
        winner = RED;
        return true;
    }
    else if (diagonalCheck(RED)) {
        winner = RED;
        return true;
    }
    else if (diagonalCheck(BLACK)) {
        winner = BLACK;
        return true;
    }
    else if (checkTie()) {
        winner = TIE_GAME;
        return true;
    }
    
    
    return false;
}
bool GameImpl::columnCheck( const int& winner) const {
    int rowCount = 0;

    int rCount = 0;
    int bCount = 0;
    for (int i = 1; i <= s.levels() && (bCount < m_n || rCount < m_n);i++) {
        if (s.checkerAt(last_col, i) != VACANT) { //finding exact location of recently placed checker
            rowCount++;
        }
    }
    if (rowCount == 0)
        rowCount = 1;

    //check vertically downwards
    for (int i = rowCount; i != 0;i--) {

        if (s.checkerAt(last_col, i) == RED && s.checkerAt(last_col, rowCount) == RED) //checking that next checker is same as recently placed checker
            rCount++;
        else if (s.checkerAt(last_col, i) == BLACK && s.checkerAt(last_col, rowCount) == BLACK)
            bCount++;
        else
            break;

    }
    if (rCount == m_n) {
        
        return winner == RED;
    }
    if (bCount == m_n) {
        
        return winner == BLACK;
    }
    else return false;

}
bool GameImpl::rowCheck( const int& winner) const { //checking horizontal wins
    int rowCount = 0;

    int rCount = 0;
    int bCount = 0;
    for (int i = 1; i <= s.levels() && (bCount < m_n || rCount < m_n);i++) {
        if (s.checkerAt(last_col, i) != VACANT) { //finding row location
            rowCount++;
        }
    }
    if (rowCount == 0)
        rowCount = 1;
    for (int i = last_col;i >= 1;i--)  //iterate to the left in that row
    {
        if (s.checkerAt(i, rowCount) == RED && s.checkerAt(last_col, rowCount) == RED) { //checking that next checker is same as recently placed checker
            rCount++;

        }
        else if (s.checkerAt(i, rowCount) == BLACK && s.checkerAt(last_col, rowCount) == BLACK) {
            bCount++;

        }
        else
            break;
    }
    for (int j = last_col + 1;j <= s.cols();j++) {   //iterate to the right in that row
        if (s.checkerAt(j, rowCount) == RED && s.checkerAt(last_col, rowCount) == RED) {
            rCount++;

        }
        else if (s.checkerAt(j, rowCount) == BLACK && s.checkerAt(last_col, rowCount) == BLACK) {
            bCount++;

        }
        else
            break;

    }
    if (rCount >= m_n) {
        
        return winner == RED;
    }
    if (bCount >= m_n) {
        
        return winner == BLACK;
    }
    else
        return false;

}
bool GameImpl::diagonalCheck(const int& winner) const {
    int rowCount = 0;

    int count=1; //initialize count to one b/c one checker is always diagonal to itself
    for (int i = 1; i <= s.levels();i++)
    {
        if (s.checkerAt(last_col, i) != VACANT) { //finding current location
            rowCount++;
        }
    }
    if (rowCount == 0)
        rowCount = 1;

    int sr = rowCount + 1;
    int sc = last_col + 1;  //going to the top right
    while (sr <= s.levels() && sc <= s.cols() && s.checkerAt(sc, sr) == s.checkerAt(last_col, rowCount)) {
            count++;
            sr++;
            sc++;
            
   
        
    }
     sr = rowCount - 1;     //going to bottom left
     sc = last_col - 1;
    while (sr >= 1 && sc >= 1 && s.checkerAt(sc, sr) == s.checkerAt(last_col, rowCount)) {
        count++;
        sr--;
        sc--;
    }
    if (count >= m_n) {
        return winner == s.checkerAt(last_col, rowCount);   //bottom left diagonal and top right diagonal correspond to eachother
    }
    else {
        count = 1;
    }
     sr = rowCount + 1;
     sc = last_col - 1; //going to top left
     while (sr <= s.levels() && sc >= 1 && s.checkerAt(sc, sr) == s.checkerAt(last_col, rowCount)) {
         count++;
         sr++;
         sc--;
     }

     sr = rowCount - 1;
     sc = last_col + 1; //going to bottom right
     while (sr >= 1 && sc <= s.cols() && s.checkerAt(sc, sr) == s.checkerAt(last_col, rowCount)) {
         count++;
         sr--;
         sc++;
     }
     if (count >= m_n) {
         return winner == s.checkerAt(last_col, rowCount);  //bottom right and top left diagonal correspond to each other
     }
     else {
         count = 1;
     }



    
    
    
    
        return false;

}

bool GameImpl::checkTie() const { //if board is full, game is a tie
    for (int i=1;i<=s.levels();i++)
        for (int j = 1;j <= s.cols();j++) {
            if (s.checkerAt(j, i) != VACANT)
                continue;
            else
                return false;
        }
    return true;
}

bool GameImpl::takeTurn() 
{
    
    int winner;
    if (color==RED && !completed(winner)) { 
        
        
        last_col= m_red->chooseMove(s, m_n, RED); //storing location of last placed checker
        s.makeMove(last_col, RED);
        player = m_black;
        color = BLACK;                //change so that next turn is BLACK
        return true;

    }
    else if (color==BLACK && !completed(winner)) {
        
        
        last_col= m_black->chooseMove(s, m_n, BLACK);     //storing location of last placed checker
        s.makeMove(last_col, BLACK);
        player = m_red;
        color = RED;                                     //change so that next turn is RED
        return true;
    }
    else
        return false;
   
    
}

void GameImpl::play()
{
    int winner;
    s.display();
    while (!completed(winner)) {   //while game is not over, take alternating turns
        takeTurn();
        s.display();
        if (!player->isInteractive()) {
            cout << "Press enter to continue." << endl;
            cin.ignore(10000, '\n');
        }
    }
    if (winner == BLACK)
        cout << "The winner is: BLACK" << endl;
    else if (winner == RED)
        cout << "The winner is: RED" << endl;
    else if (winner == TIE_GAME)
        cout << "The winner is: TIE GAME" << endl;
}

int GameImpl::checkerAt(int c, int r) const
{
    return s.checkerAt(c, r);
}

//******************** Game functions *******************************

//  These functions simply delegate to GameImpl's functions.
//  You probably don't want to change any of this code. 

Game::Game(int nColumns, int nLevels, int N, Player* red, Player* black)
{
    m_impl = new GameImpl(nColumns, nLevels, N, red, black);
}

Game::~Game()
{
    delete m_impl;
}

bool Game::completed(int& winner) const
{
    return m_impl->completed(winner);
}

bool Game::takeTurn()
{
    return m_impl->takeTurn();
}

void Game::play()
{
    m_impl->play();
}

int Game::checkerAt(int c, int r) const
{
    return m_impl->checkerAt(c, r);
}
