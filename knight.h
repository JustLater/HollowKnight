#ifndef HOLLOW_KNIGHT_H
#define HOLLOW_KNIGHT_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "enemy.h"
#include "largerEnemy.h"
#include "theLargestEnemy.h"

class Knight
{
public:
    Knight()
    {
        // Загрузка текстур персонажа для анимаций
        characterTexture.loadFromFile("D://study//hollow//sprites//idle.png");
        jumpTexture.loadFromFile("D://study//hollow//sprites//newjump.png");
        attackTexture.loadFromFile("D://study//hollow//sprites//attack.png");
        deathTexture.loadFromFile("D://study//hollow//sprites//death.png");

        //здоровье персонажа
        maskTexture.loadFromFile("D://study//hollow//sprites//mask.png");
        for (int i = 0; i < maxMask; i++) {
            maskSprites[i].setTexture(maskTexture);
        }
        maskDropTexture.loadFromFile("D://study//hollow//sprites//maskdrop.png");
        maskDropSprite.setTexture(maskDropTexture);
        maskDropSprite.setTextureRect(sf::IntRect(0, 0, 83, 120));
        // Установка позиций каждой маски
        for (int i = 0; i < maxMask; i++) {
            maskSprites[i].setPosition(40.f + i * 75.f, 40.f);
        }

        // Создание спрайта персонажа для обычной анимации
        characterSprite.setTexture(characterTexture);
        characterSprite.setTextureRect(sf::IntRect(0, 0, 100, 140)); // Размер одного кадра анимации
        characterSprite.setPosition(400, 800);

        characterPosition = characterSprite.getPosition();

        // Создание спрайта персонажа для анимации прыжка
        jumpSprite.setTexture(jumpTexture);
        jumpSprite.setTextureRect(sf::IntRect(0, 0, 135, 140)); // Размер одного кадра анимации прыжка
        jumpSprite.setPosition(400, 800);

        attackSprite.setTexture(attackTexture);
        attackSprite.setTextureRect(sf::IntRect(0, 0, 260, 140));
        attackSprite.setPosition(400, 800);

        deathSprite.setTexture(deathTexture);
        deathSprite.setTextureRect(sf::IntRect(0, 0, 128, 135));
        deathSprite.setPosition(400, 800);

        //музыка
        jumpMusic.openFromFile("D://study//hollow//sounds//hero//jump.wav");
        attackMusic.openFromFile("D://study//hollow//sounds//hero//hit.wav");
        hitMusic.openFromFile("D://study//hollow//sounds//hero//damage.wav");

        jumpMusic.setVolume(50);
        attackMusic.setVolume(50);
        hitMusic.setVolume(50);

        // Индекс текущего кадра анимации
        currentFrame = 0;
        jumpCurrentFrame = 0;
        attackCurrentFrame = 0;

        // Таймер для переключения кадров анимации
        animationClock.restart();
    }

    void update(bool isLeftPressed, bool isRightPressed, bool isJumpPressed,
                bool isAttackPressed, Enemy &enemy, LargerEnemy &largerEnemy, TheLargestEnemy &theLargestEnemy);

    void draw(sf::RenderWindow& window);

    sf::Vector2f getPosition() {
        return characterPosition;
    }

    void decreaseHealth() {
        maxMask--;
        hitMusic.play();
        if (maxMask == 0) {
            isDead = true;
        }
    }

    bool isAlive() const {
        if(!isNowReallyDead) {
            return true;
        }
        return false;
    }

    sf::FloatRect getGlobalBounds() const {
        sf::FloatRect bounds;
        bounds.left = characterPosition.x;
        bounds.top = characterPosition.y;
        bounds.width = 100;
        bounds.height = 140;
        return bounds;
    }

private:
    sf::Music attackMusic;
    sf::Music hitMusic;
    sf::Music jumpMusic;

    sf::Texture characterTexture;
    sf::Sprite characterSprite;

    sf::Texture jumpTexture;
    sf::Sprite jumpSprite;

    sf::Texture attackTexture;
    sf::Sprite attackSprite;

    sf::Texture deathTexture;
    sf::Sprite deathSprite;

    //шкала здоровья
    sf::Texture maskTexture;
    sf::Sprite maskSprites[5];
    sf::Sprite maskDropSprite;
    sf::Texture maskDropTexture;
    sf::Clock maskClock;
    int maskCurrentFrame = 0;

    bool lessHealth = false;
    bool isDead = false;
    bool isNowReallyDead = false;
    bool isDeathAnimating = false;
    int maxMask = 4;

    int currentFrame;
    int jumpCurrentFrame;
    int attackCurrentFrame;
    int deathCurrentFrame;

    float movementSpeed = 3.0f;
    float jumpSpeed = 25.0f;
    float gravity = 1.0f;

    //прыжок
    bool isJumping = false;
    bool isJumpingAnimation = false;
    bool hasJumped = false;
    bool hasJumpKeyPressed = false;

    //атака
    bool isAttacking = false;
    bool isAttackingAnimation = false;
    bool hasAttacked = false;
    bool hasAttackKeyPressed = false;

    float verticalVelocity = 0.0f;

    sf::Clock animationClock;
    float animationSpeed = 0.4f;
    float attackanimationSpeed = 0.1f;

    sf::Vector2f characterPosition;

    //ограничение по передвижению
    float minX = 0;
    float maxX = 1800;
    float minY = 0;
    float maxY = 1000;

};

#endif //HOLLOW_KNIGHT_H
