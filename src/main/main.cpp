#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "../constants/constants.hpp"
#include "../entities/all_entities.hpp"
#include "../utils/utils.hpp"

int main() {
    std::vector<Entity*> entities;

    Ball ball;

    sf::Vector2f topSize(WINDOW_WIDTH, 50);
    sf::Vector2f sideSize(50, WINDOW_HEIGHT);

    Boundary leftWall(sf::Vector2f(-50, 0), sideSize, Functional, []() {
        std::cout << "Calling leftWall function" << std::endl;
    });

    Boundary rightWall(sf::Vector2f(WINDOW_WIDTH, 0), sideSize, Functional, []() {
        std::cout << "Calling rightWall function" << std::endl;
    });

    Boundary topWall(sf::Vector2f(0, -50), topSize, Bouncy);

    Boundary bottomWall(sf::Vector2f(0, WINDOW_HEIGHT), topSize, Bouncy);

    Player pLeft(DISTANCE_TO_BORDER, playerKeyBindings(sf::Keyboard::Key::W, sf::Keyboard::Key::S));
    Player pRight(WINDOW_WIDTH - (DISTANCE_TO_BORDER + PLAYER_DIMENSIONS.x), playerKeyBindings(sf::Keyboard::Key::Up, sf::Keyboard::Key::Down));

    entities.push_back(&pLeft);
    entities.push_back(&pRight);
    entities.push_back(&ball);

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "PONG");
    window.setFramerateLimit(60);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        
        Entity::updateAll(window);

        window.display();
    }
    
    return 0;
}
