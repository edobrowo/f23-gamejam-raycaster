#include <GLFW/glfw3.h>

#include <cmath>
#include <iostream>
#include "game.h"
#include "util.h"

#include "player.h"

Player::Player(float initialX, float initialY, float speed) :
posX{initialX},
posY{initialY},
angle{PI / 2},
speed{speed},
rotationSpeed{0.05f}
{
    posDiffX = cos(angle) * speed;
    posDiffY = sin(angle) * speed;
}

Player::Player() :
posX{WINDOW_WIDTH_DEFAULT / 2},
posY{WINDOW_HEIGHT_DEFAULT / 2},
angle{3*PI / 2},
speed{5.f},
rotationSpeed{0.05f}
{
    posDiffX = cos(angle) * speed;
    posDiffY = sin(angle) * speed;
}

void Player::InputOperations() {
    Game* gs = Game::GetInstance();
    int* keyStates = gs->keys;

    if (keyStates[GLFW_KEY_W]) {
        posX += posDiffX;
        posY += posDiffY;
    }
    if (keyStates[GLFW_KEY_A]) {
        angle = util::wrap2pi(angle - rotationSpeed);
        posDiffX = cos(angle) * speed;
        posDiffY = sin(angle) * speed;
    }
    if (keyStates[GLFW_KEY_S]) {
        posX -= posDiffX;
        posY -= posDiffY;
    }
    if (keyStates[GLFW_KEY_D]) {
        angle = util::wrap2pi(angle + rotationSpeed);
        posDiffX = cos(angle) * speed;
        posDiffY = sin(angle) * speed;
    }
}

Player::~Player() { }
