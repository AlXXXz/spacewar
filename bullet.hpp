#pragma once 

#include <SFML/Graphics.hpp>
#include "bullet.hpp"

/**
 * @brief Класс реализующий выстрел
 */
class Bullet : public sf::Transformable, public sf::Drawable {
    friend class Game;

    sf::CircleShape shape;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    float moveSpeed;
    float direction;
    sf::Clock lifeTime;

public:
    Bullet(int x, int y, float dir, float speed = 200.f /*, int dir*/);
};