#include "Player.hpp"
#include <unordered_map>

std::vector<Ball*> Player::balls;

Player::Player(int defaultX, std::unordered_map<Keys, sf::Keyboard::Key> keyBindings)
    : Entity(sf::Vector2f(defaultX, (WINDOW_HEIGHT / 2) - (PLAYER_DIMENSIONS.y / 2)), PLAYER_DIMENSIONS),
        keyBindings(keyBindings),
        playerSpeed(INITIAL_PLAYER_SPEED) {}


void Player::handleMovement()
{
    if (sf::Keyboard::isKeyPressed(keyBindings[UP])) {
        int newPos = body.getPosition().y - playerSpeed;
        body.setPosition(pos.x, std::max(0, newPos));
    }

    if (sf::Keyboard::isKeyPressed(keyBindings[DOWN])) {
        int newPos = body.getPosition().y + playerSpeed;
        body.setPosition(pos.x, std::min(WINDOW_HEIGHT - (int) PLAYER_DIMENSIONS.y, newPos));
    }   
}

void Player::handleBallCollisions() 
{
    for (auto ball : balls) {
        auto ballPos = ball->body.getPosition();
        auto playerPos = body.getPosition();
        int leftSide = playerPos.x;
        int rightSide = leftSide + PLAYER_DIMENSIONS.x;

        if (ball->speed.x < 0) {
            if (ballPos.x >= leftSide && ballPos.x <= rightSide) 
                ball->speed.x = -ball->speed.x;
        } else {
            if (ballPos.x + ballSide >= leftSide && ballPos.x + ballSide <= rightSide) 
                ball->speed.x = -ball->speed.x;
        }
    }
}

void Player::update()
{
    handleBallCollisions();
    handleMovement();
}
