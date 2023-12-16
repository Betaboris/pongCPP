#include "Ball.hpp"

std::unordered_set<Boundary*> Ball::boundaries;
std::unordered_set<Player*> Ball::players;

Ball::Ball() : Entity(sf::Vector2f(WINDOW_WIDTH / 2 - BALL_SIDE_LEN / 2, WINDOW_HEIGHT / 2 - BALL_SIDE_LEN / 2),
               sf::Vector2f(BALL_SIDE_LEN, BALL_SIDE_LEN)),
               inPlayerCollision(false),
               speed(sf::Vector2f(5, 0)) {}

void Ball::handleMovement() {
    auto currentPos = body.getPosition();        
    auto nextPos = currentPos + speed;
    body.setPosition(nextPos);
}

void Ball::reflectVelocityOnCollision(Entity& other, bool addSpeed) {
    auto ourBoundingBox = getBoundingBox();
    auto theirBoundingBox = other.getBoundingBox();

    // Calculate overlap in both dimensions
    float overlapX = std::min(ourBoundingBox.second.x, theirBoundingBox.second.x) - std::max(ourBoundingBox.first.x, theirBoundingBox.first.x);
    float overlapY = std::min(ourBoundingBox.second.y, theirBoundingBox.second.y) - std::max(ourBoundingBox.first.y, theirBoundingBox.first.y);

    // Determine the axis of the collision
    if (overlapX < overlapY) {
        // Smaller overlap in X-axis suggests collision is horizontal
        speed.x *= (addSpeed ? -1*BALL_SPEED_UP : -1);
    } else {
        // Smaller overlap in Y-axis suggests collision is vertical
        speed.y *= (addSpeed ? -1*BALL_SPEED_UP : -1);
    }
}

void Ball::handleBoundaryCollision() {
    for (auto b : boundaries) {
        if (!isCollision(*b)) continue;

        switch (b->type) {
            case Bouncy:
                reflectVelocityOnCollision(*b, false);
                break;
            case Functional:
                b->onCollision();
                break;
        }
    }
}

void Ball::handlePlayerCollision() {
    for (auto player : players) {
        if (!isCollision(*player)) continue;

        if (!inPlayerCollision) {
            reflectVelocityOnCollision(*player, true);

            // Catch speed from player
            speed.x += BALL_FRICTION * player->speed.x;
            speed.y += BALL_FRICTION * player->speed.y;

            inPlayerCollision = true; // Set the collision flag
        }
        return; // Exit the function to avoid multiple bounces
    }
    
    // If no collision detected, reset the flag
    inPlayerCollision = false;
}

void Ball::update() {
    handleBoundaryCollision();
    handlePlayerCollision();
    handleMovement();
}