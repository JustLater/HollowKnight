#ifndef HOLLOW_FIREBALL_H
#define HOLLOW_FIREBALL_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "knight.h"

class Knight;

class FireBall {
public:
    FireBall() {
        fireTexture.loadFromFile("D://study//hollow//enemy//fire.png");
        fireSprite1.setTexture(fireTexture);
        fireSprite1.setTextureRect(sf::IntRect(0, 0, 103, 93));
        fireSprite2.setTexture(fireTexture);
        fireSprite2.setTextureRect(sf::IntRect(0, 0, 103, 93));
        fireSprite3.setTexture(fireTexture);
        fireSprite3.setTextureRect(sf::IntRect(0, 0, 103, 93));

        fireSprite1.setPosition(-100, -100);
        fireSprite2.setPosition(-100, -100);
        fireSprite3.setPosition(-100, -100);

        currentFrame = 0;
        animationClock.restart();
    }

    void update(Knight &knight);

    sf::FloatRect getGlobalBounds(sf::Vector2f position) {
        sf::FloatRect bounds;
        bounds.left = position.x;
        bounds.top = position.y;
        bounds.width = 103;
        bounds.height = 93;
        return bounds;
    }

    void draw(sf::RenderWindow& window) {
        if (isAnimation) {
            window.draw(fireSprite1);
            window.draw(fireSprite2);
            window.draw(fireSprite3);
        }
    }

    void setPositions (sf::Vector2f start, float speed) {
        movementSpeed = speed;
        sf::Vector2f startPos(start.x - 10, start.y + 100);
        firePosition1 = startPos;
        firePosition2 = startPos;
        firePosition3 = startPos;
        firefirefire = true;
    }

private:
    sf::Texture fireTexture;
    sf::Sprite fireSprite1;
    sf::Sprite fireSprite2;
    sf::Sprite fireSprite3;

    sf::Vector2f firePosition1;
    sf::Vector2f firePosition2;
    sf::Vector2f firePosition3;

    bool firefirefire = false;
    sf::Clock animationClock;
    int currentFrame;
    float animationSpeed = 0.6f;
    float movementSpeed;
    bool isAnimation = false; // Флаг для проверки состояния анимации
    int attackCount;

};
#endif //HOLLOW_FIREBALL_H
