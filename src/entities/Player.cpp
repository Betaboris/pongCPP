#include "Player.hpp"
#include <unordered_map>
#include <iostream>

std::unordered_set<Entity*> Player::boundaries;

Player::Player(const sf::Vector2f& position, const std::unordered_map<Keys, sf::Keyboard::Key> keyBindings, PlayerType type) : 
        Entity(position, PLAYER_DIMENSIONS),
        keyBindings(keyBindings),
        speed(sf::Vector2f(0, 0)),
        acceleration(0.5f),
        deceleration(0.1f),
        score(0),
        type(type) {}

bool Player::isKeyActive(Keys key) {
    auto found = keyBindings.find(key);
    if (found != keyBindings.end()) {
        return sf::Keyboard::isKeyPressed(found->second);
    }
    return false;
}

void Player::applyAcceleration() {
    if (isKeyActive(Keys::UP)) {
        speed.y -= acceleration;
    }
    if (isKeyActive(Keys::DOWN)) {
        speed.y += acceleration;
    }
    if (isKeyActive(Keys::LEFT)) {
        speed.x -= acceleration;
    }
    if (isKeyActive(Keys::RIGHT)) {
        speed.x += acceleration;
    }
}

void Player::applyDeceleration() {
    if (!isKeyActive(Keys::UP) && !isKeyActive(Keys::DOWN)) {
        if (speed.y > 0) {
            speed.y = std::max(0.0f, speed.y - deceleration);
        } else if (speed.y < 0) {
            speed.y = std::min(0.0f, speed.y + deceleration);
        }
    }
    if (!isKeyActive(Keys::LEFT) && !isKeyActive(Keys::RIGHT)) {
        if (speed.x > 0) {
            speed.x = std::max(0.0f, speed.x - deceleration);
        } else if (speed.x < 0) {
            speed.x = std::min(0.0f, speed.x + deceleration);
        }
    }
}

void Player::clampSpeedAndPosition() {
    speed.x = std::clamp(speed.x, -PLAYER_MAX_SPEED, PLAYER_MAX_SPEED);
    speed.y = std::clamp(speed.y, -PLAYER_MAX_SPEED, PLAYER_MAX_SPEED);

    auto currentPos = body.getPosition();        
    auto nextPos = currentPos + speed;

    nextPos.x = std::clamp(nextPos.x, 0.0f, WINDOW_WIDTH - PLAYER_DIMENSIONS.x);
    nextPos.y = std::clamp(nextPos.y, 0.0f, WINDOW_HEIGHT - PLAYER_DIMENSIONS.y);

    body.setPosition(nextPos);
}

void Player::handleMovement() {
    applyAcceleration();
    applyDeceleration();
    clampSpeedAndPosition();
}

void Player::handleBoundaryCollision() {
    for (auto b : boundaries) {
        if (!isCollision(*b)) continue;
        speed.x *= -BOUNCE_FACTOR;
        speed.y *= -BOUNCE_FACTOR;
    }
}

void Player::update() {
    handleBoundaryCollision();
    handleMovement();
}