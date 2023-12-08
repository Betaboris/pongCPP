#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Entity.hpp"
#include "Ball.hpp"
#include "../constants/constants.hpp"

class Player : public Entity
{
public:
    int playerSpeed;
    std::unordered_map<Keys, sf::Keyboard::Key> keyBindings;

    Player(int defaultX, std::unordered_map<Keys, sf::Keyboard::Key> keyBindings);

    void handleMovement() override;
    void handleBallCollision(Ball& ball);
};

#endif