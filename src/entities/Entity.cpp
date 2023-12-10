#include "Entity.hpp"
#include <SFML/Graphics.hpp>

Entity::Entity(const sf::Vector2f& position, const sf::Vector2f& size) {
    body.setSize(size);
    body.setPosition(position);
}

void Entity::updateAll(sf::RenderWindow &window, std::vector<Entity*> entities)
{
    for (auto entity : entities) {
        entity->update();
        window.draw(entity->body);
    }
}