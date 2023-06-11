#ifndef GAME_LEVEL_H
#define GAME_LEVEL_H

#include <string>
#include <vector>

class GameLevel {
public:
    std::vector<std::vector<int>> map;
    unsigned int mapWidth;
    unsigned int mapHeight;

    GameLevel();

    void LoadMap(std::string path);
    void SetMap(const int *mapMat, const unsigned int &mapW, const unsigned int &mapH);
    // void drawMap2D();

    ~GameLevel();
};

#endif // GAME_LEVEL_H
