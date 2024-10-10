#pragma once

#include <iostream>
#include "SFML/Graphics.hpp"
#include <numbers>

using namespace std;

class Ball {
public:
    vector<float> ballCoords;
    float bounceAngle;

public:
    Ball();
    ~Ball();

    void drawBall(sf::RenderWindow& window, bool colision1, bool colision2);

    bool ballBarCollision(vector<float> playersBarCoords);

    void bounceDirectionCalculation(vector<float> playerBar);

    void ballMovement(sf::Time time);
};