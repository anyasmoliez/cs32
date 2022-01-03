#include <queue>
#include <iostream>
using namespace std;

bool pathExists(char maze[][10], int sr, int sc, int er, int ec);

class Coord
{
public:
    Coord(int r, int c) : m_row(r), m_col(c) {}
    int r() const { return m_row; }
    int c() const { return m_col; }
private:
    int m_row;
    int m_col;
};
int main()
{
    char maze[10][10] = {
        { 'X','X','X','X','X','X','X','X','X','X' },
        { 'X','.','.','.','.','X','.','.','X','X' },
        { 'X','.','X','X','.','X','X','.','.','X' },
        { 'X','X','X','.','.','.','.','X','.','X' },
        { 'X','.','X','X','X','.','X','X','X','X' },
        { 'X','.','X','.','.','.','X','.','.','X' },
        { 'X','.','.','.','X','.','X','.','.','X' },
        { 'X','X','X','X','X','.','X','.','X','X' },
        { 'X','.','.','.','.','.','.','.','.','X' },
        { 'X','X','X','X','X','X','X','X','X','X' }
    };

    if (pathExists(maze, 3, 5, 8, 8))
        cout << "Solvable!" << endl;
    else
        cout << "Out of luck!" << endl;
}


bool pathExists(char maze[][10], int sr, int sc, int er, int ec) {
    queue<Coord> coordQ;
    coordQ.push(Coord(sr, sc));
    maze[sr][sc] = 'P';
    while (!coordQ.empty()) {
        Coord top = coordQ.front();
        int r = top.r();
        int c = top.c();
        
        coordQ.pop();
        
        if (r == er && c == ec) {
            return true;
        }
        if (maze[r + 1][c] != 'X' && maze[r + 1][c] != 'P') {
            coordQ.push(Coord(r + 1, c));
            maze[r + 1][c] = 'P';
        }
        if (maze[r][c - 1] != 'X' && maze[r][c - 1] != 'P') {
            coordQ.push(Coord(r, c - 1));
            maze[r][c - 1] = 'P';
        }
        if (maze[r - 1][c] != 'X' && maze[r - 1][c] != 'P') {
            coordQ.push(Coord(r - 1, c));
            maze[r - 1][c] = 'P';
        }
        if (maze[r][c + 1] != 'X' && maze[r][c + 1] != 'P') {
            coordQ.push(Coord(r, c + 1));
            maze[r][c + 1] = 'P';
        }
    }
    return false;


}