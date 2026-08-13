#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <cstdlib>
#include <math.h>
#include "knight.h"
#include "enemy.h"
#include "fireball.h"

void Enemy::update(Knight &knight, FireBall &fireBall) {
    fireBall.update(knight);
    if (isDead) {
        return;
    }
    switch (currentState) {
        case Teleport:
            if (enemyHealth <= 0) {
                currentState = Dead;
            }
            teleport();
            if (isDone) {
                currentState = Idle;
                animationClock.restart();
            }
            break;
        case Idle:
            if (enemyHealth <= 0) {
                currentState = Dead;
            }
            idle();
            if (isDone) {
                currentState = Attack;
                animationClock.restart();
            }
            break;
        case Attack:
            if (enemyHealth <= 0) {
                currentState = Dead;
            }
            attack(knight, fireBall);
            if (isDone) {
                currentState = Disappear;
                animationClock.restart();
            }
            break;
        case Disappear:
            if (enemyHealth <= 0) {
                currentState = Dead;
            }
            disappear();
            if (isDone) {
                currentState = Teleport;
                animationClock.restart();
            }
            break;
        case Dead:
            dead();
            if (isDone) {
                isDead = true;
            }
    }
}


void Enemy::draw(sf::RenderWindow& window, FireBall &fireBall) {
    fireBall.draw(window);
    switch (currentState) {
        case Teleport:
            window.draw(teleportSprite);
            break;
        case Attack:
            window.draw(attackSprite);
            break;
        case Disappear:
            window.draw(disappearSprite);
            break;
        case Idle:
            window.draw(idleSprite);
            break;
        case Dead:
            window.draw(deathSprite);
            break;
    }
}

void Enemy::teleport() {
    teleportSprite.setPosition(enemyPosition);
    isDone = false;
    if (animationClock.getElapsedTime().asSeconds() > animationSpeed) {
        if (currentFrame < 8) {
            currentFrame++;
        } else {
            currentFrame = 0;
            isDone = true;
        }
        teleportSprite.setTextureRect(sf::IntRect(currentFrame * (2361.f/9), 0,
                                                  (2361.f/9), 426));
        animationClock.restart();
    }
}

void Enemy::idle() {
    idleSprite.setPosition(enemyPosition);
    isDone = false;
    if (animationClock.getElapsedTime().asSeconds() > animationSpeed) {
        if (currentFrame < 5) {
            currentFrame++;
        } else {
            currentFrame = 0;
            isDone = true;
        }
        idleSprite.setTextureRect(sf::IntRect(currentFrame * 159, 0,
                                              159, 410));
        animationClock.restart();
    }
}

void Enemy::attack(Knight &knight, FireBall &fireBall) {
    attackSprite.setPosition(enemyPosition);
    isDone = false;

    if (animationClock.getElapsedTime().asSeconds() > animationSpeed) {
        if (currentFrame < 7) {
            if (currentFrame == 6) {
                fireBall.setPositions(enemyPosition, 4.5);
                attackMusic.play();
                sf::Vector2f knightPosition = knight.getPosition();
                float distance = std::sqrt(std::pow(enemyPosition.x - knightPosition.x, 2)
                                           + std::pow((enemyPosition.y + 200) - knightPosition.y, 2));

                if (distance <= 300) {
                    sf::FloatRect knightBounds = knight.getGlobalBounds();
                    sf::FloatRect attackBounds = attackSprite.getGlobalBounds();
                    sf::FloatRect intersection;

                    if (attackBounds.intersects(knightBounds, intersection) && attackCount == 0) {
                        knight.decreaseHealth();
                        std::cout << "Knight got hit" << std::endl;
                        attackCount++;
                    }
                }
            }

            currentFrame++;
        }
        else {
            currentFrame = 0;
            isDone = true;
            attackCount = 0;
        }

        attackSprite.setTextureRect(sf::IntRect(currentFrame * 376, 0, 376, 410));
        animationClock.restart();
    }
}


void Enemy::disappear() {
    disappearSprite.setPosition(enemyPosition);
    isDone = false;
    if (animationClock.getElapsedTime().asSeconds() > animationSpeed) {
        if (currentFrame < 9) {
            currentFrame++;
        } else {
            currentFrame = 0;
            int xPos = rand() % (1920 - disappearSprite.getTextureRect().width);
            int yPos = rand() % (1080 - disappearSprite.getTextureRect().height);
            disappearSprite.setPosition(xPos, yPos);
            enemyPosition = disappearSprite.getPosition();
            idleSprite.setPosition(enemyPosition);
            teleportSprite.setPosition(enemyPosition);
            attackSprite.setPosition(enemyPosition);
            deathSprite.setPosition(enemyPosition);
            isDone = true;
        }
        disappearSprite.setTextureRect(sf::IntRect(currentFrame * 265, 0,
                                                   265, 426));
        animationClock.restart();
    }
}

void Enemy::dead() {
    if(!DMplaying) {
        deathMusic.play();
        DMplaying = true;
    }
    deathSprite.setPosition(enemyPosition);
    isDone = false;
    if (animationClock.getElapsedTime().asSeconds() > animationSpeed) {
        if (currentFrame < 9) {
            currentFrame++;
        } else {
            currentFrame = 0;
            isDone = true;
        }
        deathSprite.setTextureRect(sf::IntRect(currentFrame * 182, 0,
                                               182, 661));
        animationClock.restart();
    }
}
