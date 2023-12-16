#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Entity.hpp"
#include "Boundary.hpp"
#include "../constants/constants.hpp"
#include <unordered_set>

class Player : public Entity {
public:
    sf::Vector2f speed;
    float acceleration;
    float deceleration;
    std::unordered_map<Keys, sf::Keyboard::Key> keyBindings;
    static std::unordered_set<Boundary*> boundaries;

    Player(const sf::Vector2f& position, const std::unordered_map<Keys, sf::Keyboard::Key> keyBindings);

    bool isKeyActive(Keys key);
    void applyAcceleration();
    void applyDeceleration();
    void clampSpeedAndPosition();
    void handleMovement() override;
    void update() override;
    void handleBoundaryCollision();
};

#endif