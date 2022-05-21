#include <GL/gl.h>
#include <iostream>
#include "../include/Game.hpp"
#include "../include/tools/save.hpp"

std::string Game::saveEmplacements = "assets/save/save.txt";
int Game::level = 1;

Game::Game() {}

void Game::setMap() {
    if (Game::level == 0) { Game::level = 1; }
    currentMap = new Map(Game::level);
    camera = new Camera(currentMap, currentMap->getMapZoom());
    minimap = new Minimap(currentMap);
    camera->newLevel(Game::level);
}

void Game::update() {
    currentMap->update();

    if (currentMap->isFinished() && level < MAX_LEVELS) {
        level++;
        currentMap = new Map(level);

        camera->setMap(currentMap);
        camera->newLevel(level);
        minimap->setMap(currentMap);
    }

    camera->update();
}

void Game::draw() {
    glClearColor(0.18, 0.22, 0.41, 1);
    currentMap->draw();
    camera->draw();
    minimap->draw();
}
