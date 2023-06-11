#include <GLFW/glfw3.h>

#include <iostream>

#include "game.h"

Game* Game::instance = 0;

Game::Game(const unsigned int &width, const unsigned int &height, const std::string& title) : 
winWidth{width},
winHeight{height},
title{title} { }

Game* Game::GetInstance(const unsigned int &width, const unsigned int &height, const std::string& title) {
    if (instance == nullptr) {
        instance = new Game(width, height, title);
    }
    return instance;
}

void Game::Init() {
    //
}

void Game::Update() {
    //
}

void Game::Input() {
    //
}

void Game::Display() {
    //
}

Game::~Game() {
    //
}
