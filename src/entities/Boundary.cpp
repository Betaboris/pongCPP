#include "Boundary.hpp"

Boundary::Boundary(std::function<void()> func, const sf::Vector2f &pos, const sf::Vector2f &dim, BoundaryType type)
: Entity(pos, dim), func(func), type(type){ }

void Boundary::handleMovement() {};

void Boundary::update() {};

void Boundary::onCollision() {
    func();
}