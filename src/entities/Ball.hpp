#ifndef BALL_HPP
#define BALL_HPP

#include <unordered_set>
#include "Entity.hpp"
#include "Boundary.hpp"
#include "Player.hpp"
#include <deque>

class Ball : public Entity {
public:
    sf::Vector2f speed;
    static std::unordered_set<Boundary*> boundaries;
    static std::unordered_set<Player*> players;
    bool inPlayerCollision;
    std::deque<sf::Vector2f> tailPositions;
    

    Ball();

    void clampSpeed();
    void addTailPosition();
    void drawTails(sf::RenderWindow & window);
    void reflectVelocityOnCollision(Entity& other, bool addSpeed);
    bool isSweptCollision(Entity& other);
    std::pair<sf::Vector2f, sf::Vector2f> getSweptAABB();
    void handleBoundaryCollision();
    void handlePlayerCollision();
    void handleMovement() override;
    void update() override;
};

#endif