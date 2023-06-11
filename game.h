#ifndef GAME_H
#define GAME_H

#include <string>

// Game state

class Game {
private:
    // Singleton instance
    static Game* instance;
    Game(const unsigned int &width, const unsigned int &height, const std::string& title);

public:
    // State
    int             keys[512];
    unsigned int    winWidth, winHeight;
    std::string     title;

    // Instance
    static Game* GetInstance(const unsigned int &width, const unsigned int &height, const std::string& title);
    
    // Game state and resource initialization
    void Init();

    // Game loop
    void Input();
    void Update();
    void Display();

    ~Game();
    Game(const Game& game) = delete;
    void operator=(const Game &) = delete;
};

#endif // GAME_H
