#include "../headers/game.hpp"
#include "../headers/player.hpp"
#include <iostream>
#include <cmath>

Player player;

Game::Game() : window(sf::VideoMode(800, 600), "Spacewar") {
    
    // player.setScale(0.5, 1);
    // player.setOrigin(50, 50);

    player.setPosition(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2));
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed) {
    if (key == sf::Keyboard::W)
        isMovingUp = isPressed;
    else if (key == sf::Keyboard::S)
        isMovingDown = isPressed;
    else if (key == sf::Keyboard::A)
        isMovingLeft = isPressed;
    else if (key == sf::Keyboard::D)
        isMovingRight = isPressed;
}

void Game::processEvents() {
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) window.close();

        switch (event.type) {
        case sf::Event::KeyPressed:
            handlePlayerInput(event.key.code, true);
            break;
        case sf::Event::KeyReleased:
            handlePlayerInput(event.key.code, false);
            break;
        }
    }
}

void Game::update(sf::Time deltaTime) {
    sf::Vector2f movement(0.f, 0.f);

    static sf::Vector2f inertia(0.f, 0.f);

    if (isMovingRight)
        player.rotate(player.rotateAngle * deltaTime.asSeconds() * player.rotateSpeed);

    if (isMovingLeft)
        player.rotate(-(player.rotateAngle * deltaTime.asSeconds() * player.rotateSpeed));

    
    if (isMovingUp) {
        movement.y -= player.moveSpeed * cos(player.getRotation() * M_PI / 180);
        movement.x += player.moveSpeed * sin(player.getRotation() * M_PI / 180);
        inertia = movement;
    }

    if (isMovingDown) 
        movement.y += player.moveSpeed;

    movement += inertia;

    std::cout << "(" << player.getPosition().x << ":" << player.getPosition().y << ") " << movement.x << " " << movement.y << " " << inertia.x << " " << inertia.y << std::endl;

    player.move(movement * deltaTime.asSeconds());
}

void Game::render() {
    window.clear();
    window.draw(player);
    window.display();
}

void Game::run() {
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    while (window.isOpen()) {
        processEvents();
        timeSinceLastUpdate += clock.restart();

        while (timeSinceLastUpdate > sf::seconds(1.f / 60.f)) {
            timeSinceLastUpdate -= sf::seconds(1.f / 60.f);
            processEvents();
            update(sf::seconds(1.f / 60.f));
        }
        render();
    }
}