#ifndef FLAPPYBIRD_BOOST_H
#define FLAPPYBIRD_BOOST_H

#include "../Score/Score.h"
#include "../classBird/Bird.h"
#include "../MainWindow/MainWindow.h"

sf::Clock *boostTime;
static int timeToBoost = 4;
int countBoost = 0;

class Boost {
public:
    static float update() {
        if (score % timeToBoost == 0 && countBoost % 10 == 0) {
            int tmp = speed;
            return tmp - (-50 + rand() % (50 + 50 + 1));
        } else if (countBoost % 4 == 0)
            return speed;
    }

    static void draw() {
        sf::Text boostText("???DANGER???", *font);
        boostText.setCharacterSize(24);
        boostText.setFillColor(sf::Color::Yellow);
        boostText.setPosition(window->getSize().x / 2 - boostText.getLocalBounds().width / 2, 60);

        if (score % timeToBoost == 0)
            window->draw(boostText);
    }
};

#endif //FLAPPYBIRD_BOOST_H
