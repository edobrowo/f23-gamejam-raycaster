#include "game.h"
#include "util.h"

#include "player.h"

Player::Player(float initialX, float initialY, float speed) :
posX{initialX},
posY{initialY},
speed{speed},
posDiffX{0},
posDiffY{0},
angle{PI / 2} {}

void Player::InputOperations() {
    //
}

Player::~Player() { }
