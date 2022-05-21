#include <GL/gl.h>
#include <iostream>
#include "../include/Game.hpp"
#include "../include/tools/save.hpp"

std::string Game::saveEmplacements = "assets/save/save.txt";

Game::Game() {}

void Game::setMap(int gameId) {
    initializeMap(gameId);
    camera = new Camera(currentMap, currentMap->getMapZoom());
    camera->newLevel(level);
}

void Game::update() {
    currentMap->update();

    if (currentMap->isFinished() && level < MAX_LEVELS) {
        save(std::to_string(level));
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

/**
 * @brief Initialize the map from the save if needed.
 */
void Game::initializeMap(int gameId) {
    if (gameId == -1) {
        currentMap = new Map(1);
        return;
    }

    if (readSave(gameId).empty()) {
        std::cout << "game not found, starting default map" << std::endl;
        currentMap = new Map(1);
        return;
    }

    currentMap = new Map(stoi(readSave(gameId)) + 1);
}