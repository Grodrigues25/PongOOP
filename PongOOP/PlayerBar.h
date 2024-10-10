#pragma once

#include <iostream>
#include "SFML/Graphics.hpp"

using namespace std;

class PlayerBar {
public:
    int length;
    vector<float> playerCoords;

public:
    PlayerBar();
    ~PlayerBar();

    void drawPlayerBar(sf::RenderWindow& window);

    void updateBarPosition(sf::RenderWindow& window);

};