#include "PlayerBar.h"
#include "Ball.h"
#include "GameWindow.h"

using namespace std;

int main() {

    PlayerBar player1Bar;
    PlayerBar player2Bar;

    player1Bar.playerCoords = { 150, 590 };
    player2Bar.playerCoords = { 1770, 590 };

    Ball ball;

    GameWindow GameSession;

    GameSession.renderGame(player1Bar, player2Bar, ball);
    
    return 0;
}