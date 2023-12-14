#include "Entity.hpp"
#include <SFML/Graphics.hpp>

Entity::Entity(const sf::Vector2f& position, const sf::Vector2f& size) {
    body.setSize(size);
    body.setPosition(position);
}

std::pair<sf::Vector2f, sf::Vector2f> Entity::getBoundingBox() {
    auto pos = body.getPosition();
    return {pos, pos + body.getSize()};
}

bool Entity::isCollision(Entity& other) {
    auto ourBoundingBox = getBoundingBox();
    auto theirBoundingBox = other.getBoundingBox();
    
    bool overlapOnX = (ourBoundingBox.second.x >= theirBoundingBox.first.x && ourBoundingBox.first.x <= theirBoundingBox.second.x);
    bool overlapOnY = (ourBoundingBox.second.y >= theirBoundingBox.first.y && ourBoundingBox.first.y <= theirBoundingBox.second.y);

    return overlapOnX && overlapOnY;
}

void Entity::updateAll(sf::RenderWindow &window, std::vector<Entity*> entities) {
    for (auto entity : entities) {
        entity->update();
        window.draw(entity->body);
    }
}