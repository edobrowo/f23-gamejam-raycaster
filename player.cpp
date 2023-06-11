#include <GLFW/glfw3.h>

#include <cmath>
#include <iostream>
#include "game.h"
#include "util.h"

#include "player.h"

Player::Player(float initialX, float initialY, float speed) :
posX{initialX},
posY{initialY},
speed{speed},
angle{PI / 2} {
    posDiffX = cos(angle) * 5;
    posDiffY = sin(angle) * 5;
}

Player::Player() :
posX{WINDOW_WIDTH_DEFAULT / 2},
posY{WINDOW_HEIGHT_DEFAULT / 2},
speed{5.f},
angle{3*PI / 2} {
    posDiffX = cos(angle) * 5;
    posDiffY = sin(angle) * 5;
}

void Player::InputOperations() {
    Game* gs = Game::GetInstance();
    int* keyStates = gs->keys;

    if (keyStates[GLFW_KEY_W]) {
        posX += posDiffX;
        posY += posDiffY;
    }
    if (keyStates[GLFW_KEY_A]) {
        angle = util::wrap2pi(angle - 0.1);
        posDiffX = cos(angle) * speed;
        posDiffY = sin(angle) * speed;
    }
    if (keyStates[GLFW_KEY_S]) {
        posX -= posDiffX;
        posY -= posDiffY;
    }
    if (keyStates[GLFW_KEY_D]) {
        angle = util::wrap2pi(angle + 0.1);
        posDiffX = cos(angle) * speed;
        posDiffY = sin(angle) * speed;
    }
}

Player::~Player() { }
