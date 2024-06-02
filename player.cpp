#include "player.hpp"

Player::Player() : shape(50.f, 3) {
    shape.setFillColor(sf::Color::Cyan);
    health = 100;
    moveSpeed = 100.f;
    rotateSpeed = 100.f;
    rotateAngle = 1;
    shape.setScale(0.5, 1);
    shape.setOrigin(50, 50);
}

void Player::setHealth(int value) {
    health = value;
}

int Player::getHealth() {
    return health;
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(shape, states);
}