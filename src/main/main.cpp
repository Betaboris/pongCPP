#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "../constants/constants.hpp"
#include "../entities/Entity.hpp"
#include "../entities/Player.hpp"
#include "../entities/Ball.hpp"
#include "../utils/utils.hpp"


int main()
{
    std::vector<Entity*> enteties;
    Ball ball;
    Player::balls.push_back(&ball);
    Player pLeft(DISTANCE_TO_BORDER, playerKeyBindings(sf::Keyboard::Key::W, sf::Keyboard::Key::S));
    Player pRight(WINDOW_WIDTH - (DISTANCE_TO_BORDER + PLAYER_DIMENSIONS.x), playerKeyBindings(sf::Keyboard::Key::Up, sf::Keyboard::Key::Down));

    enteties.push_back(&pLeft);
    enteties.push_back(&pRight);
    enteties.push_back(&ball);

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "PONG");
    window.setFramerateLimit(60);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        
        Entity::updateAll(window, enteties);

        window.display();
    }
    
    return 0;
}
