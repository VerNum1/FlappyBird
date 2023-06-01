#ifndef FLAPPYBIRD_MAINWINDOW_H
#define FLAPPYBIRD_MAINWINDOW_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "C:\Users\vadim\CLionProjects\FlappyBird\Entity\Entity.h"
#include "C:\Users\vadim\CLionProjects\FlappyBird\classPipes\Pipes.h"
#include "../classBird/Bird.h"

using namespace std;

int score;
bool gameRunning, gameOvered;
float delta;

sf::Texture *backgroundTexture;
sf::Texture *groundTexture;
sf::Font *font;

float groundOffset;

sf::RenderWindow *window;

class MainWindow {
public :
    static void run() {
        srand((unsigned int) time(nullptr));
        pipesGeneratingClock = new sf::Clock;

        font = new sf::Font();
        font->loadFromFile("C:\\Users\\vadim\\CLionProjects\\FlappyBird\\resources\\fonts\\04B_19__.TTF");

        window = new sf::RenderWindow(sf::VideoMode(450, 700), "Flappy Bird");
        window->setPosition({1417, 120});

        bird = new Bird();

        backgroundTexture = new sf::Texture();
        backgroundTexture->loadFromFile(
                "C:\\Users\\vadim\\CLionProjects\\FlappyBird\\resources\\textures\\background\\impossible.png");

        groundTexture = new sf::Texture();
        groundTexture->loadFromFile("C:\\Users\\vadim\\CLionProjects\\FlappyBird\\resources\\textures\\ground.png");

        upperPipe = new sf::Texture();
        lowerPipe = new sf::Texture();

        sf::Image pipeImage;
        pipeImage.loadFromFile("C:\\Users\\vadim\\CLionProjects\\FlappyBird\\resources\\textures\\pipe.png");

        upperPipe->loadFromImage(pipeImage);
        pipeImage.flipVertically();
        lowerPipe->loadFromImage(pipeImage);

        pipes.push_back(new Pipe());
    }

    static void destroy() {
        delete window;
        delete bird;
        delete backgroundTexture;
        delete pipesGeneratingClock;
        delete font;
    }

    static void update() {
        bird->update();

        for (const auto &pipe: pipes) {
            pipe->update();
        }

        if (gameRunning and not gameOvered) {
            if (pipesGeneratingClock->getElapsedTime().asSeconds() > 3.5) {
                pipesGeneratingClock->restart();
                pipes.push_back(new Pipe());

                if (pipes.size() > 4) {
                    delete pipes[0];
                    pipes.erase(pipes.begin());
                }
            }
        }
    }

    static void handleEvent(sf::Event &event) {
        if (event.type == sf::Event::Closed) {
            window->close();
        }
        if (event.type == sf::Event::MouseButtonPressed) {
            if (not gameRunning) {
                gameRunning = true;
                pipesGeneratingClock->restart();
                pipes.push_back(new Pipe());
            }
            bird->flap();
        }
    }

    static void draw() {
        window->clear();
        window->draw(sf::Sprite(*backgroundTexture));

        for (const auto &pipe: pipes) {
            pipe->draw();
        }

        sf::Sprite groundSprite(*groundTexture);
        if (not(not gameRunning or gameOvered)) {
            groundOffset -= delta * 100;
            if (groundOffset <= -24) {
                groundOffset += 24;
            }
        }

        groundSprite.setPosition(groundOffset, (float) backgroundTexture->getSize().y);
        window->draw(groundSprite);

        sf::RectangleShape lowerRectangle({
                                                  (float) window->getSize().x,
                                                  (float) window->getSize().y - (float) backgroundTexture->getSize().y -
                                                  (float) groundTexture->getSize().y
                                          });
        lowerRectangle.setPosition(0, (float) backgroundTexture->getSize().y + (float) groundTexture->getSize().y);
        lowerRectangle.setFillColor({235, 100, 04});
        window->draw(lowerRectangle);

        bird->draw();

        sf::Text scoreText("Score: " + to_string(score), *font);
        scoreText.setPosition(window->getSize().x / 2 - scoreText.getLocalBounds().width / 2, 5);
        window->draw(scoreText);
    }

};

#endif //FLAPPYBIRD_MAINWINDOW_H
