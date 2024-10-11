#include "GameWindow.h"

GameWindow::GameWindow()
{
    GameWindow::score[0] = 0;
    GameWindow::score[1] = 0;

    // SETTINGS
    GameWindow::windowWidth = 1920;
    GameWindow::windowHeight = 1080;

    // VARIABLES
    GameWindow::bColided1 = false;
    GameWindow::bColided2 = false;
    GameWindow::colisionDelay = 0;

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

void GameWindow::goalScoredCheck(Ball& ball) {

    std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution(-1, 1);

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
}

void GameWindow::collisionChecks(Ball& ball, PlayerBar& player1Bar, PlayerBar player2Bar)
{
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
}

void GameWindow::renderGame(PlayerBar player1Bar, PlayerBar player2Bar, Ball ball) 
{
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "TicTacToe");
    sf::Event event;
    sf::Clock clock;
    sf::RectangleShape background(sf::Vector2f(windowWidth, windowHeight));
    background.setFillColor(sf::Color::Black);
    window.setVerticalSyncEnabled(true);

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

        goalScoredCheck(ball);

        collisionChecks(ball, player1Bar, player2Bar);

        ball.ballMovement(elapsed);

        // Rendering
        window.clear();
        window.draw(background);

        player1Bar.drawPlayerBar(window);
        player2Bar.drawPlayerBar(window);

        drawScoreAndCenterLine(window);

        ball.drawBall(window, bColided1, bColided2);

        window.display();
    }

}


