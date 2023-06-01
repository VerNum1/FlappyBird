#ifndef FLAPPYBIRD_ENTITY_H
#define FLAPPYBIRD_ENTITY_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

using namespace std;

class MainWindowEntity {
public:
    virtual void draw() {};

    virtual void update() {};
};

#endif //FLAPPYBIRD_ENTITY_H
