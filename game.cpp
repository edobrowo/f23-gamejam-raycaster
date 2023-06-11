#include <GLFW/glfw3.h>

#include <iostream>
#include "player.h"

#include "game.h"


Game* Game::instance = nullptr;

Game::Game(const unsigned int &width, const unsigned int &height, const int &tileSize) : 
winWidth{width},
winHeight{height},
tileSize{tileSize} {}

Game* Game::GetInstance(const unsigned int &width, const unsigned int &height, const int &tileSize) {
    if (instance == nullptr) {
        instance = new Game(width, height, tileSize);
    }
    return instance;
}

Game* Game::GetInstance() {
    if (instance == nullptr) {
        instance = new Game(WINDOW_WIDTH_DEFAULT, WINDOW_HEIGHT_DEFAULT, 128);
    }
    return instance;
}

void Game::Init(Player* p) {
    // Player
    player = p;

    // Camera
    camera = new RaycastCamera(player);
    camera->Init();

    // Levels
    int mapW = 8, mapH = 8;
    int map[] = {
        1,1,1,1,1,1,1,1,
        1,0,1,0,0,0,0,1,
        1,0,1,0,0,0,0,1,
        1,0,1,0,0,0,0,1,
        1,0,0,0,0,0,0,1,
        1,0,0,0,0,1,0,1,
        1,0,0,0,0,0,0,1,
        1,1,1,1,1,1,1,1
    };

    GameLevel* gl = new GameLevel();
    gl->SetMap(map, mapW, mapH);

    currentLevel = gl;
}

void Game::Input() {
    player->InputOperations();
}

void Game::Update() {
    //
}

void Game::Render() {
    camera->Render();
}

Game::~Game() { }
