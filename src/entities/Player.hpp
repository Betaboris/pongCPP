#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Entity.hpp"
#include "Boundary.hpp"
#include "../constants/constants.hpp"
#include <vector>

class Player : public Entity {
public:
    sf::Vector2f velocity;
    sf::Vector2f acceleration;
    sf::Vector2f deceleration;
    int defaultX;
    std::unordered_map<Keys, sf::Keyboard::Key> keyBindings;
    static std::vector<Boundary*> boundaries;

    Player(int defaultX, std::unordered_map<Keys, sf::Keyboard::Key> keyBindings);

    void handleMovement() override;
    void update() override;
};

#endif