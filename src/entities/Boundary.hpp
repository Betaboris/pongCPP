#ifndef BOUNDARY_HPP
#define BOUNDARY_HPP

#include "Entity.hpp"
#include "../constants/constants.hpp"
#include <functional>

class Boundary : public Entity {
public:
    BoundaryType type;

    Boundary(const sf::Vector2f& pos, const sf::Vector2f& dim, BoundaryType type, std::function<void()> func = [](){});

    void onCollision();
    void handleMovement() override;
    void update() override;

private:
    std::function<void()> func;

};

#endif