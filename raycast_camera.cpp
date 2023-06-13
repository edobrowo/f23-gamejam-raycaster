#include <GLFW/glfw3.h>

#include <cmath>
#include <iostream>
#include <limits>
#include "game.h"
#include "game_level.h"
#include "player.h"
#include "util.h"

#include "raycast_camera.h"

#define NUM_RAYS 60

RaycastCamera::RaycastCamera(Player *p) :
player{p} {}

void RaycastCamera::Init() {
    Game* gs = Game::GetInstance();

    // Background
    glClearColor(0.30f, 0.30f, 0.35f, 0.00f);
    
    // Window-sized orthogonal viewing area
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, gs->winWidth, gs->winHeight, 0, 1.f, -1.f);
    glMatrixMode(GL_MODELVIEW);
}

void RaycastCamera::Render() {
    Game* gs = Game::GetInstance();
    GameLevel* level = gs->currentLevel;
    const int tileSize = gs->tileSize;

    // Number of tiles to perform the check through
    int depthOfField;

    float rayX, rayY, rayAngle;
    float offsetX, offsetY, maxDistance;

    rayAngle = util::wrap2pi(player->angle - NUM_RAYS / 2 * DR);

    for (size_t ray = 0; ray < NUM_RAYS; ++ray) {

        // Horizontal line check
        depthOfField = 0;
        float distanceH = std::numeric_limits<float>::max();
        float horizontalX = player->posX, horizontalY = player->posY;
        float nrtan = -1 / tan(rayAngle);

        if (rayAngle > PI) {
            rayY = (static_cast<int>(player->posY) / tileSize) * tileSize - 0.0001;
            rayX = (player->posY - rayY) * nrtan + player->posX;
            offsetY = -tileSize;
            offsetX = -offsetY * nrtan;
        } else if (rayAngle < PI) {
            rayY = (static_cast<int>(player->posY) / tileSize) * tileSize + tileSize;
            rayX = (player->posY - rayY) * nrtan + player->posX;
            offsetY = tileSize;
            offsetX = -offsetY * nrtan;
        } else if (rayAngle == 0 || rayAngle == PI) {
            rayX = player->posX;
            rayY = player->posY;
            depthOfField = 8;
        }

        // Check until a wall is hit or max depth of field is reached
        while (depthOfField < 8) {
            size_t my = (static_cast<int>(rayY) / tileSize);
            size_t mx = (static_cast<int>(rayX) / tileSize);
            if (0 <= mx && mx < level->mapWidth && 0 <= my && my < level->mapHeight && level->map[my][mx] == 1) {
                horizontalX = rayX;
                horizontalY = rayY;
                distanceH = util::dist(player->posX, player->posY, horizontalX, horizontalY);
                depthOfField = 8;
            } else {
                rayX += offsetX;
                rayY += offsetY;
                ++depthOfField;
            }
        }

        // Vertical line check
        depthOfField = 0;
        float distanceV = std::numeric_limits<float>::max();
        float verticalX = player->posX, verticalY = player->posY;
        float ntan = -tan(rayAngle);

        if (rayAngle > PI / 2 && rayAngle < 3 * PI / 2) {
            rayX = (static_cast<int>(player->posX) / tileSize) * tileSize - 0.0001;
            rayY = (player->posX - rayX) * ntan + player->posY;
            offsetX = -tileSize;
            offsetY = -offsetX * ntan;
        } else if (rayAngle < PI / 2 || rayAngle > 3 * PI / 2) {
            rayX = (static_cast<int>(player->posX) / tileSize) * tileSize + tileSize;
            rayY = (player->posX - rayX) * ntan + player->posY;
            offsetX = tileSize;
            offsetY = -offsetX * ntan;
        } else if (rayAngle == 0 || rayAngle == PI) {
            rayY = player->posY;
            rayX = player->posX;
            depthOfField = 8;
        }

        // Check until a wall is hit or max depth of field is reached
        while (depthOfField < 8) {
            size_t my = (static_cast<int>(rayY) / tileSize);
            size_t mx = (static_cast<int>(rayX) / tileSize);
            if (0 <= mx && mx < level->mapWidth && 0 <= my && my < level->mapHeight && level->map[my][mx] == 1) {
                verticalX = rayX;
                verticalY = rayY;
                distanceV = util::dist(player->posX, player->posY, verticalX, verticalY);
                depthOfField = 8;
            } else {
                rayX += offsetX;
                rayY += offsetY;
                ++depthOfField;
            }
        }

        if (distanceV < distanceH) {
            rayX = verticalX;
            rayY = verticalY;
            maxDistance = distanceV;
            glColor3f(0.9, 0, 0);
        } else {
            rayX = horizontalX;
            rayY = horizontalY;
            maxDistance = distanceH;
            glColor3f(0.7, 0, 0);
        }

        // Fisheye lens correction
        float angleDiff = util::wrap2pi(player->angle - rayAngle);
        maxDistance = maxDistance * cos(angleDiff);

        // Line height
        float lineHeight = (gs->tileSize * gs->winHeight) / maxDistance * 2;
        util::clamp(lineHeight, 0, 2 * gs->winHeight);

        // Line width
        float lineWidth = gs->winWidth / NUM_RAYS;

        // Line offsets
        float lineOffsetVert = gs->winHeight / 2 - lineHeight / 2;

        glBegin(GL_QUADS);
        glVertex2i(ray * lineWidth, lineOffsetVert);
        glVertex2i(ray * lineWidth + lineWidth, lineOffsetVert);
        glVertex2i(ray * lineWidth + lineWidth, lineHeight + lineOffsetVert);
        glVertex2i(ray * lineWidth, lineHeight + lineOffsetVert);
        glEnd();

        rayAngle = util::wrap2pi(rayAngle + DR);
    }
}

RaycastCamera::~RaycastCamera() { }
