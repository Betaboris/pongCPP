#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <SFML/Graphics.hpp>

extern const int WINDOW_HEIGHT;
extern const int WINDOW_WIDTH;
extern const int DISTANCE_TO_BORDER;
extern const float BOUNCE_FACTOR;
extern const int BALL_SIDE_LEN;
extern const float BALL_FRICTION;
extern const float BALL_SPEED_UP;
extern const sf::Vector2f PLAYER_DIMENSIONS;
extern const float PLAYER_MAX_SPEED;

enum BoundaryType {
    Bouncy, Functional
};

enum class Keys { UP, DOWN, LEFT, RIGHT };

#endif
