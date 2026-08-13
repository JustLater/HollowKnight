#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <conio.h>
#include "knight.h"
#include "enemy.h"
#include "largerEnemy.h"
#include "theLargestEnemy.h"


void Knight::update(bool isLeftPressed, bool isRightPressed, bool isJumpPressed, bool isAttackPressed,
                    Enemy &enemy, LargerEnemy &largerEnemy, TheLargestEnemy &theLargestEnemy) {

    if (isDead && !isNowReallyDead) {
        if (!isDeathAnimating) {
            isDeathAnimating = true;
            animationClock.restart();
        }
        if (animationClock.getElapsedTime().asSeconds() > animationSpeed) {
            deathCurrentFrame++;
            if (deathCurrentFrame >= 9) {
                deathCurrentFrame = 0;
                isNowReallyDead = true;
                std::cout << "Knight is dead" << std::endl;
                isDeathAnimating = false;
            }
            deathSprite.setTextureRect(sf::IntRect(deathCurrentFrame * 128, 0, 128,
                                                   deathTexture.getSize().y));
            animationClock.restart();
        }
    }

    if (isLeftPressed) {
        characterSprite.move(-movementSpeed, 0);
    } else if (isRightPressed) {
        characterSprite.move(movementSpeed, 0);
    }

    characterPosition = characterSprite.getPosition();
    jumpSprite.setPosition(characterPosition);
    attackSprite.setPosition(characterPosition);

    if (isJumpPressed && !isJumping && !hasJumped && !hasJumpKeyPressed) {
        jumpMusic.play();
        isJumping = true;
        isJumpingAnimation = true;
        verticalVelocity = -jumpSpeed;
        jumpCurrentFrame = 0;
        jumpSprite.setTextureRect(sf::IntRect(jumpCurrentFrame * 135,
                                              0, 135, jumpTexture.getSize().y));
        hasJumped = true;
        hasJumpKeyPressed = true;

        if (isAttacking) {
            isAttacking = false;
            isAttackingAnimation = false;
            hasAttacked = false;
        }
    }

    if (isAttackPressed && !isAttacking && !hasAttacked && !hasAttackKeyPressed) {
        attackMusic.play();
        isAttacking = true;
        isAttackingAnimation = true;
        attackCurrentFrame = 0;
        attackSprite.setTextureRect(sf::IntRect(attackCurrentFrame * 260,
                                                0, 260, attackTexture.getSize().y));
        hasAttacked = true;
        hasAttackKeyPressed = true;
        sf::FloatRect enemyBounds;
        if (enemy.isAlive()) {
            enemyBounds = enemy.getGlobalBounds();
        }
        else if (!enemy.isAlive() && largerEnemy.isAlive()) {
            enemyBounds = largerEnemy.getGlobalBounds();
        }
        else {
            enemyBounds = theLargestEnemy.getGlobalBounds();
        }
        sf::FloatRect attackBounds = attackSprite.getGlobalBounds();
        sf::FloatRect intersection;
        if (attackBounds.intersects(enemyBounds, intersection)) {
            if (enemy.isAlive()) {
                enemy.getHit();
            }
            else if (!enemy.isAlive() && largerEnemy.isAlive()) {
                largerEnemy.getHit();
            }
            else {
                theLargestEnemy.getHit();
            }
            std::cout << "Enemy got hit" << std::endl; // для отладки
        }
        if (isJumping) {
            isJumping = false;
            isJumpingAnimation = true;
            jumpCurrentFrame = 6; // Устанавливаем последние три кадра анимации прыжка
            jumpSprite.setTextureRect(sf::IntRect(jumpCurrentFrame * 135,
                                                  0, 135, jumpTexture.getSize().y));
            verticalVelocity = 0.0f;

            // Персонаж приземляется на землю после атаки в воздухе
            if (characterSprite.getPosition().y != 800) {
                characterSprite.setPosition(characterSprite.getPosition().x, 800); // Приземление на землю
                hasJumped = false;
            }
        }
    }

    if (isJumping && isJumpingAnimation) {
        if (animationClock.getElapsedTime().asSeconds() > animationSpeed) {
            jumpCurrentFrame++;
            if (jumpCurrentFrame >= 9) {
                jumpCurrentFrame = 0;
                isJumpingAnimation = false;
            }
            jumpSprite.setTextureRect(sf::IntRect(jumpCurrentFrame * 135, 0,
                                                  135, jumpTexture.getSize().y));
            animationClock.restart();
        }
    }

    //ограничение персонажа по передвижению (чтоб за пределы окна не убегал)

    if (characterPosition.x < minX) {
        characterPosition.x = minX;
    } else if (characterPosition.x > maxX) {
        characterPosition.x = maxX;
    }

    if (characterPosition.y < minY) {
        characterPosition.y = minY;
    } else if (characterPosition.y > maxY) {
        characterPosition.y = maxY;
    }
    characterSprite.setPosition(characterPosition);
    if (characterSprite.getPosition().x < 772 || characterSprite.getPosition().x > 1147) {
        jumpCurrentFrame = 6;
        if (animationClock.getElapsedTime().asSeconds() > animationSpeed) {
            jumpCurrentFrame++;
            if (jumpCurrentFrame >= 9) {
                jumpCurrentFrame = 0;
                isJumpingAnimation = false;
            }
            jumpSprite.setTextureRect(sf::IntRect(jumpCurrentFrame * 135,
                                                  0, 135, jumpTexture.getSize().y));
            animationClock.restart();
        }
        characterSprite.move(0.0f, verticalVelocity);
        verticalVelocity += gravity;
        if (characterSprite.getPosition().y >= 800) {
            characterSprite.setPosition(characterSprite.getPosition().x, 800);
            verticalVelocity = 0.0f;
        }
    }

    if ((isJumping || isAttacking) && !isAttackingAnimation) {
        if (isLeftPressed) {
            characterSprite.move(-movementSpeed * 0.5, 0);
        } else if (isRightPressed) {
            characterSprite.move(movementSpeed * 0.5, 0);
        }
    }

    if ((isJumping || isAttacking) && characterSprite.getPosition().y != 800) {
        jumpCurrentFrame = 6;
        if (animationClock.getElapsedTime().asSeconds() > animationSpeed) {
            jumpCurrentFrame++;
            if (jumpCurrentFrame >= 9) {
                jumpCurrentFrame = 0;
                isJumpingAnimation = false;
            }
            jumpSprite.setTextureRect(sf::IntRect(jumpCurrentFrame * 135,
                                                  0, 135, jumpTexture.getSize().y));
            animationClock.restart();
        }
        characterSprite.move(0.0f, verticalVelocity);
        verticalVelocity += gravity;
        if (characterSprite.getPosition().y >= 800) {
            characterSprite.setPosition(characterSprite.getPosition().x, 800);
            hasJumped = false;
            isJumpingAnimation = false;
            isJumping = false;
            verticalVelocity = 0.0f;
        }
    }

    if (isJumping) {
        if (isLeftPressed) {
            characterSprite.move(-movementSpeed * 2, 0);
        } else if (isRightPressed) {
            characterSprite.move(movementSpeed * 2, 0);
        }

        characterSprite.move(0.0f, verticalVelocity);
        verticalVelocity += gravity;

        if (characterSprite.getPosition().y >= 800) {
            characterSprite.setPosition(characterSprite.getPosition().x, 800);
            isJumping = false;
            isJumpingAnimation = false;
            verticalVelocity = 0.0f;
            hasJumped = false;
        }

    }

    if (isAttacking && isAttackingAnimation) {
        if (animationClock.getElapsedTime().asSeconds() > attackanimationSpeed) {
            attackCurrentFrame++;
            if (attackCurrentFrame >= 8) {
                attackCurrentFrame = 0;
                isAttackingAnimation = false;
                isAttacking = false;
                hasAttacked = false;
            }
            attackSprite.setTextureRect(sf::IntRect(attackCurrentFrame * 260,
                                                    0, 260, attackTexture.getSize().y));
            animationClock.restart();
        }
    }

    if (!isJumping && !isAttacking) {
        if (animationClock.getElapsedTime().asSeconds() > animationSpeed) {
            if (currentFrame < 9) {
                currentFrame++;
            } else {
                currentFrame = 0;
            }
            characterSprite.setTextureRect(sf::IntRect(currentFrame * 100, 0, 100, 140));
            animationClock.restart();
        }
    }

    if (!isJumpPressed) {
        hasJumpKeyPressed = false;
    }

    if (!isAttackPressed) {
        hasAttackKeyPressed = false;
    }
}

void Knight::draw(sf::RenderWindow& window) {
    for (int i = 0; i < maxMask; i++) {
        window.draw(maskSprites[i]);
    }
    if (isDead) {
        window.draw(deathSprite);
    }
    else if (isJumping) {
        window.draw(jumpSprite);
    }
    else if (isAttacking) {
        window.draw(attackSprite);
    }
    else {
        window.draw(characterSprite);
    }
}