// Player.cpp

#include "provided.h"
#include "support.h"
#include <iostream>
#include <string>
#include <vector>
#include <math.h>  
using namespace std;



class HumanPlayerImpl 
{
public:
    
    int chooseMove(const Scaffold& s, int N, int color);

    
};

class BadPlayerImpl
{
public:
   
    int chooseMove(const Scaffold& s, int N, int color);
};

class SmartPlayerImpl
{
public:
    
    int chooseMove(const Scaffold& s, int N, int color);
private:
    int rating(Scaffold& s, int column, int color, int depth, int N, bool isComputer);
    pair<int, int> determineBestMoveComp(AlarmClock& ac,Scaffold& t,int&move, int depth, int color, bool isComputer, int N);
    
    
    int other(int& color);
   
    
    
    
};




int HumanPlayerImpl::chooseMove(const Scaffold& s, int N, int color)
{
    int col=0;
    bool done = false;
    while (done == false) {  //prompt user until they choose a valid column
        cout << "Please enter a non-full column number to place your checker in: ";
        cin >> col;
        cout << endl;
        if (col <0 || col> s.cols()) {
            cout << "Invalid! Try again please." << endl;
            continue;
        }
        for (int i = s.levels();i != 0;i--) {
            if (s.checkerAt(col, i) == VACANT) {
                done = true;
                break;    //exit out of loop and return column number
            }
        }


        }
    return col;
    
    }

    
        
   






int BadPlayerImpl::chooseMove(const Scaffold& s, int N, int color)
{
     
        
            for (int j = 1; j <= s.cols();j++) {        //chooses leftmost empty column to make move in
                if (s.checkerAt(j, s.levels()) == VACANT)
                    
                    return j;

            }
    
    
        return 0;
}


