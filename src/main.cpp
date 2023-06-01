#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "C:\Users\vadim\CLionProjects\FlappyBird\classBird\Bird.h"
#include "C:\Users\vadim\CLionProjects\FlappyBird\Entity\Entity.h"
#include "C:\Users\vadim\CLionProjects\FlappyBird\MainWindow\MainWindow.h"

using namespace std;

int main() {

    MainWindow::run();

    sf::Clock deltaClock;

    while (window->isOpen()) {
        sf::Event event{};

        while (window->pollEvent(event)) {
            MainWindow::handleEvent(event);
        }
        delta = deltaClock.getElapsedTime().asMicroseconds() / 1000.0f / 1000.0f;
        deltaClock.restart();

        MainWindow::update();
        MainWindow::draw();

        window->display();
    }

    MainWindow::destroy();

    return EXIT_SUCCESS;
}