#include "GameWindow.h"

GameWindow::GameWindow()
{
    GameWindow::score[0] = 0;
    GameWindow::score[1] = 0;

    // SETTINGS
    GameWindow::windowWidth = 1920;
    GameWindow::windowHeight = 1080;

    ////RENDER WINDOW
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "TicTacToe");
    //sf::RectangleShape background(sf::Vector2f(windowWidth, windowHeight));
    //background.setFillColor(sf::Color::Black);
    //window.setVerticalSyncEnabled(true);

    //sf::Event event;
    //std::default_random_engine generator;
    //std::uniform_real_distribution<double> distribution(-1, 1);

    //sf::Clock clock;
}

GameWindow::~GameWindow()
{
}

void GameWindow::drawScoreAndCenterLine(sf::RenderWindow& window) {

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