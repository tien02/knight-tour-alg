#include "src/CheckerBoard.h"

int main()
{
    const int xStart = 0;
    const int yStart = 0;
    const int tileSize = 90;

    CheckerBoard board(xStart, yStart, tileSize);
    board.draw();
}