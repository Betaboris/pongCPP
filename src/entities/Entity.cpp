#include <iostream>
#include "Entity.hpp"
#include <SFML/Graphics.hpp>
int Entity::globalID = 0;
std::vector<Entity*> Entity::allEntities;

Entity::Entity(const sf::Vector2f& position, const sf::Vector2f& size) :
    halfX(size.x / 2),
    halfY(size.y / 2),
    _id(generateID())
 {
    body.setSize(size);
    body.setPosition(position);
    allEntities.push_back(this);
}

std::pair<sf::Vector2f, sf::Vector2f> Entity::getBoundingBox() {
    auto pos = body.getPosition();
    return {pos, pos + body.getSize()};
}

sf::Vector2f Entity::middle() {
    auto pos = body.getPosition();
    pos.x += halfX;
    pos.y += halfY;

    return pos;
}

int Entity::id() {
    return _id;
}

bool Entity::isCollision(Entity& other) {
    sf::Vector2f distance = middle() - other.middle();

    //overlap if sum of half-sides bigger then distance
    bool xOverlap = (abs(distance.x) <= halfX + other.halfX);
    bool yOverlap = (abs(distance.y) <= halfY + other.halfY);
    prevOverlap[other.id()] = {xOverlap, yOverlap};
    return xOverlap && yOverlap;
}

void Entity::updateAll(sf::RenderWindow &window) {
    for (auto entity : Entity::allEntities) {
        entity->update();
        window.draw(entity->body);
    }
}

int Entity::generateID()
{
    globalID++;
    return globalID;
}
