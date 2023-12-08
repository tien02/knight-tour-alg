#ifndef CHECKERBOARD_H
#define CHECKERBOARD_H

#include <set>
#include <vector>
#include "Knight.h"
#include <SFML/Graphics.hpp>

std::vector< std::vector <int> > sliceVector(std::vector< std::vector<int> > vec, int begin_idx, int end_idx);

class CheckerBoard
{
private:
    const int xStart;
    const int yStart;
    const int tileSize;
    Knight myKnight;

    void drawBoard(sf::RenderWindow &window, std::set< std::pair<int, int> > visited); 
    void drawKnight(sf::RenderWindow &window, int x, int y);
    void drawLines(sf::RenderWindow &window, sf::VertexArray &lines, std::vector <std::vector <int> > &singlePath);

public: 
    CheckerBoard();
    CheckerBoard(int x, int y, int tileSize);
    ~CheckerBoard();
    void draw();
};

#endif // CHECKERBOARD_H