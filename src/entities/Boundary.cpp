#include "Boundary.hpp"

Boundary::Boundary(const sf::Vector2f& pos, const sf::Vector2f& dim, BoundaryType type, std::function<void()> func) : 
    Entity(pos, dim), type(type), func(func) {}

void Boundary::handleMovement() {};

void Boundary::update() {};

void Boundary::onCollision() {
    func();
}