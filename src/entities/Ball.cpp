#include "Ball.hpp"

Ball::Ball() : Entity(sf::Vector2f(WINDOW_WIDTH / 2 - ballSide / 2, WINDOW_HEIGHT / 2 - ballSide / 2),
               sf::Vector2f(ballSide, ballSide)),
               speed(sf::Vector2f(5, 8)) {}

void Ball::handleMovement()
{
    auto currentPos = body.getPosition();
    if (currentPos.y <= 0 || currentPos.y >= WINDOW_HEIGHT - ballSide) {
        speed.y = -speed.y;
    }         

    auto nextPos = currentPos + speed;
    nextPos.y = std::min(WINDOW_HEIGHT - ballSide, std::max(0, (int) nextPos.y));

    body.setPosition(nextPos);
}

void Ball::update()
{
    handleMovement();
}