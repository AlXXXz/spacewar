#include "bullet.hpp"

Bullet::Bullet(int x, int y, float speed/*, int dir*/) : shape(5.f) {
    shape.setFillColor(sf::Color::Red);
    shape.setPosition(x, y);
    lifeTime.restart();
    moveSpeed = speed;
}

void Bullet::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(shape, states);
}