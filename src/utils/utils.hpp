#ifndef UTILS_HPP
#define UTILS_HPP

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include "../constants/constants.hpp"

class PlayerKeyBindingsBuilder {
private:
    std::unordered_map<Keys, sf::Keyboard::Key> keyBindings;

public:
    PlayerKeyBindingsBuilder& setUp(sf::Keyboard::Key key);
    PlayerKeyBindingsBuilder& setDown(sf::Keyboard::Key key);
    PlayerKeyBindingsBuilder& setLeft(sf::Keyboard::Key key);
    PlayerKeyBindingsBuilder& setRight(sf::Keyboard::Key key);

    std::unordered_map<Keys, sf::Keyboard::Key> build();
};

#endif