#include <numbers>
#include <iostream>
#include <random>
#include "SFML/Graphics.hpp"
#include "PlayerBar.h"
#include "Ball.h"
#include "GameWindow.h"

using namespace std;


void drawScoreAndCenterLine(sf::RenderWindow& window, int score[2]) {

    sf::Font font;
    font.loadFromFile("C:\\Users\\gonca\\source\\repos\\Pong\\assets\\PressStart2P-vaV7.ttf");

    sf::Text player1Score;
    sf::Text player2Score;

    player1Score.setFont(font);
    player1Score.setString(std::to_string(score[0]));
    player1Score.setCharacterSize(60); // in pixels, not points!
    player1Score.setFillColor(sf::Color::White);
    player1Score.setStyle(sf::Text::Bold);
    player1Score.setPosition(860, 100);

    player2Score.setFont(font);
    player2Score.setString(std::to_string(score[1]));
    player2Score.setCharacterSize(60); // in pixels, not points!
    player2Score.setFillColor(sf::Color::White);
    player2Score.setStyle(sf::Text::Bold);
    player2Score.setPosition(995, 100);

    sf::RectangleShape middleLine(sf::Vector2f(30, 7.f));

    sf::Color middleBarCollor(255, 255, 255, 120);
    middleLine.setFillColor(middleBarCollor);

    middleLine.rotate(90.f);

    int middleLineY = 0;
    while (middleLineY < 1080) {
        middleLine.setPosition(960, middleLineY);
        window.draw(middleLine);

        middleLineY += 50;
    }

    window.draw(player1Score);
    window.draw(player2Score);

}

int main() {

    // SETTINGS
    int windowWidth = 1920;
    int windowHeight = 1080;

    //RENDER WINDOW
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "TicTacToe", sf::Style::Close);
    sf::RectangleShape background(sf::Vector2f(windowWidth, windowHeight));
    background.setFillColor(sf::Color::Black);
    window.setVerticalSyncEnabled(true);

    //GAME DATA STRUCTURES
    int score[2] = { 0,0 };
    sf::Clock clock;
    bool bColided1;
    bool bColided2;
    float colisionDelay = 0;

    PlayerBar player1Bar;
    PlayerBar player2Bar;

    player1Bar.playerCoords = { 150, 590 };
    player2Bar.playerCoords = { 1770, 255 };

    Ball ball;

    GameWindow GameSession;

    sf::Event event;
    std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution(-1, 1);

    //WHILE WINDOW IS OPEN LOGIC AKA WHILE THE GAME IS RUNNING
    while (window.isOpen()) {

        //while (window.pollEvent(event)) {
        window.pollEvent(event);

        switch (event.type) {
        case sf::Event::Closed:
            window.close();
            break;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) { player1Bar.updateBarPosition(window); }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) { player2Bar.updateBarPosition(window); };

        colisionDelay += clock.getElapsedTime().asSeconds();
        sf::Time elapsed = clock.restart();

        // Goal Scored Checks
        if (ball.ballCoords[2] == -100) {
            score[1] += 1;

            float random_angle = distribution(generator) * (5 * std::numbers::pi) / 12;
            random_angle >= 0 ? random_angle = std::numbers::pi - random_angle : ball.ballCoords[2] = -std::numbers::pi - random_angle;

            ball.ballCoords = { 960, 540, random_angle };
        }

        if (ball.ballCoords[2] == 2000) {
            score[0] += 1;

            float random_angle = distribution(generator) * (5 * std::numbers::pi) / 12;

            ball.ballCoords = { 960, 540, random_angle };
        }

        // Colision Checks
        bColided1 = ball.ballBarCollision(player1Bar.playerCoords);
        bColided2 = ball.ballBarCollision(player2Bar.playerCoords);
        if (bColided1 && colisionDelay > 1) {
            colisionDelay = 0;
            ball.bounceDirectionCalculation(player1Bar.playerCoords);
        }

        if (bColided2 && colisionDelay > 1) {
            colisionDelay = 0;
            ball.bounceDirectionCalculation(player2Bar.playerCoords);
            ball.ballCoords[2] >= 0 ? ball.ballCoords[2] = std::numbers::pi - ball.ballCoords[2] : ball.ballCoords[2] = -std::numbers::pi - ball.ballCoords[2];
        }

        ball.ballMovement(elapsed);

        // Rendering
        window.clear();
        window.draw(background);

        player1Bar.drawPlayerBar(window);
        player2Bar.drawPlayerBar(window);
        
        drawScoreAndCenterLine(window, score);
        
        ball.drawBall(window, bColided1, bColided2);
        
        window.display();

    }

    return 0;

}