#include "PlayerBar.h"

PlayerBar::PlayerBar() {
    PlayerBar::length = 100;
}

PlayerBar::~PlayerBar() {

}

void PlayerBar::drawPlayerBar(sf::RenderWindow& window) {

    sf::RectangleShape playerBar(sf::Vector2f(length, 20.f));
    playerBar.setFillColor(sf::Color::White);
    playerBar.setPosition(playerCoords[0], playerCoords[1]);
    playerBar.rotate(-90.f);

    window.draw(playerBar);
}

void PlayerBar::updateBarPosition(sf::RenderWindow& window) {
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
    if (playerCoords[1] + velocity.y > 1080) {
        playerCoords[1] = 1080;
    }
    else if (playerCoords[1] + velocity.y < 100) {
        playerCoords[1] = 100;
    }
    else {
        playerCoords[1] += velocity.y;
    }

    // apply damping to the velocity
    velocity = 0.99f * velocity;

};