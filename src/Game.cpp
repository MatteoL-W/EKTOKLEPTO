#include <GL/GL.h>
#include "../include/Game.hpp"

Game::Game() {
    this->currentMap = new Map();
}

void Game::update() {
    currentMap->update();
}

void Game::draw() {
    glClearColor(0.18, 0.22, 0.41, 1);
    currentMap->draw();
}

