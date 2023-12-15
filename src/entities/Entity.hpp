#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <unordered_map>

class Entity
{

public:
    sf::RectangleShape body;

    float halfX;

    float halfY;

    std::unordered_map<int, std::pair<bool, bool>> prevOverlap;

    Entity(const sf::Vector2f& position, const sf::Vector2f& size);

    int id();

    static std::vector<Entity*> allEntities;

    std::pair<sf::Vector2f, sf::Vector2f> getBoundingBox();

    sf::Vector2f middle();

    bool isCollision(Entity& other);

    static void updateAll(sf::RenderWindow &window);

    static int generateID();

    virtual void handleMovement() = 0;

    virtual void update() = 0;

    private:
        int _id;

        static int globalID;
};

#endif