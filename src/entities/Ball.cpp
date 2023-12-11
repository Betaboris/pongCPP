#include "Ball.hpp"

std::unordered_set<Boundary*> Ball::boundaries;

Ball::Ball() : Entity(sf::Vector2f(WINDOW_WIDTH / 2 - BALL_SIDE_LEN / 2, WINDOW_HEIGHT / 2 - BALL_SIDE_LEN / 2),
               sf::Vector2f(BALL_SIDE_LEN, BALL_SIDE_LEN)),
               speed(sf::Vector2f(5, 8)) {}

void Ball::handleMovement()
{
    auto currentPos = body.getPosition();
    // if (currentPos.y <= 0 || currentPos.y >= WINDOW_HEIGHT - BALL_SIDE_LEN) {
    //     speed.y = -speed.y;
    // }         

    auto nextPos = currentPos + speed;
    //nextPos.y = std::min(WINDOW_HEIGHT - BALL_SIDE_LEN, std::max(0, (int) nextPos.y));

    body.setPosition(nextPos);
}

void Ball::checkBoundaryCollision() {
    for (auto b : boundaries) {
        if (isCollision(*b)) {
            switch (b->type) {
                case Bouncy:
                    speed.y = -speed.y;
                    break;
                case Functional:
                    b->onCollision();
                    break;
            }
        }
    }
}

void Ball::update()
{
    checkBoundaryCollision();
    handleMovement();
}