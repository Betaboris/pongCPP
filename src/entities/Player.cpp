#include "Player.hpp"
#include <unordered_map>
#include "../utils/utils.hpp"
#include <iostream>

std::vector<Ball*> Player::balls;
std::vector<Boundary*> Player::boundaries;

Player::Player(int defaultX, std::unordered_map<Keys, sf::Keyboard::Key> keyBindings) : 
        Entity(sf::Vector2f(defaultX, (WINDOW_HEIGHT / 2) - (PLAYER_DIMENSIONS.y / 2)), PLAYER_DIMENSIONS),
        keyBindings(keyBindings),
        playerSpeed(INITIAL_PLAYER_SPEED),
        acceleration(1),
        defaultX(defaultX) {}

void Player::handleMovement() {
    for (auto b : boundaries) {
        if (isCollision(*b)) {
            playerSpeed *= -BOUNCE_FACTOR;
        }
    }
    if (sf::Keyboard::isKeyPressed(keyBindings[UP])) {
        playerSpeed += acceleration;
        int newPos = body.getPosition().y - playerSpeed;
        body.setPosition(defaultX, std::max(0, newPos));
    }

    if (sf::Keyboard::isKeyPressed(keyBindings[DOWN])) {
        playerSpeed += acceleration;
        int newPos = body.getPosition().y + playerSpeed;
        body.setPosition(defaultX, std::min(WINDOW_HEIGHT - (int) PLAYER_DIMENSIONS.y, newPos));
    }   
}

void Player::handleBallCollisions() {
    for (auto ball : balls) {
        if (isCollision(*ball))  {
            ball->speed.x = -ball->speed.x;
            int dy;
            if (sf::Keyboard::isKeyPressed(keyBindings[UP])) {
                dy = -playerSpeed;
            } else if (sf::Keyboard::isKeyPressed(keyBindings[DOWN])) {
                dy = playerSpeed;
            } else dy = 0;
            ball->speed.y = ball->speed.y + dy;
        }
    }
}

void Player::update() {
    handleBallCollisions();
    handleMovement();
}
