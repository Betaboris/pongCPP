#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/Graphics.hpp>
#include <vector>

class Entity
{

public:
    sf::RectangleShape body;
    sf::Vector2f pos;

    Entity(const sf::Vector2f& position, const sf::Vector2f& size);

    static void updateAll(sf::RenderWindow &window, std::vector<Entity*> entities);

    virtual void handleMovement() = 0;

    virtual void update() = 0;
};

#endif