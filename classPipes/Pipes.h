#ifndef FLAPPYBIRD_PIPES_H
#define FLAPPYBIRD_PIPES_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "C:\Users\vadim\CLionProjects\FlappyBird\Entity\Entity.h"
#include "C:\Users\vadim\CLionProjects\FlappyBird\classBird\Bird.h"
#include "C:\Users\vadim\CLionProjects\FlappyBird\MainWindow\MainWindow.h"
#include "../Score/Score.h"

using namespace std;

sf::Texture *upperPipe;
sf::Texture *lowerPipe;

class Pipe : MainWindowEntity {
private:
    float x;
    float y;
    bool scored;
public:
    Pipe() {
        x = (float) (window->getSize().x + upperPipe->getSize().x);
        y = 100.0f + (float) ((rand() % 5 - 3) * 50);
        scored = false;
    }

    sf::FloatRect getUpperRect() {
        auto size = upperPipe->getSize();

        return {
                x, y + 340,
                (float) size.x, (float) size.y
        };
    }

    sf::FloatRect getLowerRect() {
        auto size = lowerPipe->getSize();

        return {
                x, y - 340,
                (float) size.x, (float) size.y
        };
    }

    void draw() override {
        sf::Sprite upperPipeSprite(*upperPipe);
        upperPipeSprite.setPosition(x, y + 340);
        sf::Sprite lowerPipeSprite(*lowerPipe);
        lowerPipeSprite.setPosition(x, y - 340);

        window->draw(upperPipeSprite);
        window->draw(lowerPipeSprite);
    }

    void update() override {
        if (not gameRunning or gameOvered) return;

        x -= 100 * delta;
        auto birdRect = bird->getRect();

        if (birdRect.intersects(getUpperRect()) or birdRect.intersects(getLowerRect())) {
            gameOvered = true;
        }

        if (x + upperPipe->getSize().x < birdRect.left and not scored) {
            scored = true;
            score++;
        }
    }
};

vector<Pipe *> pipes;
sf::Clock *pipesGeneratingClock;

#endif //FLAPPYBIRD_PIPES_H
