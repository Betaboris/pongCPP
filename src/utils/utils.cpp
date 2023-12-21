#include "utils.hpp"

PlayerKeyBindingsBuilder& PlayerKeyBindingsBuilder::setUp(sf::Keyboard::Key key) {
    keyBindings[Keys::UP] = key;
    return *this;
}

PlayerKeyBindingsBuilder& PlayerKeyBindingsBuilder::setDown(sf::Keyboard::Key key) {
    keyBindings[Keys::DOWN] = key;
    return *this;
}

PlayerKeyBindingsBuilder& PlayerKeyBindingsBuilder::setLeft(sf::Keyboard::Key key) {
    keyBindings[Keys::LEFT] = key;
    return *this;
}

PlayerKeyBindingsBuilder& PlayerKeyBindingsBuilder::setRight(sf::Keyboard::Key key) {
    keyBindings[Keys::RIGHT] = key;
    return *this;
}

std::unordered_map<Keys, sf::Keyboard::Key> PlayerKeyBindingsBuilder::build() {
    return keyBindings;
}

std::unordered_map<PlayerType, sf::Vector2f> scorePositions = 
{
    { PlayerType::Left, sf::Vector2f(WINDOW_WIDTH / 2.0f - 100, 50) },
    { PlayerType::Right, sf::Vector2f(WINDOW_WIDTH / 2.0f + 100, 50) }
};
