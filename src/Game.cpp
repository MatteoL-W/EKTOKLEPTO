#include <GL/gl.h>
#include "../include/Game.hpp"

Game::Game() {
    this->currentMap = new Map(1);
    this->camera = new Camera(currentMap, 10);
}

void Game::update() {
    currentMap->update();
    camera->update();
}

void Game::draw() {
    glClearColor(0.18, 0.22, 0.41, 1);
    currentMap->draw();
    camera->draw();
}

