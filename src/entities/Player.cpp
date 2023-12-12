#include "Player.hpp"
#include <unordered_map>
#include "../utils/utils.hpp"
#include <iostream>

std::vector<Ball*> Player::balls;
std::vector<Boundary*> Player::boundaries;

Player::Player(int defaultX, std::unordered_map<Keys, sf::Keyboard::Key> keyBindings) : 
        Entity(sf::Vector2f(defaultX, (WINDOW_HEIGHT / 2) - (PLAYER_DIMENSIONS.y / 2)), PLAYER_DIMENSIONS),
        keyBindings(keyBindings),
        velocity(0),
        acceleration(0.4f),
        deceleration(0.1f),
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

    if (velocity > 0) {
        velocity = std::max(0.0f, velocity - deceleration);
    } else if (velocity < 0) {
        velocity = std::min(0.0f, velocity + deceleration);
    }

    float yAxis = body.getPosition().y + velocity;
    float maxYPos = WINDOW_HEIGHT - (int) PLAYER_DIMENSIONS.y;
    yAxis = std::min(maxYPos, std::max(yAxis, 0.0f));
    body.setPosition(defaultX, yAxis);
}

void Player::handleBallCollisions() {
    for (auto ball : balls) {
        if (isCollision(*ball))  {
            ball->speed.x = -ball->speed.x;
            int dy;
            if (sf::Keyboard::isKeyPressed(keyBindings[UP])) {
                dy = -velocity;
            } else if (sf::Keyboard::isKeyPressed(keyBindings[DOWN])) {
                dy = velocity;
            } else dy = 0;
            ball->speed.y = ball->speed.y + dy;
        }
    }
}

void Player::update() {
    handleBallCollisions();
    handleMovement();
}
