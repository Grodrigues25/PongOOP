#pragma once

#include <iostream>
#include "SFML/Graphics.hpp"
#include <numbers>
#include <random>
#include "PlayerBar.h"
#include "Ball.h"

using namespace std;

class GameWindow {
public:
    int score[2];

    // SETTINGS
    int windowWidth;
    int windowHeight;

    bool bColided1;
    bool bColided2;
    float colisionDelay;

public:
    GameWindow();
    ~GameWindow();

    void renderGame(PlayerBar player1Bar, PlayerBar player2Bar, Ball ball);

    void drawScoreAndCenterLine(sf::RenderWindow& window);

    void goalScoredCheck(Ball& ball);

    void collisionChecks(Ball& ball, PlayerBar& player1Bar, PlayerBar player2Bar);
};