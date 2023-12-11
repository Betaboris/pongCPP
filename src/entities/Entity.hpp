#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/Graphics.hpp>
#include <vector>

class Entity
{

public:
    sf::RectangleShape body;

    Entity(const sf::Vector2f& position, const sf::Vector2f& size);

    std::pair<sf::Vector2f, sf::Vector2f> getBoundingBox();

    bool isCollision(Entity& other);

    static void updateAll(sf::RenderWindow &window, std::vector<Entity*> entities);

    virtual void handleMovement() = 0;

    virtual void update() = 0;
};

#endif