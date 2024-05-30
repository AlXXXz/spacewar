#pragma once

#include <SFML/Graphics.hpp>

class Game {
    sf::RenderWindow window;
    sf::Event event;

    sf::CircleShape triangle;

    bool isMovingUp;
    bool isMovingDown;
    bool isMovingLeft;
    bool isMovingRight; 

    float PlayerSpeed = 100;

    void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
    void processEvents();
    void update(sf::Time deltaTime);
    void render();

public:
    Game();
    void run();
};