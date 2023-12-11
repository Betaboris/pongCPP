#ifndef BALL_HPP
#define BALL_HPP

#include <unordered_set>
#include "Entity.hpp"
#include "../constants/constants.hpp"
#include "Boundary.hpp"
#include "functional"

class Ball : public Entity
{
public:
    sf::Vector2f speed;

    static std::unordered_set<Boundary*> boundaries;

    void checkBoundaryCollision();

    Ball();

    void handleMovement() override;

    void update() override;

};

#endif