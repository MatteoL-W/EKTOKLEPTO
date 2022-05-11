#include <GL/gl.h>
#include "../include/Game.hpp"

Game::Game() {
    currentMap = new Map(level);
    camera = new Camera(currentMap, currentMap->getMapZoom());
    camera->newLevel(level);
}

void Game::update() {
    currentMap->update();

    if (currentMap->isFinished() && level < MAX_LEVELS) {
        level++;
        currentMap = new Map(level);

        camera->setMap(currentMap);
        camera->newLevel(level);
    }

    camera->update();
}

void Game::draw() {
    glClearColor(0.18, 0.22, 0.41, 1);
    currentMap->draw();
    camera->draw();
}

