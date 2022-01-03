#ifndef GAME_H
#define GAME_H

class City;

class Game
{
public:
    // Constructor/destructor
    Game(int rows, int cols, int nFlatulans);
    ~Game();

    // Mutators
    void play();

private:
    City* m_city;
};

int decodeDirection(char dir); //note: place declaration and implemenation in corresponding class, put in player?



#endif // !GAME_H

