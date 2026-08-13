#ifndef HOLLOW_THELARGESTENEMY_H
#define HOLLOW_THELARGESTENEMY_H

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

class TheLargestEnemy {
public:
    TheLargestEnemy() {

        // Загрузка текстур и инициализация анимаций
        idleTexture.loadFromFile("D://study//hollow//enemy//idle3.png");
        idleSprite.setTexture(idleTexture);
        idleSprite.setTextureRect(sf::IntRect(0, 0, (2115.f/10), 457));

        teleportTexture.loadFromFile("D://study//hollow//enemy//teleport3.png");
        teleportSprite.setTexture(teleportTexture);
        teleportSprite.setTextureRect(sf::IntRect(0, 0, 265, 511));

        attackTexture.loadFromFile("D://study//hollow//enemy//attack3.png");
        attackSprite.setTexture(attackTexture);
        attackSprite.setTextureRect(sf::IntRect(0, 0, 355, 460));

        disappearTexture.loadFromFile("D://study//hollow//enemy//disappear3.png");
        disappearSprite.setTexture(disappearTexture);
        disappearSprite.setTextureRect(sf::IntRect(0, 0, (2650.f/10), 511));

        deathTexture.loadFromFile("D://study//hollow//enemy//alldeath3.png");
        deathSprite.setTexture(deathTexture);
        deathSprite.setTextureRect(sf::IntRect(0, 0, (2300.f/9), 917));

        //помещаем персонажа в начальную точку
        idleSprite.setPosition(enemyPosition);
        teleportSprite.setPosition(enemyPosition);
        attackSprite.setPosition(enemyPosition);
        disappearSprite.setPosition(enemyPosition);
        deathSprite.setPosition(enemyPosition);

        attackMusic.openFromFile("D://study//hollow//sounds//tLE_attack.wav");
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

    float animationSpeed = 0.07f;

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

#endif //HOLLOW_THELARGESTENEMY_H
