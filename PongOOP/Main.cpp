#include <numbers>
#include <iostream>
#include <random>
#include "SFML/Graphics.hpp"
#include "PlayerBar.h"

using namespace std;


void drawPlayerBar(sf::RenderWindow& window, vector<float> player1Coords, vector<float> player2Coords) {

    int length = 100;

    sf::RectangleShape playerBar(sf::Vector2f(length, 20.f));
    playerBar.setFillColor(sf::Color::Blue);
    playerBar.setPosition(player1Coords[0], player1Coords[1]);
    playerBar.rotate(-90.f);

    sf::RectangleShape playerBar2(sf::Vector2f(length, 20.f));
    playerBar2.setFillColor(sf::Color::Red);
    playerBar2.setPosition(player2Coords[0], player2Coords[1]);
    playerBar2.rotate(-90.f);

    window.draw(playerBar);
    window.draw(playerBar2);

}

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

void drawBall(sf::RenderWindow& window, vector<float> ballCoords, bool colision1, bool colision2) {

    sf::RectangleShape ball(sf::Vector2f(12, 12));
    ball.setPosition(ballCoords[0], ballCoords[1]);
    ball.setFillColor(sf::Color::White);

    if (colision1) { cout << "Colision Left happened!" << endl; }
    if (colision2) { cout << "Colision Right happened!" << endl; }

    window.draw(ball);
}

void updateBarPosition(sf::RenderWindow& window, vector<float>& barCoords) {
    sf::Vector2f acceleration;
    sf::Vector2f velocity;

    // adjust this at will
    const float dAcc = 3.3f;

    // set acceleration
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) { acceleration.y -= dAcc; }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) { acceleration.y += dAcc; }

    // update velocity through acceleration
    velocity += acceleration;

    // update position through velocity
    if (barCoords[1] + velocity.y > 1080) {
        barCoords[1] = 1080;
    }
    else if (barCoords[1] + velocity.y < 100) {
        barCoords[1] = 100;
    }
    else {
        barCoords[1] += velocity.y;
    }

    // apply damping to the velocity
    velocity = 0.50f * velocity;

};

bool ballBarCollision(vector<float> ballDirections, vector<float> playersBarCoords) {

    return playersBarCoords[0] < ballDirections[0] + 12 && playersBarCoords[0] + 20 > ballDirections[0] && playersBarCoords[1] - 100 < ballDirections[1] + 12 && playersBarCoords[1] > ballDirections[1];
}

void bounceDirectionCalculation(vector<float>& ballCoords, vector<float> playerBar) {

    float maxBounceAngle = (5 * std::numbers::pi) / 12;

    float intersect = (playerBar[1] - 56) - ballCoords[1];
    intersect = intersect / 56;

    float bounceAngle = intersect * maxBounceAngle;

    ballCoords[2] = bounceAngle;

    cout << (ballCoords[2] * 360) / (2 * std::numbers::pi) << " degrees\n";
}

void ballMovement(vector<float>& ballCoords, sf::Time time) {

    float speed = 800;

    // Horizontal colision checks
    if (ballCoords[0] + speed * cos(ballCoords[2]) * time.asSeconds() >= 1900) {
        ballCoords[2] = 2000;
    }
    else if (ballCoords[0] + speed * cos(ballCoords[2]) * time.asSeconds() <= 0) {
        ballCoords[2] = -100;
    }
    else {
        ballCoords[0] += speed * cos(ballCoords[2]) * time.asSeconds();
    }

    // TOP and BOTTOM colision checks
    if (ballCoords[1] + speed * -sin(ballCoords[2]) * time.asSeconds() <= 1060 && ballCoords[1] + speed * -sin(ballCoords[2]) * time.asSeconds() >= 0) {
        ballCoords[1] += speed * -sin(ballCoords[2]) * time.asSeconds();
    }
    else {
        ballCoords[2] = -ballCoords[2];
        ballCoords[1] += speed * -sin(ballCoords[2]) * time.asSeconds();
    }
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
    float bounceAngle = sqrt(2) / 2;

    PlayerBar player1Bar;
    PlayerBar player2Bar;

    player1Bar.playerCoords = { 150, 590 };
    player2Bar.playerCoords = { 1770, 255 };

    //vector<float> player1BarCoords = { 150, 590 };
    //vector<float> player2BarCoords = { 1770, 255 };
    vector<float> ballCoords = { 960, 540, bounceAngle };
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
        if (ballCoords[2] == -100) {
            score[1] += 1;

            float random_angle = distribution(generator) * (5 * std::numbers::pi) / 12;
            random_angle >= 0 ? random_angle = std::numbers::pi - random_angle : ballCoords[2] = -std::numbers::pi - random_angle;

            ballCoords = { 960, 540, random_angle };
        }

        if (ballCoords[2] == 2000) {
            score[0] += 1;

            float random_angle = distribution(generator) * (5 * std::numbers::pi) / 12;

            ballCoords = { 960, 540, random_angle };
        }

        // Colision Checks
        bColided1 = ballBarCollision(ballCoords, player1Bar.playerCoords);
        bColided2 = ballBarCollision(ballCoords, player2Bar.playerCoords);
        if (bColided1 && colisionDelay > 1) {
            colisionDelay = 0;
            bounceDirectionCalculation(ballCoords, player1Bar.playerCoords);
        }

        if (bColided2 && colisionDelay > 1) {
            colisionDelay = 0;
            bounceDirectionCalculation(ballCoords, player2Bar.playerCoords);
            ballCoords[2] >= 0 ? ballCoords[2] = std::numbers::pi - ballCoords[2] : ballCoords[2] = -std::numbers::pi - ballCoords[2];
        }

        ballMovement(ballCoords, elapsed);

        // Rendering
        window.clear();
        window.draw(background);
        player1Bar.drawPlayerBar(window);
        player2Bar.drawPlayerBar(window);
        drawScoreAndCenterLine(window, score);
        drawBall(window, ballCoords, bColided1, bColided2);
        window.display();

    }

    return 0;

}