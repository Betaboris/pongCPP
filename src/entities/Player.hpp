#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Entity.hpp"
#include "Ball.hpp"
#include "../constants/constants.hpp"
#include <vector>

class Player : public Entity {
public:
    float velocity;
    float acceleration;
    float deceleration;
    int defaultX;
    std::unordered_map<Keys, sf::Keyboard::Key> keyBindings;
    static std::vector<Ball*> balls;
    static std::vector<Boundary*> boundaries;

    Player(int defaultX, std::unordered_map<Keys, sf::Keyboard::Key> keyBindings);

    void handleMovement() override;
    void update() override;
    void handleBallCollisions();
};

#endif