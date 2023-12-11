#include "Player.hpp"
#include <unordered_map>
#include "../utils/utils.hpp"
#include <iostream>

std::vector<Ball*> Player::balls;

Player::Player(int defaultX, std::unordered_map<Keys, sf::Keyboard::Key> keyBindings)
    : Entity(sf::Vector2f(defaultX, (WINDOW_HEIGHT / 2) - (PLAYER_DIMENSIONS.y / 2)), PLAYER_DIMENSIONS),
        keyBindings(keyBindings),
        playerSpeed(INITIAL_PLAYER_SPEED),
        defaultX(defaultX) {}

void Player::handleMovement()
{
    if (sf::Keyboard::isKeyPressed(keyBindings[UP])) {
        int newPos = body.getPosition().y - playerSpeed;
        body.setPosition(defaultX, std::max(0, newPos));
    }

    if (sf::Keyboard::isKeyPressed(keyBindings[DOWN])) {
        int newPos = body.getPosition().y + playerSpeed;
        body.setPosition(defaultX, std::min(WINDOW_HEIGHT - (int) PLAYER_DIMENSIONS.y, newPos));
    }   
}

void Player::handleBallCollisions() {
    auto pBounding = getBoundingBox();

    for (auto ball : balls) {
        if (isCollision(*ball)) {
            ball->speed.x = -ball->speed.x;
        }
    }
}

void Player::update()
{
    handleBallCollisions();
    handleMovement();
}
