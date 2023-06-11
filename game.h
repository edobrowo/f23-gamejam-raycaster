#ifndef GAME_H
#define GAME_H

#include <string>
#include "game_level.h"
#include "level_generator.h"
#include "raycast_camera.h"

#define WINDOW_WIDTH_DEFAULT    1024
#define WINDOW_HEIGHT_DEFAULT   512

// Game state
class Game {
private:
    // Singleton instance
    static Game* instance;
    Game(const unsigned int &width, const unsigned int &height, const int &tileSize);

public:
    // State
    int             keys[512] = {0};
    unsigned int    winWidth, winHeight;
    std::string     title;
    int             tileSize;
    RaycastCamera*  camera;
    Player*         player;
    GameLevel*      currentLevel;

    // Instance
    static Game* GetInstance(const unsigned int &width, const unsigned int &height, const int &tileSize);
    static Game* GetInstance();
    
    // Game state and resource initialization
    void Init(Player* p);

    // Game loop
    void Input();
    void Update();
    void Render();

    ~Game();
    Game(const Game& game) = delete;
    void operator=(const Game &) = delete;
};

#endif // GAME_H
