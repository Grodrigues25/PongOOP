#include "Ball.h"

Ball::Ball()
{
    Ball::bounceAngle = sqrt(2) / 2;
    Ball::ballCoords = { 960, 540, bounceAngle };
}

Ball::~Ball()
{
}

void Ball::drawBall(sf::RenderWindow& window, bool colision1, bool colision2) {

    sf::RectangleShape ball(sf::Vector2f(12, 12));
    ball.setPosition(ballCoords[0], ballCoords[1]);
    ball.setFillColor(sf::Color::White);

    if (colision1) { cout << "Colision Left happened!" << endl; }
    if (colision2) { cout << "Colision Right happened!" << endl; }

    window.draw(ball);
}

bool Ball::ballBarCollision(vector<float> playersBarCoords)
{
    return playersBarCoords[0] < ballCoords[0] + 12 && playersBarCoords[0] + 20 > ballCoords[0] && playersBarCoords[1] - 100 < ballCoords[1] + 12 && playersBarCoords[1] > ballCoords[1];
}

void Ball::bounceDirectionCalculation(vector<float> playerBar)
{
    float maxBounceAngle = (5 * std::numbers::pi) / 12;

    float intersect = (playerBar[1] - 56) - ballCoords[1];
    intersect = intersect / 56;

    float bounceAngle = intersect * maxBounceAngle;

    ballCoords[2] = bounceAngle;

    cout << (ballCoords[2] * 360) / (2 * std::numbers::pi) << " degrees\n";
}

void Ball::ballMovement(sf::Time time)
{
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
