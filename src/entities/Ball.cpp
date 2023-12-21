#include "Ball.hpp"
#include <iostream>
#include <cmath>

std::unordered_set<Boundary*> Ball::boundaries;
std::unordered_set<Player*> Ball::players;

Ball::Ball() : Entity(sf::Vector2f(WINDOW_WIDTH / 2 - BALL_SIDE_LEN / 2, WINDOW_HEIGHT / 2 - BALL_SIDE_LEN / 2),
               sf::Vector2f(BALL_SIDE_LEN, BALL_SIDE_LEN)),
               inPlayerCollision(false),
               speed(sf::Vector2f(5, 0)) {}

void Ball::clampSpeed() {
    float speedMagnitude = std::sqrt(speed.x * speed.x + speed.y * speed.y);
    if (speedMagnitude > MAX_BALL_SPEED) {
        speed.x = (speed.x / speedMagnitude) * MAX_BALL_SPEED;
        speed.y = (speed.y / speedMagnitude) * MAX_BALL_SPEED;
    }
}

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

    clampSpeed();
}

std::pair<sf::Vector2f, sf::Vector2f> Ball::getSweptAABB() {
    auto box = getBoundingBox();
    sf::Vector2f topLeft = box.first;
    sf::Vector2f bottomRight = box.second;

    if (speed.x > 0) {
        bottomRight.x += speed.x;
    } else {
        topLeft.x += speed.x;
    }

    if (speed.y > 0) {
        bottomRight.y += speed.y;
    } else {
        topLeft.y += speed.y;
    }

    return {topLeft, bottomRight};
}

bool Ball::isSweptCollision(Entity& other) {
    auto sweptBox = getSweptAABB();
    auto otherBox = other.getBoundingBox();

    // Check if there is an overlap between the swept AABB and the other entity
    bool overlapX = sweptBox.second.x >= otherBox.first.x && sweptBox.first.x <= otherBox.second.x;
    bool overlapY = sweptBox.second.y >= otherBox.first.y && sweptBox.first.y <= otherBox.second.y;

    return overlapX && overlapY;
}

void Ball::handleBoundaryCollision() {
    for (auto b : boundaries) {
        if (!isSweptCollision(*b)) continue;

        switch (b->type) {
            case Bouncy:
                reflectVelocityOnCollision(*b, false);
                break;
            case Functional:
                b->onCollision();
                body.setPosition(sf::Vector2f(WINDOW_WIDTH / 2 - BALL_SIDE_LEN / 2, WINDOW_HEIGHT / 2 - BALL_SIDE_LEN / 2));
                speed = (std::rand() % 2 == 0) ? sf::Vector2f(5, 0) : sf::Vector2f(-5, 0);
                break;
        }
    }
}

void Ball::handlePlayerCollision() {
    for (auto player : players) {
        if (!isSweptCollision(*player)) continue;

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