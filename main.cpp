#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

const int WINDOW_HEIGHT = 800; //Lös detta på ett bättre sätt sen
const int WINDOW_WIDTH = 1200; //Lös detta på ett bättre sätt sen
const int DISTANCE_TO_BORDER = 30;
const int INITIAL_PLAYER_SPEED = 8;
const int ballSide = 15;
sf::Vector2f PLAYER_DIMENSIONS(25, 200);

enum Keys 
{
    UP, DOWN
};

class Ball 
{
public:
    sf::RectangleShape body;
    sf::Vector2f speed;

    void handleMovement() 
    {
        auto currentPos = body.getPosition();
        if (currentPos.y <= 0 || currentPos.y >= WINDOW_HEIGHT - ballSide) {
            speed.y = -speed.y;
        }         


        auto nextPos = currentPos + speed;
        nextPos.y = std::min(WINDOW_HEIGHT - ballSide, std::max(0, (int) nextPos.y));

        body.setPosition(nextPos);
    }

    Ball() :
    speed(sf::Vector2f(5, 8)),
    body(sf::RectangleShape(sf::Vector2f(ballSide, ballSide)))
    {
        body.setPosition(WINDOW_WIDTH / 2 - ballSide / 2, WINDOW_HEIGHT / 2 - ballSide / 2);
    }



};

class Player 
{
public:
    int playerSpeed;
    sf::Vector2f pos;
    sf::RectangleShape body;
    std::unordered_map<Keys, sf::Keyboard::Key> keyBindings;

    Player(int defaultX, std::unordered_map<Keys, sf::Keyboard::Key> keyBindings) : 
    pos(defaultX, (WINDOW_HEIGHT / 2) - (PLAYER_DIMENSIONS.y / 2)),
    keyBindings(keyBindings),
    playerSpeed(INITIAL_PLAYER_SPEED),
    body()
    {
        body.setSize(PLAYER_DIMENSIONS);
        body.setPosition(pos);
    }

    void handleMovement() 
    {
        if (sf::Keyboard::isKeyPressed(keyBindings[UP])) {
            int newPos = body.getPosition().y - playerSpeed;
            body.setPosition(pos.x, std::max(0, newPos));
        }   
        if (sf::Keyboard::isKeyPressed(keyBindings[DOWN])) {
            int newPos = body.getPosition().y + playerSpeed;
            body.setPosition(pos.x, std::min(WINDOW_HEIGHT - (int) PLAYER_DIMENSIONS.y, newPos));
        }   
    }

    void handleBallCollision(Ball& ball) 
    {
        auto ballPos = ball.body.getPosition();
        auto playerPos = body.getPosition();
        int leftSide = playerPos.x;
        int rightSide = leftSide + PLAYER_DIMENSIONS.x;

        if (ball.speed.x < 0) 
        {
            if (ballPos.x >= leftSide && ballPos.x <= rightSide) 
            {
                ball.speed.x = -ball.speed.x;
            }
        } 

        else  
        {
            if (ballPos.x + ballSide >= leftSide && ballPos.x + ballSide <= rightSide) 
            {
                ball.speed.x = -ball.speed.x;
            }
        }
    }
};


int main()
{
    std::unordered_map<Keys, sf::Keyboard::Key> pLeftBindings{
        {Keys::UP, sf::Keyboard::Key::W},
        {Keys::DOWN, sf::Keyboard::Key::S}
    };

    std::unordered_map<Keys, sf::Keyboard::Key> pRightBindings{
        {Keys::UP, sf::Keyboard::Key::Up},
        {Keys::DOWN, sf::Keyboard::Key::Down}};

    std::vector<Player*> players;
    Player pLeft(DISTANCE_TO_BORDER, pLeftBindings);
    Player pRight(WINDOW_WIDTH - (DISTANCE_TO_BORDER + PLAYER_DIMENSIONS.x), pRightBindings);
    players.push_back(&pLeft);
    players.push_back(&pRight);

    Ball ball;

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML works!");
    window.setFramerateLimit(60);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }


        window.clear();
        for (Player* player : players) {
            player->handleMovement();
            player->handleBallCollision(ball);
            window.draw(player->body);
        }

        ball.handleMovement(); window.draw(ball.body);

        window.display();
    }

    return 0;
}
