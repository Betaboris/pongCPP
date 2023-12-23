#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "../constants/constants.hpp"
#include "../entities/all_entities.hpp"
#include "../utils/utils.hpp"
#include <chrono>
#include <thread>

const sf::Font font = []() {
    sf::Font font;
    font.loadFromFile("../src/fonts/Roboto-Regular.ttf");
    return font;
}();

Boundary createWall(const sf::Vector2f& position, const sf::Vector2f& size, const BoundaryType& type, std::function<void()> callback = nullptr) {
    return Boundary(position, size, type, callback);
}

Player createPlayer(const sf::Vector2f& position, const std::unordered_map<Keys, sf::Keyboard::Key>& keyBindings, PlayerType type) {
    return Player(position, keyBindings, type);
}


std::unordered_map<Keys, sf::Keyboard::Key> buildKeyBindings(sf::Keyboard::Key upKey, sf::Keyboard::Key downKey) {
    PlayerKeyBindingsBuilder builder;
    return builder.setUp(upKey).setDown(downKey).build();
}

Player createPlayer(PlayerType type) {
    switch (type)
    {
    case PlayerType::Left:
        return createPlayer(sf::Vector2f(DISTANCE_TO_BORDER, (WINDOW_HEIGHT - PLAYER_DIMENSIONS.y) / 2.0f), 
        buildKeyBindings(sf::Keyboard::Key::W, sf::Keyboard::Key::S),
        type);
    case PlayerType::Right:
        return createPlayer(sf::Vector2f(WINDOW_WIDTH - (DISTANCE_TO_BORDER + PLAYER_DIMENSIONS.x), 
        (WINDOW_HEIGHT - PLAYER_DIMENSIONS.y) / 2.0f), buildKeyBindings(sf::Keyboard::Key::Up, sf::Keyboard::Key::Down),
        type);
    }
}

void drawScores(sf::RenderWindow& window, const std::vector<Player*>& players) {
    for (auto& player : players) {
        sf::Text scoreText;
        scoreText.setFont(font);
        scoreText.setCharacterSize(50);
        scoreText.setFillColor(sf::Color::White);
        scoreText.setPosition(scorePositions[player->type]);
        scoreText.setString(std::to_string(player->score));
        window.draw(scoreText);
    }
}

void score(Player& player, GameState& state) {
    player.score++;
    if (player.score >= MAX_SCORE) {
        state = GameState::GameOver;
    } else {
        //state = GameState::Paused;
    }
}

void drawCenteredText(std::string text, sf::RenderWindow& window, int size = 50, sf::Color color = sf::Color::White) {
    sf::Text textObj;
    textObj.setFont(font);
    textObj.setCharacterSize(size);
    textObj.setFillColor(color);
    textObj.setString(text);
    textObj.setPosition(sf::Vector2f((WINDOW_WIDTH - textObj.getLocalBounds().width) / 2, (WINDOW_HEIGHT - textObj.getLocalBounds().height) / 2));
    window.draw(textObj);
}

int main() {
    GameState gameState = GameState::StartScreen;

 // Calculate the vertical center position for the players
    float centerY = (WINDOW_HEIGHT - PLAYER_DIMENSIONS.y) / 2.0f;

    // Create the left player
    Player pLeft = createPlayer(PlayerType::Left);

    // Create the right player, adjusting position for the player's width
    Player pRight = createPlayer(PlayerType::Right);

    std::vector<Boundary> walls = {
        createWall(sf::Vector2f(-50, 0), sf::Vector2f(50, WINDOW_HEIGHT), Functional, [&pRight, &gameState]() {score(pRight, gameState);}),
        createWall(sf::Vector2f(WINDOW_WIDTH, 0), sf::Vector2f(50, WINDOW_HEIGHT), Functional, [&pLeft, &gameState]() {score(pLeft, gameState);}),
        createWall(sf::Vector2f(0, -50), sf::Vector2f(WINDOW_WIDTH, 50), Bouncy),
        createWall(sf::Vector2f(0, WINDOW_HEIGHT), sf::Vector2f(WINDOW_WIDTH, 50), Bouncy)
    };

    for (auto& wall : walls) {
        Ball::boundaries.insert(&wall);
        Player::boundaries.insert(&wall);
    } 

    Ball ball;
    Player::boundaries.insert(&ball);

    std::vector<Player*> players = {&pLeft, &pRight};

    for (auto& player : players) {
        Ball::players.insert(player);
    }

    std::vector<Entity*> entities = {&pLeft, &pRight, &ball};

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "PONG");
    window.setFramerateLimit(60);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        switch (gameState)
        {
        case GameState::Playing:
            Entity::updateAll(window, entities);
            ball.drawTails(window);
            drawScores(window, players);
            break;

        case GameState::Paused:
            drawCenteredText("PAUSED", window, 10);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                gameState = GameState::Playing;
            }
            break;

        case GameState::StartScreen:
            drawCenteredText("Press space to start", window);

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                gameState = GameState::Playing;
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
                exit(0);
            }
            break;

        case GameState::GameOver:
            //Också scuffed exempelkod
            drawCenteredText("Game over\nPress space to play again, esc to exit", window);

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                gameState = GameState::Playing;
                //Reset scores, TODO also reset positions?
                for (auto p : players) {
                    p->score = 0;
                }
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
                exit(0);
            }
            break;
        }

        window.display();
    }

    return 0;
}
