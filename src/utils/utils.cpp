#include "utils.hpp"

std::unordered_map<Keys, sf::Keyboard::Key> playerKeyBindings(sf::Keyboard::Key up, sf::Keyboard::Key down)
{
    return {
        {Keys::UP, up},
        {Keys::DOWN, down}
    };
}

bool areRectanglesOverlapping(
    const sf::Vector2f& rectATopLeft,
    const sf::Vector2f& rectABottomRight,
    const sf::Vector2f& rectBTopLeft,
    const sf::Vector2f& rectBBottomRight) {

    // Check for non-overlapping conditions along the x-axis
    if (rectATopLeft.x > rectBBottomRight.x || rectABottomRight.x < rectBTopLeft.x)
        return false;

    // Check for non-overlapping conditions along the y-axis
    if (rectATopLeft.y > rectBBottomRight.y || rectABottomRight.y < rectBTopLeft.y)
        return false;

    // If not non-overlapping along both axes, rectangles are overlapping or touching
    return true;
}

