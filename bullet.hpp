#pragma once 

#include <SFML/Graphics.hpp>

class Bullet : public sf::Transformable, public sf::Drawable {
    sf::CircleShape shape;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:
    float moveSpeed;
    float direction;
    sf::Clock lifeTime;
    Bullet(int x, int y, float dir, float speed = 200.f /*, int dir*/);
};