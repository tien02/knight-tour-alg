#ifndef KNIGHT_H
#define KNIGHT_H

#include <vector>

class Knight 
{
private:
    int x, y;   // coordinates
    const int BOARD_SZ = 8;   // checkerboard size
    const int movementN = 8;  // number of possible movements
    int totalMove = 1;  // total number of movements
    int xMove[8] = {-2, -2, -1, -1, 1, 1, 2, 2};    // valid x coordinate
    int yMove[8] = {-1, 1, -2, 2, -2, 2, -1, 1};    // valid y corrdinate
    std::vector< std::vector<int> > board;   // record order of traveral

public:
    Knight();
    ~Knight();
    bool isValid(int x, int y); // check if the movement is valid
    bool backtracking();    // perform backtracking

    int getX(); // get x
    int getY(); // get y
    int getBoardSize();
    int getBoardWeight(int x, int y);

    void setCoord(int xNew, int yNew);  // set x and y

    void showBoardOnTerminal(); //Show the result on terminal
    std::vector< std::vector<int> > exportTraversalOrder();
};

#endif // KNIGHT_H