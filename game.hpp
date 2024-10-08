#pragma once

#include <SFML/Graphics.hpp>
#include "bullet.hpp"

/**
 * @name Game
 * @brief Главный класс игры, отвечающий за всю внутриигровую логику
 * 
 * @details Класс отвечает за:
 * 1. Создание и обновление окна
 * 2. Отрисовку
 * 3. Отслеживанием ввода
 * 4. Обработкой событий  
 */
class Game {
    sf::RenderWindow window;
    sf::Event event;

    sf::CircleShape triangle;

    bool isMovingUp;
    bool isMovingDown;
    bool isMovingLeft;
    bool isMovingRight; 

    float PlayerSpeed = 100;

    /**
     * @brief Отслеживание ввода 
     */
    void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
    /**
     * @brief обработка событий 
     */
    void processEvents();
    /**
     * @brief Обновление игрового процесса 
     */
    void update(sf::Time deltaTime);
    /**
     * @brief Отрисовка игры
     */
    void render();


public:
    Game();
    void run();
};