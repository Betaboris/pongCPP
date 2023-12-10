#include "Entity.hpp"
#include <SFML/Graphics.hpp>

Entity::Entity(const sf::Vector2f& position, const sf::Vector2f& size) : pos(position) {
    body.setSize(size);
    body.setPosition(pos);
}

void Entity::updateAll(sf::RenderWindow &window, std::vector<Entity*> entities)
{
    for (auto entity : entities) {
        entity->update();
        window.draw(entity->body);
    }
}