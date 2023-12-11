#include "Entity.hpp"
#include <SFML/Graphics.hpp>

Entity::Entity(const sf::Vector2f& position, const sf::Vector2f& size) {
    body.setSize(size);
    body.setPosition(position);
}

std::pair<sf::Vector2f, sf::Vector2f> Entity::getBoundingBox()
{
    auto p = body.getPosition();
    return {p, p + body.getSize()};
}

bool Entity::isCollision(Entity& other)
    {
       auto our = getBoundingBox();
       auto theirs = other.getBoundingBox();
    // Check for non-overlapping conditions along the x-axis
    if (our.first.x > theirs.second.x || our.second.x < theirs.first.x)
        return false;

    // Check for non-overlapping conditions along the y-axis
    if (our.first.y > theirs.second.y || our.second.y < theirs.first.y)
        return false;

    // If not non-overlapping along both axes, rectangles are overlapping or touching
    return true;
}

void Entity::updateAll(sf::RenderWindow &window, std::vector<Entity*> entities)
{
    for (auto entity : entities) {
        entity->update();
        window.draw(entity->body);
    }
}

