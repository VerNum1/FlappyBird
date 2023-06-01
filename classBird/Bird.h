#ifndef FLAPPYBIRD_BIRD_H
#define FLAPPYBIRD_BIRD_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "C:\Users\vadim\CLionProjects\FlappyBird\Entity\Entity.h"
#include "C:\Users\vadim\CLionProjects\FlappyBird\MainWindow\MainWindow.h"

using namespace std;

class Bird : public MainWindowEntity {
private:
    static Bird *bird;
    sf::Texture *texture;
    float y;
    float vel;
    float currentFrames{};
    sf::Clock *animationClock;
    vector<sf::Texture *> frames;

public:
    Bird() {
        animationClock = new sf::Clock;

        for (const auto &path: {
                "C:\\Users\\vadim\\CLionProjects\\FlappyBird\\resources\\textures\\bird\\2-2.png",
                "C:\\Users\\vadim\\CLionProjects\\FlappyBird\\resources\\textures\\bird\\2-3.png",
                "C:\\Users\\vadim\\CLionProjects\\FlappyBird\\resources\\textures\\bird\\2-2.png",
                "C:\\Users\\vadim\\CLionProjects\\FlappyBird\\resources\\textures\\bird\\2-1.png"
        }) {
            auto frame = new sf::Texture();
            frame->loadFromFile(path);
            frames.push_back(frame);
        }
        texture = frames[0];

        y = 400;
        vel = 0;
    }

    static Bird *getInstance() {
        if (!bird)
            bird = new Bird();

        return bird;
    }


    ~Bird() {
        for (const auto &ptr: frames) {
            delete ptr;
        }
        delete animationClock;
    }

    sf::FloatRect getRect() {
        auto size = texture->getSize();

        return {
                50, y,
                (float) size.x, (float) size.y
        };
    }

    void flap() {
        if (not gameRunning or gameOvered) return;
        vel = -420;
    }

    void draw() override {
        sf::Sprite birdSprite(*texture);
        birdSprite.setRotation(8 * (vel / 400));
        birdSprite.setPosition(50, y);

        window->draw(birdSprite);
    }

    void update() override {
        currentFrames += delta * 4;
        if (currentFrames > frames.size()) {
            currentFrames -= frames.size();
        }

        texture = frames[(int) currentFrames];

        if (gameRunning) {
            vel += delta * 1200;
            y += delta * vel;

            if (y < 0 or y + texture->getSize().y > backgroundTexture->getSize().y) {
                gameOvered = true;
            }

            if (y + texture->getSize().y > backgroundTexture->getSize().y) {
                y = (float) backgroundTexture->getSize().y + texture->getSize().y;
                vel = 0;
            }
        }
    }
};

Bird *bird = 0;

#endif //FLAPPYBIRD_BIRD_H
