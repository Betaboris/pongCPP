#ifndef BALL_HPP
#define BALL_HPP

#include "Entity.hpp"
#include "../constants/constants.hpp"

class Ball : public Entity
{
public:
    sf::Vector2f speed;

    Ball();

    void handleMovement() override;

    void update() override;
};

#endif