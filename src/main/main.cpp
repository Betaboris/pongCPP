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
        state = GameState::Paused;
    }
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

        sf::Text text;
        text.setFont(font);
        text.setCharacterSize(50);
        text.setFillColor(sf::Color::White);

        switch (gameState)
        {
        case GameState::Playing:
            //playingLoop();
            break;

        case GameState::Paused:
            //Exempelkod för att se så att det funkar
            std::this_thread::sleep_for(std::chrono::milliseconds(2000));
            gameState = GameState::Playing;
            break;

        case GameState::StartScreen:
            //Också scuffed exempelkod
            window.clear();
            text.setString("Press space to start");
            text.setPosition(sf::Vector2f((WINDOW_WIDTH - text.getLocalBounds().width) / 2, (WINDOW_HEIGHT - text.getLocalBounds().height) / 2));
            window.draw(text);
            window.display();

            while (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                continue;
            }

            gameState = GameState::Playing;
            break;

        case GameState::GameOver:
            //Också scuffed exempelkod
            window.clear();
            text.setString("Game over");
            text.setPosition(sf::Vector2f((WINDOW_WIDTH - text.getLocalBounds().width) / 2, (WINDOW_HEIGHT - text.getLocalBounds().height) / 2));
            window.draw(text);
            window.display();

            while (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || !sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                continue;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                gameState = GameState::Playing;
                //Reset game
            } else {
                exit(0);
            }

            gameState = GameState::StartScreen;
            break;
        }

        window.clear();
        Entity::updateAll(window, entities);
        drawScores(window, players);
        window.display();
    }

    return 0;
}
