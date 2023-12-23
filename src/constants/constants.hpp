#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <SFML/Graphics.hpp>

extern const int WINDOW_HEIGHT;
extern const int WINDOW_WIDTH;
extern const int DISTANCE_TO_BORDER;
extern const float BOUNCE_FACTOR;
extern const int BALL_SIDE_LEN;
extern const int BALL_TAIL_LEN;
extern const float BALL_FRICTION;
extern const float BALL_SPEED_UP;
extern const float MAX_BALL_SPEED;
extern const sf::Vector2f PLAYER_DIMENSIONS;
extern const float PLAYER_MAX_SPEED;
extern const int MAX_SCORE;

enum BoundaryType {
    Bouncy, Functional
};

enum class PlayerType {
    Left, Right
};

enum class GameState {
    Playing, Paused, StartScreen, GameOver
};

enum class Keys { UP, DOWN, LEFT, RIGHT };

#endif