int SmartPlayerImpl::chooseMove(const Scaffold& s, int N, int color)
{
    
    Scaffold m_s = s;
    AlarmClock ac(9900);
    int move;
    //int column=1;
    //vector< pair <int, int> >collection;
    
    


    
    return determineBestMoveComp(ac,m_s, move, 0, color, true, N).second;
}
pair<int, int> SmartPlayerImpl::determineBestMoveComp(AlarmClock& ac,Scaffold& t, int& move, int depth, int color, bool isComputer, int N) {

    //vector< pair <int, int> >collection;
    int n;
    int score;
    vector< pair <int, int> >collection;

    int maxDepth = t.cols() * t.levels();

    if (depth == maxDepth)

        return make_pair(2, -1);
    else if (color == RED && isComputer==true && t.numberEmpty() == t.cols() * t.levels()) { //first computer move will choose middle column
        if (t.cols() % 2 != 0) {
            n = (t.cols() + 2 - 1) / 2;
        }
        else {
            n = t.cols() / 2;
        }
        if (t.checkerAt(n, t.levels()) != VACANT) {  //if middle column is full, find a different column
            for (int j = 1;j <= t.cols();j++) {
                if (t.checkerAt(j, t.levels()) == VACANT) {
                    n = j;
                    break;
                }

            }
        }
        t.makeMove(n, RED);
        move = n;
         score = 2;
        return make_pair(score, move);
    }
    else if (color == BLACK && isComputer == true && t.numberEmpty() == t.cols() * t.levels() - 1) { //first computer move will choose middle column
        if (t.cols() % 2 != 0) {
            n = (t.cols() + 2 - 1) / 2;
        }
        else {
            n = t.cols() / 2;
        }
        if (t.checkerAt(n, t.levels()) != VACANT) { //if middle column is full find a nonempty column
            for (int j = 1;j <= t.cols();j++) {
                if (t.checkerAt(j, t.levels()) == VACANT) {
                    n = j;
                    break;
                }

            }
        }
        t.makeMove(n, BLACK);
        move = n;
        score = 2;
        return make_pair(score, move);
    }

    if (ac.timedOut())
        return make_pair(score, move);
   // cout << ac.timedOut() << endl;
    if (isComputer) {


        if (ac.timedOut()) {
            return make_pair(score, move);  //if timer runs out, return best most
        }


        for (int j = 1;j <= t.cols();j++) {

            if (t.checkerAt(j, t.levels()) == VACANT) { //loop through all available spots

                t.makeMove(j, color);

              //  t.display();
                int rate = rating(t, j, depth, color, N, isComputer);

                if (rate == 0 || rate == 512345 - depth) { //if rating indicates win or tie, remember that score and move

                    collection.push_back(make_pair(rate, j));

                }

                else {



                    pair<int, int> x = determineBestMoveComp(ac,t, move, depth + 1, other(color), !isComputer, N);  //call the human player!

                    collection.push_back(x);



                }

                t.undoMove();

            }



        }//t.undoMove();

    }



    else {

        if (ac.timedOut()) {
            return make_pair(score, move);
        }

        

            for (int j = 1;j <= t.cols();j++) {

                if (t.checkerAt(j, t.levels()) == VACANT) { //loop through all available spots

                    t.makeMove(j, color);


                   // t.display();
                    int rate = rating(t, j, depth, color, N, isComputer);

                    if (rate == 0 || rate== -512345 + depth) //if rating indicates win or tie, remember that rating and move

                    {

                        collection.push_back(make_pair(-rate, j));

                    }

                    else {

                        pair<int, int> y = determineBestMoveComp(ac,t, move, depth + 1, other(color), !isComputer, N);  //call the computer player

                        collection.push_back(y);

                    }

                    t.undoMove();

                }

            } //t.undoMove();

        



    }



    move = 0;

    int scores;



    int maxScore = -10000;

    int maxMove = 1;

    

        for (int i = 1; i != collection.size();i++) { //find the maximum score

            if (collection[i].first > maxScore) {

                maxScore = collection[i].first;

                maxMove = collection[i].second;

            }

        }

    

    move = maxMove;

    scores = maxScore;

    if (move < 1 || t.checkerAt(move, t.levels()) != VACANT) {
        for (int j = 1;j <= t.levels();j++) {
            if (t.checkerAt(j, t.levels()) == VACANT) {
                move = j;
                break;
            }
        }
    }

    




    return make_pair(score, move);



}
int SmartPlayerImpl::other(int& color) { //changes the color to its opposite
    if (color == RED)
        return BLACK;
    else
        return RED;
}


     
    
    
int SmartPlayerImpl::rating(Scaffold& s, int column, int depth, int color, int N, bool isComputer) { 
    const int bigNumber = 512345;
    
    
     if (checkTie1(s))

        return 0;
    
    else if (color == RED && isComputer==true) { //if computer move is red and win

        if ((columnCheck1(RED, column, s, N) || rowCheck1(RED, column, s, N) || diagonalCheck1(RED, column, s, N))) {
            return bigNumber - depth;
        }
    }

    else if (color == BLACK && isComputer==false) {//if human move is black and win
        if ((columnCheck1(BLACK, column, s, N) || rowCheck1(BLACK, column, s, N) || diagonalCheck1(BLACK, column, s, N)))

            return -bigNumber + depth;
    }

       
        
    
        else if (color == BLACK && isComputer==true) {//if computer move is black and win
        if ((columnCheck1(BLACK, column, s, N) || rowCheck1(BLACK, column, s, N) || diagonalCheck1(BLACK, column, s, N))) {
            return bigNumber - depth;
        }
    }
        else if (color == RED && isComputer==false) {//if human move is red and win
        if ((columnCheck1(RED, column, s, N) || rowCheck1(RED, column, s, N) || diagonalCheck1(RED, column, s, N)))
        {
            return -bigNumber + depth;
        }
    }

        
        
       
        return 2;  //neither win,loss, or tie

    
}







//******************** Player derived class functions *************************

//  These functions simply delegate to the Impl classes' functions.
//  You probably don't want to change any of this code. 

HumanPlayer::HumanPlayer(string nm)
    : Player(nm)
{
    m_impl = new HumanPlayerImpl;
}

HumanPlayer::~HumanPlayer()
{
    delete m_impl;
}

int HumanPlayer::chooseMove(const Scaffold& s, int N, int color)
{
    return m_impl->chooseMove(s, N, color);
}

BadPlayer::BadPlayer(string nm)
    : Player(nm)
{
    m_impl = new BadPlayerImpl;
}

BadPlayer::~BadPlayer()
{
    delete m_impl;
}

int BadPlayer::chooseMove(const Scaffold& s, int N, int color)
{
    return m_impl->chooseMove(s, N, color);
}

SmartPlayer::SmartPlayer(string nm)
    : Player(nm)
{
    m_impl = new SmartPlayerImpl;
}

SmartPlayer::~SmartPlayer()
{
    delete m_impl;
}

int SmartPlayer::chooseMove(const Scaffold& s, int N, int color)
{
    return m_impl->chooseMove(s, N, color);
}
