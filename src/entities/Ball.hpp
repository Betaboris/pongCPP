#ifndef BALL_HPP
#define BALL_HPP

#include <unordered_set>
#include "Entity.hpp"
#include "Boundary.hpp"

class Ball : public Entity {
public:
    sf::Vector2f speed;
    static std::unordered_set<Boundary*> boundaries;

    Ball();

    void checkBoundaryCollision();
    void handleMovement() override;
    void update() override;
};

#endif