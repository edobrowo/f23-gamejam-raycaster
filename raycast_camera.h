#ifndef RAYCAST_CAMERA_H
#define RAYCAST_CAMERA_H

#include "player.h"

class RaycastCamera {
private:
    Player* player;

public:
    RaycastCamera(Player *p);

    void Init();
    void Render();

    ~RaycastCamera();
};

#endif // RAYCAST_CAMERA_H
