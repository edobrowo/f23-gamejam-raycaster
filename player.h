#ifndef PLAYER_H
#define PLAYER_H

class Player {
public:
    float posX, posY, posDiffX, posDiffY, angle;
    float speed;

    Player(float initialX, float initialY, float speed);

    void InputOperations();
    void setPosition(float x, float y);

    ~Player();
};

#endif // PLAYER_H
