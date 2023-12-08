#include <iostream>
#include "src/CheckerBoard.h"

int main()
{   
    const int tileSize = 90;

    int x, y;
    std::cin >> x >> y;

    const int xStart = x;
    const int yStart = y;

    CheckerBoard board(xStart, yStart, tileSize);
    board.draw();
}