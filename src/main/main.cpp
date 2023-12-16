#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "../constants/constants.hpp"
#include "../entities/all_entities.hpp"
#include "../utils/utils.hpp"

Boundary createWall(const sf::Vector2f& position, const sf::Vector2f& size, const BoundaryType& type, std::function<void()> callback = nullptr) {
    return Boundary(position, size, type, callback);
}

Player createPlayer(const sf::Vector2f& position, const std::unordered_map<Keys, sf::Keyboard::Key>& keyBindings) {
    return Player(position, keyBindings);
}

std::unordered_map<Keys, sf::Keyboard::Key> buildKeyBindings(sf::Keyboard::Key upKey, sf::Keyboard::Key downKey) {
    PlayerKeyBindingsBuilder builder;
    return builder.setUp(upKey).setDown(downKey).build();
}

int main() {
    std::vector<Boundary> walls = {
        createWall(sf::Vector2f(-50, 0), sf::Vector2f(50, WINDOW_HEIGHT), Bouncy, []() { std::cout << "Left wall\n"; }),
        createWall(sf::Vector2f(WINDOW_WIDTH, 0), sf::Vector2f(50, WINDOW_HEIGHT), Bouncy, []() { std::cout << "Right wall\n"; }),
        createWall(sf::Vector2f(0, -50), sf::Vector2f(WINDOW_WIDTH, 50), Bouncy),
        createWall(sf::Vector2f(0, WINDOW_HEIGHT), sf::Vector2f(WINDOW_WIDTH, 50), Bouncy)
    };

    for (auto& wall : walls) {
        Ball::boundaries.insert(&wall);
        Player::boundaries.insert(&wall);
    }

    Ball ball;

    // Calculate the vertical center position for the players
    float centerY = (WINDOW_HEIGHT - PLAYER_DIMENSIONS.y) / 2.0f;

    // Create the left player
    Player pLeft = createPlayer(sf::Vector2f(DISTANCE_TO_BORDER, centerY), buildKeyBindings(sf::Keyboard::Key::W, sf::Keyboard::Key::S));

    // Create the right player, adjusting position for the player's width
    Player pRight = createPlayer(sf::Vector2f(WINDOW_WIDTH - (DISTANCE_TO_BORDER + PLAYER_DIMENSIONS.x), centerY), buildKeyBindings(sf::Keyboard::Key::Up, sf::Keyboard::Key::Down));

    std::vector<Player*> players = {&pLeft, &pRight};

    for (auto& player : players) {
        Ball::players.insert(player);
    }

    std::vector<Entity*> entities = {&pLeft, &pRight, &ball};

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "PONG");
    window.setFramerateLimit(60);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        Entity::updateAll(window, entities);
        window.display();
    }

    return 0;
}
