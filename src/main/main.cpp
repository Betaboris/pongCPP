#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <unordered_map>
#include "../constants/constants.hpp"
#include "../entities/Entity.hpp"
#include "../entities/Player.hpp"
#include "../entities/Ball.hpp"


int main()
{
    std::unordered_map<Keys, sf::Keyboard::Key> pLeftBindings{
        {Keys::UP, sf::Keyboard::Key::W},
        {Keys::DOWN, sf::Keyboard::Key::S}
    };

    std::unordered_map<Keys, sf::Keyboard::Key> pRightBindings{
        {Keys::UP, sf::Keyboard::Key::Up},
        {Keys::DOWN, sf::Keyboard::Key::Down}};

    std::vector<Player*> players;
    Player pLeft(DISTANCE_TO_BORDER, pLeftBindings);
    Player pRight(WINDOW_WIDTH - (DISTANCE_TO_BORDER + PLAYER_DIMENSIONS.x), pRightBindings);
    players.push_back(&pLeft);
    players.push_back(&pRight);

    Ball ball;

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
        for (Player* player : players) {
            player->handleMovement();
            player->handleBallCollision(ball);
            window.draw(player->body);
        }

        ball.handleMovement(); window.draw(ball.body);

        window.display();
    }

    return 0;
}
