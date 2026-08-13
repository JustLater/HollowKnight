#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <cmath>
#include "knight.h"
#include "fireball.h"

void FireBall::update(Knight& knight) {

    if (firefirefire) {
        if(!isAnimation) {
            isAnimation = true;
        }
        firePosition1.x -= movementSpeed;
        firePosition1.y -= movementSpeed;
        firePosition2.x -= movementSpeed;
        firePosition3.x -= movementSpeed;
        firePosition3.y += movementSpeed;

        fireSprite1.setPosition(firePosition1);
        fireSprite2.setPosition(firePosition2);
        fireSprite3.setPosition(firePosition3);

        if (firePosition1.x < -103 || firePosition1.y < -93 ||
            firePosition2.x < -103 || firePosition3.x < -103 ||
            firePosition3.y > 1080) {
            attackCount = 0;
            firefirefire = false;
            isAnimation = false;
        }
        sf::Vector2f knightPosition = knight.getPosition();
        float distance1 = std::sqrt(std::pow(firePosition1.x - knightPosition.x, 2)
                                   + std::pow((firePosition1.y + 100) - knightPosition.y, 2));
        if (distance1 <= 200) {
            sf::FloatRect knightBounds = knight.getGlobalBounds();
            sf::FloatRect attackBounds = getGlobalBounds(firePosition1);
            sf::FloatRect intersection;
            if (attackBounds.intersects(knightBounds, intersection) && attackCount == 0) {
                knight.decreaseHealth();
                std::cout << "Knight got hit" << std::endl;
                attackCount++;
            }

        }
        float distance2 = std::sqrt(std::pow(firePosition2.x - knightPosition.x, 2)
                                    + std::pow((firePosition2.y + 100) - knightPosition.y, 2));
        if (distance2 <= 200) {
            sf::FloatRect knightBounds = knight.getGlobalBounds();
            sf::FloatRect attackBounds = getGlobalBounds(firePosition2);
            sf::FloatRect intersection;
            if (attackBounds.intersects(knightBounds, intersection) && attackCount == 0) {
                knight.decreaseHealth();
                std::cout << "Knight got hit" << std::endl;
                attackCount++;
            }

        }

        float distance3 = std::sqrt(std::pow(firePosition3.x - knightPosition.x, 2)
                                    + std::pow((firePosition3.y + 100) - knightPosition.y, 2));
        if (distance3 <= 200) {
            sf::FloatRect knightBounds = knight.getGlobalBounds();
            sf::FloatRect attackBounds = getGlobalBounds(firePosition3);
            sf::FloatRect intersection;
            if (attackBounds.intersects(knightBounds, intersection) && attackCount == 0) {
                knight.decreaseHealth();
                std::cout << "Knight got hit" << std::endl;
                attackCount++;
            }

        }

    }

     if (isAnimation) {
         if (animationClock.getElapsedTime().asSeconds() > animationSpeed) {
             if (currentFrame < 7) {
                    currentFrame++;
             } else {
                 currentFrame = 0;
             }
             fireSprite1.setTextureRect(sf::IntRect(currentFrame * 103, 0, 103, 93));
             fireSprite2.setTextureRect(sf::IntRect(currentFrame * 103, 0, 103, 93));
             fireSprite3.setTextureRect(sf::IntRect(currentFrame * 103, 0, 103, 93));
             animationClock.restart();
         }
     }
}

