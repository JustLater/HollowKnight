#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include "knight.h"
#include "theLargestEnemy.h"
#include "fireball.h"


void TheLargestEnemy::update(Knight &knight, FireBall &fireBall) {
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


void TheLargestEnemy::draw(sf::RenderWindow& window, FireBall &fireBall) {
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

void TheLargestEnemy::teleport() {
    teleportSprite.setPosition(enemyPosition);
    isDone = false;
    if (animationClock.getElapsedTime().asSeconds() > animationSpeed) {
        if (currentFrame < 8) {
            currentFrame++;
        } else {
            currentFrame = 0;
            isDone = true;
        }
        teleportSprite.setTextureRect(sf::IntRect(currentFrame * 265, 0,
                                                  265, 511));
        animationClock.restart();
    }
}

void TheLargestEnemy::idle() {
    idleSprite.setPosition(enemyPosition);
    isDone = false;
    if (animationClock.getElapsedTime().asSeconds() > animationSpeed) {
        if (currentFrame < 9) {
            currentFrame++;
        } else {
            currentFrame = 0;
            isDone = true;
        }
        idleSprite.setTextureRect(sf::IntRect(currentFrame * (2115.f/10), 0,
                                              (2115.f/10), 457));
        animationClock.restart();
    }
}

void TheLargestEnemy::attack(Knight &knight, FireBall &fireBall) {
    attackSprite.setPosition(enemyPosition);
    isDone = false;
    if (animationClock.getElapsedTime().asSeconds() > animationSpeed) {
        if (currentFrame < 7) {
            if (currentFrame == 6) {
                fireBall.setPositions(enemyPosition, 6.0);
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
                        knight.decreaseHealth();
                        std::cout << "Knight got hit" << std::endl;
                        attackCount++;
                    }
                }
            }
            currentFrame++;
        } else {
            currentFrame = 0;
            isDone = true;
            attackCount = 0;
        }
        attackSprite.setTextureRect(sf::IntRect(currentFrame * 355, 0,
                                                355, 460));
        animationClock.restart();
    }
}

void TheLargestEnemy::disappear() {
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
                                                   265, 511));
        animationClock.restart();
    }
}

void TheLargestEnemy::dead() {
    if(!DMplaying) {
        deathMusic.play();
        DMplaying = true;
    }
    deathSprite.setPosition(enemyPosition);
    isDone = false;
    if (animationClock.getElapsedTime().asSeconds() > animationSpeed) {
        if (currentFrame < 8) {
            currentFrame++;
        } else {
            currentFrame = 0;
            isDone = true;
        }
        deathSprite.setTextureRect(sf::IntRect(currentFrame * (2300.f/9), 0,
                                               (2300.f/9), 917));
        animationClock.restart();
    }
}