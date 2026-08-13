#ifndef HOLLOW_LARGERENEMY_H
#define HOLLOW_LARGERENEMY_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <SFML/System/Clock.hpp>
#include <cstdlib>
#include <ctime>
#include "knight.h"
#include "fireball.h"

class FireBall;

class Knight;

class LargerEnemy {
public:
    LargerEnemy() {

        // Загрузка текстур и инициализация анимаций
        idleTexture.loadFromFile("D://study//hollow//enemy//idle2.png");
        idleSprite.setTexture(idleTexture);
        idleSprite.setTextureRect(sf::IntRect(0, 0, (2199.f/10), 418));

        teleportTexture.loadFromFile("D://study//hollow//enemy//teleport2.png");
        teleportSprite.setTexture(teleportTexture);
        teleportSprite.setTextureRect(sf::IntRect(0, 0, (2622.f/9), 417));

        attackTexture.loadFromFile("D://study//hollow//enemy//attack2.png");
        attackSprite.setTexture(attackTexture);
        attackSprite.setTextureRect(sf::IntRect(0, 0, 315, 460));

        disappearTexture.loadFromFile("D://study//hollow//enemy//disappear2.png");
        disappearSprite.setTexture(disappearTexture);
        disappearSprite.setTextureRect(sf::IntRect(0, 0, 255, 417));

        deathTexture.loadFromFile("D://study//hollow//enemy//alldeath2.png");
        deathSprite.setTexture(deathTexture);
        deathSprite.setTextureRect(sf::IntRect(0, 0, 255, 917));

        //помещаем персонажа в начальную точку
        idleSprite.setPosition(enemyPosition);
        teleportSprite.setPosition(enemyPosition);
        attackSprite.setPosition(enemyPosition);
        disappearSprite.setPosition(enemyPosition);
        deathSprite.setPosition(enemyPosition);

        //музыка
        attackMusic.openFromFile("D://study//hollow//sounds//LE_attack.wav");
        attackMusic.setVolume(50);
        deathMusic.openFromFile("D://study//hollow//sounds//death.wav");
        deathMusic.setVolume(50);

        // Задаем начальное состояние персонажа
        currentState = Teleport;
        animationClock.restart();
        currentFrame = 0;
    }

    void update(Knight &knight, FireBall &fireBall);

    void draw(sf::RenderWindow& window, FireBall &fireBall);

    void teleport();

    void idle();

    void attack(Knight &knight, FireBall &fireBall);

    void disappear();

    void dead();

    void getHit() {
        enemyHealth -= 20;
    }

    bool isAlive() const {
        if(!isDead) {
            return true;
        }
        return false;
    }

    sf::FloatRect getGlobalBounds() const {
        sf::FloatRect bounds;
        bounds.left = enemyPosition.x;
        bounds.top = enemyPosition.y;
        bounds.width = 160;
        bounds.height = 410;
        return bounds;
    }


private:
    sf::Sprite idleSprite;
    sf::Sprite teleportSprite;
    sf::Sprite attackSprite;
    sf::Sprite disappearSprite;
    sf::Sprite deathSprite;

    sf::Texture idleTexture;
    sf::Texture teleportTexture;
    sf::Texture attackTexture;
    sf::Texture disappearTexture;
    sf::Texture deathTexture;

    sf::Music attackMusic;
    sf::Music deathMusic;

    int enemyHealth = 140;

    sf::Vector2f enemyPosition = sf::Vector2f(1000, 500);

    bool isDone = false;
    bool isDead = false;
    bool DMplaying = false;

    float animationSpeed = 0.10f;

    enum State {
        Teleport,
        Idle,
        Attack,
        Disappear,
        Dead
    };

    State currentState;
    sf::Clock animationClock;
    int currentFrame;

    int attackCount = 0;

};

#endif //HOLLOW_LARGERENEMY_H
