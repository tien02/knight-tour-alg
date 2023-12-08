#include "Knight.h"
#include <iostream>
#include <iomanip>

Knight::Knight() : board(this->BOARD_SZ, std::vector<int>(this->BOARD_SZ, -1)) {}

Knight::~Knight() {}

void Knight::setCoord(int xNew, int yNew) {
    this->x = xNew;
    this->y = yNew;
    this->board[xNew][yNew] = this->totalMove;
}

int Knight::getX() {
    return this->x;
}

int Knight::getY() {
    return this->y;
}

bool Knight::isValid(int x, int y) {
    return x >= 0 && y >= 0 && x < this->BOARD_SZ && y < this->BOARD_SZ && this->board[x][y] == -1;
}

int Knight::getBoardSize()
{
    return this->BOARD_SZ;
}

bool Knight::backtracking() 
{
    if (this->totalMove == this->BOARD_SZ * this->BOARD_SZ) {
        return true;
    }

    for (int i = 0; i < this->movementN; i++) {
        int xNext = this->getX() + this->xMove[i];
        int yNext = this->getY() + this->yMove[i];

        if (this->isValid(xNext, yNext)) 
        {
            this->setCoord(xNext, yNext);
            this->board[xNext][yNext] = this->totalMove + 1;
            this->totalMove += 1;

            if (this->backtracking()) {
                return true;
            }

            this->board[xNext][yNext] = -1;
            this->totalMove -= 1;
            this->setCoord(xNext - this->xMove[i], yNext - this->yMove[i]);
        }
    }

    return false;
}

void Knight::showBoardOnTerminal()
{
    for (auto rows:this->board)
    {
        for (auto cols:rows)
        {
            std::cout << std::setw(3) << cols;
        }
        std::cout << "\n";
    }
}

int Knight::getBoardWeight(int x, int y)
{
    return board[x][y];
}

std::vector< std::vector<int> > Knight::exportTraversalOrder()
{
    std::vector< std::vector<int> > visitedOrder(this->BOARD_SZ*this->BOARD_SZ);

    for (int i = 0 ; i < this->BOARD_SZ; i++)
    {
        for (int j = 0; j < this->BOARD_SZ; j++)
        {
            visitedOrder[board[i][j]-1].push_back(i);
            visitedOrder[board[i][j]-1].push_back(j);
        }
    }

    return visitedOrder;
}