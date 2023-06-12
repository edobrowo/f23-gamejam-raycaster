#ifndef PLAYER_H
#define PLAYER_H

class Player {
public:
    float posX, posY, angle;
    float speed, rotationSpeed;
    float posDiffX, posDiffY;

    Player(float initialX, float initialY, float speed);
    Player();

    void InputOperations();
    void setPosition(float x, float y);

    ~Player();
};

#endif // PLAYER_H
