#ifndef BOUNDARY_HPP
#define BOUNDARY_HPP

#include "Entity.hpp"
#include "../constants/constants.hpp"
#include <functional>

class Boundary : public Entity {
    public:
        Boundary(std::function<void()> func, const sf::Vector2f& pos, const sf::Vector2f& dim, BoundaryType type);
        void onCollision();
        BoundaryType type;
        void handleMovement() override;
        void update() override;

    private:
        std::function<void()> func;

};



#endif