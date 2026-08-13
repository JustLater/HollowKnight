#ifndef HOLLOW_ENEMY_H
#define HOLLOW_ENEMY_H

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

class Enemy {
public:
    Enemy() {

        // Загрузка текстур и инициализация анимаций
        idleTexture.loadFromFile("D://study//hollow//enemy//idle1.png");
        idleSprite.setTexture(idleTexture);
        idleSprite.setTextureRect(sf::IntRect(0, 0, 159, 410));

        teleportTexture.loadFromFile("D://study//hollow//enemy//teleport1.png");
        teleportSprite.setTexture(teleportTexture);
        teleportSprite.setTextureRect(sf::IntRect(0, 0, (2361.f/9), 426));

        attackTexture.loadFromFile("D://study//hollow//enemy//atttack1.png");
        attackSprite.setTexture(attackTexture);
        attackSprite.setTextureRect(sf::IntRect(0, 0, 376, 410));

        disappearTexture.loadFromFile("D://study//hollow//enemy//disappear1.png");
        disappearSprite.setTexture(disappearTexture);
        disappearSprite.setTextureRect(sf::IntRect(0, 0, (2624.f/10), 426));

        deathTexture.loadFromFile("D://study//hollow//enemy//alldeath1.png");
        deathSprite.setTexture(deathTexture);
        deathSprite.setTextureRect(sf::IntRect(0, 0, 182, 661));

        //помещаем персонажа в начальную точку
        idleSprite.setPosition(enemyPosition);
        teleportSprite.setPosition(enemyPosition);
        attackSprite.setPosition(enemyPosition);
        disappearSprite.setPosition(enemyPosition);
        deathSprite.setPosition(enemyPosition);

        //музыка
        attackMusic.openFromFile("D://study//hollow//sounds//E_attack.wav");
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

    bool isAttacking () {
        return Attacks;
    }

    sf::Vector2f getPosition() {
        return enemyPosition;
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

    int enemyHealth = 80;

    sf::Vector2f enemyPosition = sf::Vector2f(1000, 500);

    bool isDone = false;
    bool isDead = false;
    bool DMplaying = false;

    float animationSpeed = 0.15f;

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
    bool Attacks = false;
};

#endif //HOLLOW_ENEMY_H
