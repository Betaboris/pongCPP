#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

const int WINDOW_HEIGHT = 800; //Lös detta på ett bättre sätt sen
const int WINDOW_WIDTH = 1000; //Lös detta på ett bättre sätt sen
const int DISTANCE_TO_BORDER = 30;
sf::Vector2f PLAYER_DIMENSIONS(50, 300);

class Player 
{

public:
    sf::Vector2f pos;
    sf::RectangleShape body;

    Player(int defaultX) : 
    pos(defaultX, (WINDOW_HEIGHT / 2) - (PLAYER_DIMENSIONS.y / 2)),
    body()
    {
        body.setSize(PLAYER_DIMENSIONS);
        body.setPosition(pos);
    }

};

int main()
{

    std::vector<Player> players;
    Player pLeft(DISTANCE_TO_BORDER);
    Player pRight(WINDOW_WIDTH - (DISTANCE_TO_BORDER + PLAYER_DIMENSIONS.x));
    players.push_back(pLeft);
    players.push_back(pRight);

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML works!");
    // sf::RectangleShape playerOne(sf::Vector2f(100, 300));
    // playerOne.setFillColor(sf::Color::Blue);
    // playerOne.setPosition(300, 300);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        for (auto& player : players) {
            window.draw(player.body);
        }
        window.display();
    }

    return 0;
}
