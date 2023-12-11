#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "../constants/constants.hpp"
#include "../entities/all_entities.hpp"
#include "../utils/utils.hpp"

void nothing() {
    std::cout << "Calling function" << std::endl;

};

int main()
{
    std::vector<Entity*> entities;
    std::cout << "Hej på dig" << std::endl;

    Ball ball;
    Player::balls.push_back(&ball);

    sf::Vector2f topSize(WINDOW_WIDTH, 50);
    sf::Vector2f sideSize(50, WINDOW_HEIGHT);

    Boundary leftWall(nothing, sf::Vector2f(-50, 0), sideSize, Functional);
    Boundary rightWall(nothing, sf::Vector2f(WINDOW_WIDTH, 0), sideSize, Functional);
    Boundary topWall(nothing, sf::Vector2f(0, -50), topSize, Bouncy);
    Boundary bottomWall(nothing, sf::Vector2f(0, WINDOW_HEIGHT), topSize, Bouncy);

    Ball::boundaries.insert(&leftWall);
    Ball::boundaries.insert(&rightWall);
    Ball::boundaries.insert(&topWall);
    Ball::boundaries.insert(&bottomWall);



    Player pLeft(DISTANCE_TO_BORDER, playerKeyBindings(sf::Keyboard::Key::W, sf::Keyboard::Key::S));
    Player pRight(WINDOW_WIDTH - (DISTANCE_TO_BORDER + PLAYER_DIMENSIONS.x), playerKeyBindings(sf::Keyboard::Key::Up, sf::Keyboard::Key::Down));

    entities.push_back(&pLeft);
    entities.push_back(&pRight);
    entities.push_back(&ball);

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
        
        Entity::updateAll(window, entities);

        window.display();
    }
    
    return 0;
}
