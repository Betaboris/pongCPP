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
