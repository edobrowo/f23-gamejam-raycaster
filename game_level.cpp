#include <GLFW/glfw3.h>

#include <string>

#include "game_level.h"

GameLevel::GameLevel() :
mapWidth{0},
mapHeight{0} {}

void GameLevel::LoadMap(std::string path) {
    return;
}

void GameLevel::SetMap(const int *mapMat, const unsigned int &mapW, const unsigned int &mapH) {
    mapWidth = mapW;
    mapHeight = mapH;
    for (size_t y = 0; y < mapH; ++y) {
        map.push_back(std::vector<int>());
        for (size_t x = 0; x < mapW; ++x) {
            map[y].push_back(mapMat[y * mapH + x]);
        }
    }
}

GameLevel::~GameLevel() { }

/*
void GameLevel::drawMap2D() {
    Game* gs = Game::GetInstance();
    int xo, yo;
    for (size_t y = 0; y < mapH; ++y) {
        for (size_t x = 0; x < mapW; ++x) {
            if (map[y][x] >= 1) {
                glColor3f(1, 1, 1);
            } else {
                glColor3f(0, 0, 0);
            }
            xo = x * gs->tileSize; yo = y * gs->tileSize;
            glBegin(GL_QUADS);
            glVertex2i(xo, yo);
            glVertex2i(xo, yo + gs->tileSize);
            glVertex2i(xo + gs->tileSize, yo + gs->tileSize);
            glVertex2i(xo + gs->tileSize, yo);
            glEnd();
        }
    }
}
*/
