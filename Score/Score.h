#ifndef FLAPPYBIRD_SCORE_H
#define FLAPPYBIRD_SCORE_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "../MainWindow/MainWindow.h"

int score = 0;

class Score {
public:
    static void draw(){
        sf::Text scoreText("Score: " + to_string(score), *font);
        scoreText.setPosition(window->getSize().x / 2 - scoreText.getLocalBounds().width / 2, 5);
        window->draw(scoreText);
    }
};

#endif //FLAPPYBIRD_SCORE_H
