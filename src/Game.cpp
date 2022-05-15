#include <GL/gl.h>
#include "../include/Game.hpp"
#include "../include/tools/Sound.hpp"

Sound* levelUpSound;

Game::Game() {
    currentMap = new Map(level);
    camera = new Camera(currentMap, currentMap->getMapZoom());
    levelUpSound = new Sound("./assets/sounds/level_up.wav");
}

void Game::update() {
    currentMap->update();

    if (currentMap->isFinished() && level < MAX_LEVELS) {
        level++;
        currentMap = new Map(level);

        levelUpSound->play();

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

