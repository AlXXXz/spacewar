#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "bullet.hpp"

class Player : public sf::Transformable, public sf::Drawable {
    
    int health;

    sf::CircleShape shape;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:
    std::vector<Bullet> bullets;
    float moveSpeed;
    float rotateSpeed;
    float rotateAngle;
    Player();
    void setHealth(int value);
    int getHealth();
};
