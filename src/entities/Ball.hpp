#ifndef BALL_HPP
#define BALL_HPP

#include <unordered_set>
#include "Entity.hpp"
#include "Boundary.hpp"
#include "Player.hpp"

class Ball : public Entity {
public:
    sf::Vector2f speed;

    Ball();

    void handleCollisions();
    void handleMovement() override;
    void update() override;
};

#endif