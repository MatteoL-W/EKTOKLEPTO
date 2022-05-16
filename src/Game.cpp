#include <GL/gl.h>
#include <iostream>
#include <fstream>
#include "../include/Game.hpp"

Game::Game() {}

void Game::setMap(int gameId) {
    initializeMap(gameId);
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
    std::ofstream saveFile (saveEmplacements, std::ios::app);
    if (saveFile.is_open())
    {
        if (stoi(saveContent) == 1)
            saveFile << "\n";
        saveFile << saveContent << "\n";
        saveFile.close();
    }
    else std::cout << "Unable to open file";
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

/**
 * @brief Return the last level saved
 * @return
 */
std::string Game::readSave(int saveId) {
    std::string savedLevel;
    std::ifstream savedFile (saveEmplacements);
    std::string saveInformation[5][MAX_LEVELS];
    int partCounting = -1, counter = 0;

    if (savedFile.is_open()) {
        std::string currentLine;

        while (getline(savedFile, currentLine)) {
            if (currentLine.empty()) {
                if (partCounting == saveId) {
                    return saveInformation[partCounting][counter-1];
                }
                partCounting++;
                counter = 0;
                continue;
            }
            saveInformation[partCounting][counter] = currentLine;

            counter++;
        }

        if (partCounting == saveId) {
            return saveInformation[partCounting][counter-1];
        }

        savedFile.close();
        return "";
    }
}
