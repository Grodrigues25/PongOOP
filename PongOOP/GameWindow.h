#pragma once

#include <iostream>
#include "SFML/Graphics.hpp"
#include <numbers>
#include <random>

using namespace std;

class GameWindow{
public:
    int score[2];

    // SETTINGS
    int windowWidth;
    int windowHeight;

public:
    GameWindow();
    ~GameWindow();

    void drawScoreAndCenterLine();
};