#include <iostream>
#include "CheckerBoard.h"

CheckerBoard::CheckerBoard() : xStart(0), yStart(0), tileSize(90) {}

CheckerBoard::CheckerBoard(int x, int y, int tileSize) : xStart(x), yStart(y), tileSize(tileSize) {}

CheckerBoard::~CheckerBoard() {}

void CheckerBoard::drawBoard(sf::RenderWindow &window, std::set< std::pair<int, int> > visited)
{
    sf::RectangleShape tile(sf::Vector2f(this->tileSize, this->tileSize));
    tile.setFillColor(sf::Color::White);

    for (int i = 0; i < this->myKnight.getBoardSize() ; ++i) {
        for (int j = 0; j < this->myKnight.getBoardSize() ; ++j) {
            if ((i + j) % 2 == 0) 
            {
                tile.setPosition(i * this->tileSize, j * this->tileSize);
                window.draw(tile);
            }

            std::pair<int, int> selectPoint = {i, j};
            if (visited.find(selectPoint) != visited.end())
                {
                    float circleRadius = this->tileSize / 3.0f;

                    sf::CircleShape circle(circleRadius);
                    circle.setFillColor(sf::Color::Green);
                    circle.setPosition(i * this->tileSize + this->tileSize / 2 - circleRadius, j * this->tileSize + this->tileSize / 2 - circleRadius);
                    window.draw(circle);

                    sf::Text orderText;
                    sf::Font font;
                    if (!font.loadFromFile("media/Roboto-Medium.ttf")) {
                        std::cerr << "Failed to load font!" << std::endl;
                        return;
                    }

                    orderText.setFont(font);
                    orderText.setString(std::to_string(this->myKnight.getBoardWeight(i, j)));
                    orderText.setCharacterSize(40);
                    orderText.setFillColor(sf::Color::Black);

                    sf::FloatRect textRect = orderText.getLocalBounds();
                    orderText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);

                    orderText.setPosition(i * this->tileSize + this->tileSize / 2, j * this->tileSize + this->tileSize / 2);
                    window.draw(orderText);
                }
        }
    }
}

void CheckerBoard::drawKnight(sf::RenderWindow &window, int x, int y)
{
    sf::Texture texture;
    if (!texture.loadFromFile("media/character.png")) {
        std::cerr << "Failed to load image file!" << std::endl;
        return;
    }

    sf::Sprite knightSprite(texture);
    knightSprite.setScale(this->tileSize / knightSprite.getLocalBounds().width,
                         this->tileSize / knightSprite.getLocalBounds().height);
    knightSprite.setPosition(x * this->tileSize, y * this->tileSize);
    window.draw(knightSprite);
}

void CheckerBoard::drawLines(sf::RenderWindow &window, sf::VertexArray &lines, std::vector <std::vector <int> > &singlePath)
{
    for (int i = 1; i < singlePath.size(); i++)
    {
        int startX = singlePath[i - 1][0] * this->tileSize + this->tileSize / 2;
        int startY = singlePath[i - 1][1] * this->tileSize + this->tileSize / 2;
        int endX = singlePath[i][0] * this->tileSize + this->tileSize / 2;
        int endY = singlePath[i][1] * this->tileSize + this->tileSize / 2;

        lines.append(sf::Vertex(sf::Vector2f(endX, endY), sf::Color::Blue));
        lines.append(sf::Vertex(sf::Vector2f(startX, startY), sf::Color::Blue));
    }

    window.draw(lines);
}

void CheckerBoard::draw()
{
    this->myKnight.setCoord(this->xStart, this->yStart);

    std::cout << "[INFO] Find Solution..." << std::endl;
    
    bool existResult = this->myKnight.backtracking();

    if (existResult)
    {
        this->myKnight.showBoardOnTerminal();
    }
    else
    {
        std::cout << "[FAIL] No solution found!" << std::endl;
        return;
    }

    sf::RenderWindow window(
        sf::VideoMode(
            this->myKnight.getBoardSize() * tileSize, 
            this->myKnight.getBoardSize() * tileSize
            ), 
        "Knight's Tour");


    std::vector<std::vector<int>> traversalOrder = this->myKnight.exportTraversalOrder();
    sf::VertexArray lines(sf::Lines);
    std::set< std::pair<int, int> > visited;

    std::cout << "Press Q to exit\n";

    while (window.isOpen())
    {
        // Inititalize Board, Knight coordinates
        this->drawBoard(window, visited);
        this->drawKnight(window, this->xStart, this->yStart);

        // Visited first point
        std::pair<int, int> initPoint = {this->xStart, this->yStart};
        visited.insert(initPoint);

        window.display();
        sf::sleep(sf::milliseconds(1000));

        for (int i = 1; i < traversalOrder.size(); i++)
        {
            // Handle keyboard event
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    window.close();
                    exit(EXIT_SUCCESS);
                }

                if (event.type == sf::Event::KeyReleased)
                {
                    if (event.key.code == sf::Keyboard::Q)
                    {
                        window.close();
                        exit(EXIT_SUCCESS);
                    }
                }
            }

            // Draw checker board, knight, arrows, marker
            window.clear();
            std::vector <std::vector <int> > singlePath = sliceVector(traversalOrder, i-1, i);
            std::pair<int, int> selectPoint = {traversalOrder[i][0], traversalOrder[i][1]};

            drawBoard(window, visited);
            drawLines(window, lines, singlePath);
            drawKnight(window, singlePath[1][0], singlePath[1][1]);

            visited.insert(selectPoint);
            sf::sleep(sf::milliseconds(500));
            window.display();
        }
        lines.clear();
        visited.clear();
        window.clear();
        sf::sleep(sf::milliseconds(1000));
    }
}

std::vector< std::vector <int> > sliceVector(
    std::vector< std::vector<int> > vec,
    int begin_idx, 
    int end_idx
    )
{
    auto start = vec.begin() + begin_idx;
    auto end = vec.begin() + end_idx + 1;

    std::vector < std::vector<int> > result(end_idx - begin_idx + 1);

    copy(start, end, result.begin());

    return result;
}