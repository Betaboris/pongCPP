#include "Player.hpp"
#include <unordered_map>
#include "../utils/utils.hpp"
#include <iostream>

//std::vector<Ball*> Player::balls;
std::vector<Boundary*> Player::boundaries;

Player::Player(int defaultX, std::unordered_map<Keys, sf::Keyboard::Key> keyBindings) : 
        Entity(sf::Vector2f(defaultX, (WINDOW_HEIGHT / 2) - (PLAYER_DIMENSIONS.y / 2)), PLAYER_DIMENSIONS),
        keyBindings(keyBindings),
        velocity(),
        acceleration(sf::Vector2f(0, 0.4f)),
        deceleration(sf::Vector2f(0, 0.1f)),
        defaultX(defaultX) {}

void Player::handleMovement() {

    bool bounced = false;

    for (auto b : boundaries) {
        if (isCollision(*b)) {
            velocity *= -BOUNCE_FACTOR;
        }
    }

    if (sf::Keyboard::isKeyPressed(keyBindings[UP])) {
        velocity -= acceleration;
    }

    if (sf::Keyboard::isKeyPressed(keyBindings[DOWN])) {
        velocity += acceleration;
    }   

    if (velocity.y > 0) {
        velocity.y = std::max(0.0f, velocity.y - deceleration.y);
    } else if (velocity.y < 0) {
        velocity.y = std::min(0.0f, velocity.y + deceleration.y);
    }

    float yAxis = body.getPosition().y + velocity.y;
    float maxYPos = WINDOW_HEIGHT - (int) PLAYER_DIMENSIONS.y;
    yAxis = std::min(maxYPos, std::max(yAxis, 0.0f));
    body.setPosition(defaultX, yAxis);
}

void Player::update() {
    //handleBallCollisions();
    handleMovement();
}
