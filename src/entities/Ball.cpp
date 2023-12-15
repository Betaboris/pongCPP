#include <iostream>
#include <typeinfo>
#include "Ball.hpp"


Ball::Ball() : Entity(sf::Vector2f(WINDOW_WIDTH / 2 - BALL_SIDE_LEN / 2, WINDOW_HEIGHT / 2 - BALL_SIDE_LEN / 2),
               sf::Vector2f(BALL_SIDE_LEN, BALL_SIDE_LEN)),
               speed(sf::Vector2f(5, 0)) {}

void Ball::handleMovement() {
    auto currentPos = body.getPosition();        
    auto nextPos = currentPos + speed;

    body.setPosition(nextPos);
}

void Ball::handleCollisions() {
    for (auto e : allEntities) { 
        if (e == this) {
            continue;
        }

        auto prev = prevOverlap[e->id()];

        if (isCollision(*e)) {
            Player * p = dynamic_cast<Player *>(e);

            //if a player, also add velocity
            if (p) {
                speed = speed + p->velocity;
            } 

            //if previous overlap in x-dimension, it moves in y-direction
            if (prev.first) {
                speed.y = -speed.y;
            } else if (prev.second){
                speed.x = -speed.x;
            }
        }
    }
}

void Ball::update() {
    handleCollisions();
    handleMovement();
}