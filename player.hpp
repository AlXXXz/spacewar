#pragma once

#include <SFML/Graphics.hpp>

class Player : public sf::Transformable, public sf::Drawable {
    
    int health;

    sf::CircleShape shape;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:
    float moveSpeed;
    float rotateSpeed;
    float rotateAngle;
    Player();
    void setHealth(int value);
    int getHealth();
};
