/*
TODO: Реализовать движение игрока внутри класса Player
*/


#include "game.hpp"
#include "player.hpp"
#include <iostream>
#include <cmath>

#define DEBUG_SHIT 1

Player player;

Game::Game() : window(sf::VideoMode(800, 600), "Spacewar") {
    
    // player.setScale(0.5, 1);
    // player.setOrigin(50, 50);

    isMovingDown = false;
    isMovingUp = false;
    isMovingLeft = false;
    isMovingRight = false;

    player.setPosition(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2));
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed) {
#if DEBUG_SHIT
    if (key == sf::Keyboard::Z && player.getHealth() > 0)
        player.setHealth(10);
#endif

    if (player.getHealth() > 0) {
        if (key == sf::Keyboard::W)
            isMovingUp = isPressed;
        else if (key == sf::Keyboard::S)
            isMovingDown = isPressed;
        else if (key == sf::Keyboard::A)
            isMovingLeft = isPressed;
        else if (key == sf::Keyboard::D)
            isMovingRight = isPressed;

        if (key == sf::Keyboard::Space) {
            player.bullets.push_back(Bullet(player.getPosition().x, player.getPosition().y, player.getRotation()));
        }
    }
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
        //inertia = movement;
    }

    if (isMovingDown) 
        movement.y += player.moveSpeed;

    

    for (int i = 0; i < (int)player.bullets.size(); i++) {
        player.bullets[i].move(
            -(player.bullets[i].moveSpeed * sin(-player.bullets[i].direction * M_PI / 180)) * deltaTime.asSeconds(),
            -(player.bullets[i].moveSpeed * cos(-player.bullets[i].direction * M_PI / 180)) * deltaTime.asSeconds()
            );
        auto iter = player.bullets.cbegin();
        if (player.bullets[i].lifeTime.getElapsedTime().asMilliseconds() >= 1500) {
            //player.bullets.pop_back();
            player.bullets.erase(iter);
        }
    }
    
    //movement += inertia;

    //std::cout << "(" << player.getPosition().x << ":" << player.getPosition().y << ") " << movement.x << " " << movement.y << " " << inertia.x << " " << inertia.y << std::endl;

    //std::cout << elapsed.asMilliseconds() << std::endl;

    std::cout << player.getRotation() << std::endl;

    player.move(movement * deltaTime.asSeconds());
}

void Game::render() {
    

    window.clear();
    if (player.getHealth() > 0)
        window.draw(player);
    for (int i = 0; i < (int)player.bullets.size(); i++) {
        window.draw(player.bullets[i]);
    }

#if DEBUG_SHIT
    sf::Font font;
    sf::Text text;
    if (!font.loadFromFile("arial.ttf")) {
        std::cout << "Error while loading font\n";
    }
    text.setFont(font);    
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    text.setString("Pos: " + std::to_string(player.getPosition().x) + " " 
        + std::to_string(player.getPosition().y) + "\nRotation: " 
        + std::to_string(player.getRotation()) + "\nBullets: " 
        + std::to_string(player.bullets.size()) + "\nPlayer's health: "
        + std::to_string(player.getHealth()));
    //text.setStyle(sf::Text::Bold | sf::Text::Underlined);
    window.draw(text);
    window.draw(text);
#endif

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