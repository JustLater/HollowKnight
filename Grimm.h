#ifndef HOLLOW_GRIMM_H
#define HOLLOW_GRIMM_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <conio.h>

class Grimm {
public:
    Grimm () {
        idleTexture.loadFromFile("D://study//hollow//enemy//grimm//idle.png");
        idleSprite.setTexture(idleTexture);
        idleSprite.setTextureRect(sf::IntRect(0, 0, (2430.f/12), 413));

        saluteTexture.loadFromFile("D://study//hollow//enemy//grimm//salute.png");
        saluteSprite.setTexture(saluteTexture);
        saluteSprite.setTextureRect(sf::IntRect(0, 0, 255, 410));

        idleSprite.setPosition(enemyPosition);
        saluteSprite.setPosition(enemyPosition);

        teleportM.openFromFile("D://study//hollow//sounds//grimm1.wav");
        teleportM.setVolume(50);
        saluteM.openFromFile("D://study//hollow//sounds//grimm2.wav");
        saluteM.setVolume(50);

        animationClock.restart();
        currentFrame = 0;
    }

    void draw(sf::RenderWindow& window) {
        if (IsSaluting) {
            window.draw(saluteSprite);
        }
        else {
            window.draw(idleSprite);
        }
    }

    void update() {
        if (!isTM) {
            teleportM.play();
            isTM = true;
        }
        if (animationClock.getElapsedTime().asSeconds() > animationSpeed) {
            if (IsSaluting) {
                if (currentFrame < 16) {
                    if (currentFrame == 6) {
                        teleportM.stop();
                        saluteM.play();
                    }
                    currentFrame++;
                    saluteSprite.setTextureRect(sf::IntRect(currentFrame * 255, 0, 255, 426));
                }
                else {
                    currentFrame = 0;
                    IsSaluting = false;
                }
            }
            else {
                if (currentFrame < 11) {
                    currentFrame++;
                    idleSprite.setTextureRect(sf::IntRect(currentFrame * (2430.f/12),
                                                          0, (2430.f/12), 413));
                }
                else {
                    currentFrame = 0;
                    allIsDone = true;
                }
            }
            animationClock.restart();
        }
    }


    bool allIsDonE() const {
        return allIsDone;
    }

private:
    sf::Texture idleTexture;
    sf::Sprite idleSprite;

    sf::Texture saluteTexture;
    sf::Sprite saluteSprite;

    sf::Music teleportM;
    sf::Music saluteM;
    bool isTM = false;

    sf::Clock animationClock;
    int currentFrame;

    bool allIsDone = false;

    float animationSpeed = 0.15f;

    sf::Vector2f enemyPosition = sf::Vector2f(1300, 520);

    bool IsSaluting = true;
};


#endif //HOLLOW_GRIMM_H
