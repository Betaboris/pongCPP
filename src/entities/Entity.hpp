#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/Graphics.hpp>

class Entity
{
public:
    sf::RectangleShape body;
    sf::Vector2f pos;

    Entity(const sf::Vector2f& position, const sf::Vector2f& size);

    virtual void handleMovement() = 0;
};

#endif