#include <SFML/Graphics.hpp>
#include <conio.h>
#include <iostream>
#include <SFML/Audio.hpp>
#include "knight.h"
#include "enemy.h"
#include "largerEnemy.h"
#include "theLargestEnemy.h"
#include "Grimm.h"
#include "fireball.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Hollow");
    sf::Texture menuTexture;
    sf::Sprite menuSprite;
    menuTexture.loadFromFile("D://study//hollow//sprites//menunew.png");
    menuSprite.setTexture(menuTexture);

    sf::Texture beginningTexture;
    sf::Sprite beginningSprite;
    beginningTexture.loadFromFile("D://study//hollow//sprites//impress.png");
    beginningSprite.setTexture(beginningTexture);

    Knight knight;
    Enemy enemy;
    LargerEnemy largerEnemy;
    TheLargestEnemy theLargestEnemy;
    Grimm grimm;
    FireBall fireBall;

    sf::Clock clock;

    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

    sf::Texture lostTexture;
    sf::Sprite lostSprite;
    sf::Texture winTexture;
    sf::Sprite winSprite;

    sf::Font font;
    sf::Text playText;
    sf::Text exitText;
    sf::Text continueText;

    backgroundTexture.loadFromFile("D://study//hollow//sprites//map.png");
    backgroundSprite.setTexture(backgroundTexture);

    lostTexture.loadFromFile("D://study//hollow//sprites//deathmap.png");
    lostSprite.setTexture(lostTexture);
    winTexture.loadFromFile("D://study//hollow//sprites//winmap.png");
    winSprite.setTexture(winTexture);

    font.loadFromFile("D://study//hollow//other//font.ttf");
    playText.setFont(font);
    playText.setString("Play");
    playText.setCharacterSize(60);
    playText.setPosition(1700, 100);

    exitText.setFont(font);
    exitText.setString("Exit");
    exitText.setCharacterSize(60);
    exitText.setPosition(1700, 200);

    continueText.setFont(font);
    continueText.setString("Continue");
    continueText.setCharacterSize(60);
    continueText.setPosition(1700, 300);

    bool isExitClicked = false;
    bool isPlayClicked = false;
    bool isContinueClicked = false;

    //музыка
    sf::Music enemyMusic;
    sf::Music largerEnemyMusic;
    sf::Music theLargestEnemyMusic;
    sf::Music lostSpriteMusic;
    sf::Music menuMusic;

    enemyMusic.openFromFile("D://study//hollow//sounds//E_sound.wav");
    largerEnemyMusic.openFromFile("D://study//hollow//sounds//LE_sound.wav");
    theLargestEnemyMusic.openFromFile("D://study//hollow//sounds//tLE_sound.wav");
    lostSpriteMusic.openFromFile("D://study//hollow//sounds//hero//deathmap.wav");
    menuMusic.openFromFile("D://study//hollow//sounds//hero//menu.wav");

    enemyMusic.setVolume(30);
    largerEnemyMusic.setVolume(30);
    theLargestEnemyMusic.setVolume(20);
    lostSpriteMusic.setVolume(30);
    menuMusic.setVolume(30);

    bool isEnemyMusicPlaying = false;
    bool isLargerEnemyMusicPlaying = false;
    bool isTheLargestEnemyMusicPlaying = false;
    bool isMenuMusicPlaying = false;
    bool isLostMusicPlaying = false;

    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

                    if (!isPlayClicked && menuSprite.getGlobalBounds().contains(mousePos)) {
                        isPlayClicked = true;
                    }

                    if (isPlayClicked && exitText.getGlobalBounds().contains(mousePos)) {
                        isExitClicked = true;
                    }

                    if (isPlayClicked && continueText.getGlobalBounds().contains(mousePos)) {
                        isContinueClicked = true;
                    }

                }
            }
        }

        // Обработка геймплея
        bool isLeftPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
        bool isRightPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
        bool isJumpPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Z);
        bool isAttackPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::X);

        if (isContinueClicked) {
            menuMusic.stop();
            if (knight.isAlive()) {
                knight.update(isLeftPressed, isRightPressed, isJumpPressed, isAttackPressed, enemy, largerEnemy, theLargestEnemy);
                if (enemy.isAlive()) {
                    enemy.update(knight, fireBall);
                    if (!isEnemyMusicPlaying) {
                        enemyMusic.play();
                        enemyMusic.setLoop(true);
                        isEnemyMusicPlaying = true;
                    }
                } else if (!enemy.isAlive()) {
                    largerEnemy.update(knight, fireBall);
                    if (!isLargerEnemyMusicPlaying) {
                        enemyMusic.stop();
                        largerEnemyMusic.play();
                        largerEnemyMusic.setLoop(true);
                        isLargerEnemyMusicPlaying = true;
                    }
                }
                if (!largerEnemy.isAlive()) {
                    theLargestEnemy.update(knight, fireBall);
                    if (!isTheLargestEnemyMusicPlaying) {
                        largerEnemyMusic.stop();
                        theLargestEnemyMusic.play();
                        theLargestEnemyMusic.setLoop(true);
                        isTheLargestEnemyMusicPlaying = true;
                    }
                }
                if (!theLargestEnemy.isAlive()) {
                    grimm.update();
                    if (isTheLargestEnemyMusicPlaying) {
                        theLargestEnemyMusic.stop();
                        isTheLargestEnemyMusicPlaying = false;
                    }
                }
            }

            window.clear();
            window.draw(backgroundSprite);

            if (enemy.isAlive()) {
                enemy.draw(window, fireBall);
            } else if (largerEnemy.isAlive()) {
                largerEnemy.draw(window, fireBall);
            } else if (theLargestEnemy.isAlive()) {
                theLargestEnemy.draw(window, fireBall);
            }

            if (knight.isAlive()) {
                knight.draw(window);
                if (!theLargestEnemy.isAlive()) {
                    grimm.draw(window);
                    if (grimm.allIsDonE()) {
                        window.draw(winSprite);
                        window.draw(exitText);

                        if (isExitClicked) {
                            window.close();
                        }
                    }
                }
            }

            if (!knight.isAlive()) {
                enemyMusic.stop();
                largerEnemyMusic.stop();
                theLargestEnemyMusic.stop();

                // Сброс флагов состояния музыки
                isEnemyMusicPlaying = false;
                isLargerEnemyMusicPlaying = false;
                isTheLargestEnemyMusicPlaying = false;
                if (!isLostMusicPlaying) {
                    lostSpriteMusic.play();
                    isLostMusicPlaying = true;
                }
                window.draw(lostSprite);
                window.draw(exitText);

                if (isExitClicked) {
                    window.close();
                }
            }

            window.display();
        }
        else {
            window.clear();
            if (!isMenuMusicPlaying) {
                menuMusic.play();
                menuMusic.setLoop(true);
                isMenuMusicPlaying = true;
            }
            window.draw(menuSprite);
            window.draw(playText);
            window.draw(exitText);
            if (isPlayClicked) {
                window.draw(beginningSprite);
                window.draw(continueText);
            }
            window.display();
        }
    }
    return 0;
}