#include "utils.hpp"

std::unordered_map<Keys, sf::Keyboard::Key> playerKeyBindings(sf::Keyboard::Key up, sf::Keyboard::Key down)
{
    return {
        {Keys::UP, up},
        {Keys::DOWN, down}
    };
}
