#include <GL/gl.h>
#include <iostream>
#include <fstream>
#include "../include/Game.hpp"

Game::Game() {
    initializeMap();
    camera = new Camera(currentMap, currentMap->getMapZoom());
}

void Game::update() {
    currentMap->update();

    if (currentMap->isFinished() && level < MAX_LEVELS) {
        save(std::to_string(level));
        level++;
        currentMap = new Map(level);

        camera->setMap(currentMap);
        camera->setZoom(currentMap->getMapZoom());
    }

    camera->update();
}

void Game::draw() {
    glClearColor(0.18, 0.22, 0.41, 1);
    currentMap->draw();
    camera->draw();
}

/**
 * @brief Save in the save file the current level.
 * @param saveContent
 */
void Game::save(const std::string& saveContent) {
    std::ofstream saveFile (saveEmplacements);
    if (saveFile.is_open())
    {
        saveFile << saveContent << "\n";
        saveFile.close();
    }
    else std::cout << "Unable to open file";
}

/**
 * @brief Initialize the map from the save if needed.
 */
void Game::initializeMap() {
    if (readSave().empty()) {
        currentMap = new Map(1);
        return;
    }

    currentMap = new Map(stoi(readSave()) + 1);
}

/**
 * @brief Return the last level saved
 * @return
 */
std::string Game::readSave() {
    std::string savedLevel;
    std::ifstream savedFile (saveEmplacements);
    if (savedFile.is_open())
    {
        while ( getline (savedFile, savedLevel) )
        {
            return savedLevel;
        }
        savedFile.close();
    }
}
